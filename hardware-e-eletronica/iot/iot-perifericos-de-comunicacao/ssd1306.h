/**
 * @file ssd1306.h
 * @brief Driver mínimo para display OLED SSD1306 (128x64) via I2C.
 *
 * Suporta apenas texto simples com uma fonte bitmap 5x8 embutida,
 * organizado em 8 "páginas" (linhas de 8 pixels) e 128 colunas.
 */

#ifndef SSD1306_H
#define SSD1306_H

#include <stdint.h>
#include "esp_err.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Inicializa o barramento I2C compartilhado usado pelo display e outros periféricos.
 *
 * @param sda_pin Pino GPIO usado como SDA.
 * @param scl_pin Pino GPIO usado como SCL.
 *
 * @return ESP_OK em sucesso, ou código de erro do driver I2C.
 */
esp_err_t i2c_bus_init(int sda_pin, int scl_pin);

/**
 * @brief Envia a sequência de comandos de inicialização ao SSD1306.
 *
 * Deve ser chamada após i2c_bus_init(). Configura o display em modo
 * de endereçamento horizontal e liga a saída.
 *
 * @return ESP_OK em sucesso.
 */
esp_err_t ssd1306_init(void);

/**
 * @brief Limpa todo o conteúdo do display (preenche com pixels apagados).
 */
void ssd1306_clear(void);

/**
 * @brief Escreve uma string de texto em uma posição do display.
 *
 * @param page Página (linha de 8 pixels) de destino, de 0 a 7.
 * @param col  Coluna inicial em pixels, de 0 a 127.
 * @param str  String terminada em '\0' a ser exibida. Caracteres fora
 *             da fonte embutida são renderizados como espaço em branco.
 */
void ssd1306_print_string(uint8_t page, uint8_t col, const char *str);

#ifdef __cplusplus
}
#endif

#endif // SSD1306_H