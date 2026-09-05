/**
 * @file mpu6050.c
 * @brief Implementação do driver do MPU6050 (leitura de aceleração via I2C).
 */

#include "mpu6050.h"
#include "driver/i2c.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"

static const char *TAG_MPU = "MPU6050";

#define I2C_PORT              I2C_NUM_0
#define MPU6050_ADDR          0x68
#define MPU6050_PWR_MGMT_1    0x6B
#define MPU6050_ACCEL_XOUT_H  0x3B
#define MPU6050_WHO_AM_I      0x75
#define MPU6050_WHO_AM_I_VAL  0x68

#define I2C_TIMEOUT_MS        1000
#define ACCEL_SCALE_2G        16384.0f /**< LSB/g para a escala padrão de ±2g. */

/**
 * @brief Escreve um único byte em um registrador do MPU6050.
 *
 * @param reg   Endereço do registrador de destino.
 * @param value Valor a ser escrito.
 * @return ESP_OK em sucesso, ou código de erro do driver I2C.
 */
static esp_err_t mpu6050_write_reg(uint8_t reg, uint8_t value) {
    i2c_cmd_handle_t cmd = i2c_cmd_link_create();
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, (MPU6050_ADDR << 1) | I2C_MASTER_WRITE, true);
    i2c_master_write_byte(cmd, reg, true);
    i2c_master_write_byte(cmd, value, true);
    i2c_master_stop(cmd);
    esp_err_t ret = i2c_master_cmd_begin(I2C_PORT, cmd, pdMS_TO_TICKS(I2C_TIMEOUT_MS));
    i2c_cmd_link_delete(cmd);
    return ret;
}

/**
 * @brief Lê @p len bytes a partir de um registrador do MPU6050.
 *
 * @param reg        Registrador inicial de leitura.
 * @param[out] buf    Buffer de destino, deve ter ao menos @p len bytes.
 * @param len        Quantidade de bytes a ler.
 * @return ESP_OK em sucesso, ou código de erro do driver I2C.
 */
static esp_err_t mpu6050_read_regs(uint8_t reg, uint8_t *buf, size_t len) {
    i2c_cmd_handle_t cmd = i2c_cmd_link_create();
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, (MPU6050_ADDR << 1) | I2C_MASTER_WRITE, true);
    i2c_master_write_byte(cmd, reg, true);
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, (MPU6050_ADDR << 1) | I2C_MASTER_READ, true);
    i2c_master_read(cmd, buf, len, I2C_MASTER_LAST_NACK);
    i2c_master_stop(cmd);
    esp_err_t ret = i2c_master_cmd_begin(I2C_PORT, cmd, pdMS_TO_TICKS(I2C_TIMEOUT_MS));
    i2c_cmd_link_delete(cmd);
    return ret;
}

esp_err_t mpu6050_init(int sda_pin, int scl_pin) {
    // Acorda o sensor (limpa o bit SLEEP em PWR_MGMT_1).
    esp_err_t ret = mpu6050_write_reg(MPU6050_PWR_MGMT_1, 0x00);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG_MPU, "Falha ao acordar o MPU6050 (SDA=%d, SCL=%d): %s",
                 sda_pin, scl_pin, esp_err_to_name(ret));
        return ret;
    }

    // Pequena espera recomendada pelo datasheet após sair do sleep.
    vTaskDelay(pdMS_TO_TICKS(10));

    if (!mpu6050_is_connected()) {
        ESP_LOGW(TAG_MPU, "MPU6050 inicializado, mas WHO_AM_I não confere.");
    }

    return ESP_OK;
}

esp_err_t mpu6050_read_accel(mpu6050_data_t *data) {
    if (data == NULL) {
        return ESP_ERR_INVALID_ARG;
    }

    uint8_t buf[6];
    esp_err_t ret = mpu6050_read_regs(MPU6050_ACCEL_XOUT_H, buf, sizeof(buf));
    if (ret != ESP_OK) {
        ESP_LOGE(TAG_MPU, "Falha na leitura do acelerômetro: %s", esp_err_to_name(ret));
        return ret;
    }

    int16_t raw_x = (int16_t)((buf[0] << 8) | buf[1]);
    int16_t raw_y = (int16_t)((buf[2] << 8) | buf[3]);
    int16_t raw_z = (int16_t)((buf[4] << 8) | buf[5]);

    data->accel_x = raw_x / ACCEL_SCALE_2G;
    data->accel_y = raw_y / ACCEL_SCALE_2G;
    data->accel_z = raw_z / ACCEL_SCALE_2G;

    return ESP_OK;
}

bool mpu6050_is_connected(void) {
    uint8_t who_am_i = 0;
    esp_err_t ret = mpu6050_read_regs(MPU6050_WHO_AM_I, &who_am_i, 1);
    if (ret != ESP_OK) {
        return false;
    }
    return who_am_i == MPU6050_WHO_AM_I_VAL;
}