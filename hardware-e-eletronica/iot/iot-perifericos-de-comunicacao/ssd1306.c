/**
 * @file ssd1306.c
 * @brief Implementação do driver SSD1306 (comandos I2C e fonte bitmap 5x8).
 */

#include "ssd1306.h"
#include "driver/i2c.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"

static const char *TAG_OLED = "SSD1306";

#define I2C_PORT       I2C_NUM_0
#define SSD1306_ADDR   0x3C
#define I2C_TIMEOUT_MS 1000

/** Fonte bitmap 5x8 (colunas), apenas com os caracteres usados pela aplicação. */
static const uint8_t font[128][8] = {
    [' '] = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
    ['-'] = {0x10,0x10,0x10,0x10,0x10,0x10,0x00,0x00},
    ['.'] = {0x00,0x00,0x60,0x60,0x00,0x00,0x00,0x00},
    ['0'] = {0x3E,0x51,0x49,0x45,0x3E,0x00,0x00,0x00},
    ['1'] = {0x00,0x42,0x7F,0x40,0x00,0x00,0x00,0x00},
    ['2'] = {0x42,0x61,0x51,0x49,0x46,0x00,0x00,0x00},
    ['3'] = {0x21,0x41,0x45,0x4B,0x31,0x00,0x00,0x00},
    ['4'] = {0x18,0x14,0x12,0x7F,0x10,0x00,0x00,0x00},
    ['5'] = {0x27,0x45,0x45,0x45,0x39,0x00,0x00,0x00},
    ['6'] = {0x3C,0x4A,0x49,0x49,0x30,0x00,0x00,0x00},
    ['7'] = {0x01,0x71,0x09,0x05,0x03,0x00,0x00,0x00},
    ['8'] = {0x36,0x49,0x49,0x49,0x36,0x00,0x00,0x00},
    ['9'] = {0x06,0x49,0x49,0x29,0x1E,0x00,0x00,0x00},
    ['X'] = {0x63,0x14,0x08,0x14,0x63,0x00,0x00,0x00},
    ['Y'] = {0x07,0x08,0x70,0x08,0x07,0x00,0x00,0x00},
    ['Z'] = {0x61,0x51,0x49,0x45,0x43,0x00,0x00,0x00},
    [':'] = {0x00,0x36,0x36,0x00,0x00,0x00,0x00,0x00}
};

esp_err_t i2c_bus_init(int sda_pin, int scl_pin) {
    i2c_config_t conf = {
        .mode = I2C_MODE_MASTER,
        .sda_io_num = sda_pin,
        .scl_io_num = scl_pin,
        .sda_pullup_en = GPIO_PULLUP_ENABLE,
        .scl_pullup_en = GPIO_PULLUP_ENABLE,
        .master.clk_speed = 400000,
    };

    esp_err_t ret = i2c_param_config(I2C_PORT, &conf);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG_OLED, "Falha ao configurar parâmetros I2C: %s", esp_err_to_name(ret));
        return ret;
    }

    return i2c_driver_install(I2C_PORT, conf.mode, 0, 0, 0);
}

/**
 * @brief Envia um único byte de comando ao SSD1306 (registrador de controle 0x00).
 *
 * @param cmd Byte de comando conforme datasheet do SSD1306.
 * @return ESP_OK em sucesso, ou código de erro do driver I2C.
 */
static esp_err_t ssd1306_cmd(uint8_t cmd) {
    i2c_cmd_handle_t link = i2c_cmd_link_create();
    i2c_master_start(link);
    i2c_master_write_byte(link, (SSD1306_ADDR << 1) | I2C_MASTER_WRITE, true);
    i2c_master_write_byte(link, 0x00, true);
    i2c_master_write_byte(link, cmd, true);
    i2c_master_stop(link);
    esp_err_t ret = i2c_master_cmd_begin(I2C_PORT, link, pdMS_TO_TICKS(I2C_TIMEOUT_MS));
    i2c_cmd_link_delete(link);
    return ret;
}

esp_err_t ssd1306_init(void) {
    const uint8_t init_sequence[] = {
        0xAE, // Display Off
        0x20, // Memory Addressing Mode
        0x00, // ...Horizontal
        0xA1, // Segment Remap
        0xC8, // COM Scan Direction
        0x8D, // Charge Pump
        0x14, // ...Enable Charge Pump
        0xAF  // Display On
    };

    for (size_t i = 0; i < sizeof(init_sequence); i++) {
        esp_err_t ret = ssd1306_cmd(init_sequence[i]);
        if (ret != ESP_OK) {
            ESP_LOGE(TAG_OLED, "Falha ao enviar comando de init 0x%02X: %s",
                     init_sequence[i], esp_err_to_name(ret));
            return ret;
        }
    }
    return ESP_OK;
}

void ssd1306_clear(void) {
    uint8_t buf[128] = {0};
    for (int page = 0; page < 8; page++) {
        ssd1306_cmd(0xB0 + page);
        ssd1306_cmd(0x00);
        ssd1306_cmd(0x10);
        i2c_cmd_handle_t link = i2c_cmd_link_create();
        i2c_master_start(link);
        i2c_master_write_byte(link, (SSD1306_ADDR << 1) | I2C_MASTER_WRITE, true);
        i2c_master_write_byte(link, 0x40, true);
        i2c_master_write(link, buf, sizeof(buf), true);
        i2c_master_stop(link);
        i2c_master_cmd_begin(I2C_PORT, link, pdMS_TO_TICKS(I2C_TIMEOUT_MS));
        i2c_cmd_link_delete(link);
    }
}

void ssd1306_print_string(uint8_t page, uint8_t col, const char *str) {
    if (str == NULL || page > 7) {
        return;
    }

    for (int i = 0; str[i] != '\0'; i++) {
        uint16_t column = col + i * 8;
        if (column > 127) {
            break; // fora dos limites do display, evita overflow
        }

        ssd1306_cmd(0xB0 + page);
        ssd1306_cmd(0x00 + (column & 0x0F));
        ssd1306_cmd(0x10 + ((column >> 4) & 0x0F));

        i2c_cmd_handle_t link = i2c_cmd_link_create();
        i2c_master_start(link);
        i2c_master_write_byte(link, (SSD1306_ADDR << 1) | I2C_MASTER_WRITE, true);
        i2c_master_write_byte(link, 0x40, true);
        i2c_master_write(link, (uint8_t *)font[(uint8_t)str[i]], 8, true);
        i2c_master_stop(link);
        i2c_master_cmd_begin(I2C_PORT, link, pdMS_TO_TICKS(I2C_TIMEOUT_MS));
        i2c_cmd_link_delete(link);
    }
}