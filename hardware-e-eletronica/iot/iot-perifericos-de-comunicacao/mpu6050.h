/**
 * @file mpu6050.h
 * @brief Driver simples para o acelerômetro/giroscópio MPU6050 via I2C.
 *
 * Este módulo assume que o barramento I2C já foi inicializado
 * externamente (ver ssd1306.h / i2c_bus_init) antes de chamar
 * mpu6050_init().
 */

#ifndef MPU6050_H
#define MPU6050_H

#include <stdbool.h>
#include "esp_err.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Estrutura com os dados de aceleração lidos do MPU6050.
 *
 * Os valores já estão convertidos para "g" (gravidade),
 * considerando a escala padrão de ±2g (sensibilidade 16384 LSB/g).
 */
typedef struct {
    float accel_x; /**< Aceleração no eixo X, em g. */
    float accel_y; /**< Aceleração no eixo Y, em g. */
    float accel_z; /**< Aceleração no eixo Z, em g. */
} mpu6050_data_t;

/**
 * @brief Inicializa o sensor MPU6050.
 *
 * Envia o comando de "wake up" (limpa o bit de sleep no registrador
 * PWR_MGMT_1), tirando o sensor do modo de baixo consumo.
 *
 * @param sda_pin Pino GPIO usado como SDA (apenas para referência/log,
 *                o barramento já deve estar configurado).
 * @param scl_pin Pino GPIO usado como SCL (apenas para referência/log).
 *
 * @return ESP_OK em caso de sucesso, ou código de erro do driver I2C.
 */
esp_err_t mpu6050_init(int sda_pin, int scl_pin);

/**
 * @brief Lê os valores de aceleração (X, Y, Z) do MPU6050.
 *
 * @param[out] data Ponteiro para estrutura que receberá os valores lidos.
 *                  Não pode ser NULL.
 *
 * @return ESP_OK em caso de sucesso.
 * @return ESP_ERR_INVALID_ARG se @p data for NULL.
 * @return Código de erro do driver I2C em caso de falha de comunicação.
 */
esp_err_t mpu6050_read_accel(mpu6050_data_t *data);

/**
 * @brief Verifica se o MPU6050 responde no endereço esperado (WHO_AM_I).
 *
 * Útil para checar a presença do sensor antes de tentar ler dados,
 * evitando logs de erro repetidos caso o hardware não esteja conectado.
 *
 * @return true se o sensor respondeu corretamente, false caso contrário.
 */
bool mpu6050_is_connected(void);

#ifdef __cplusplus
}
#endif

#endif // MPU6050_H