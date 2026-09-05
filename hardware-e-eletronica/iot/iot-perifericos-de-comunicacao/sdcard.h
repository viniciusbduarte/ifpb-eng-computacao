/**
 * @file sdcard.h
 * @brief Driver para montagem, escrita e leitura de arquivos em cartão SD via SPI.
 */

#ifndef SDCARD_H
#define SDCARD_H

#include <stddef.h>
#include "esp_err.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Inicializa o barramento SPI e monta o sistema de arquivos FAT no cartão SD.
 *
 * @param miso Pino GPIO conectado ao MISO/DO do cartão SD.
 * @param mosi Pino GPIO conectado ao MOSI/DI do cartão SD.
 * @param sclk Pino GPIO conectado ao SCK do cartão SD.
 * @param cs   Pino GPIO conectado ao CS do cartão SD.
 *
 * @return ESP_OK se o cartão foi montado com sucesso.
 * @return Código de erro do driver SPI/SDMMC ou do sistema de arquivos
 *         em caso de falha (ex.: cartão ausente, falha ao formatar).
 */
esp_err_t sdcard_init(int miso, int mosi, int sclk, int cs);

/**
 * @brief Desmonta o sistema de arquivos e libera o barramento SPI.
 *
 * Deve ser chamada antes de remover o cartão fisicamente ou ao encerrar
 * o uso do módulo, para evitar corrupção do sistema de arquivos.
 *
 * @return ESP_OK em sucesso, ou código de erro caso a desmontagem falhe.
 */
esp_err_t sdcard_deinit(void);

/**
 * @brief Acrescenta (append) uma linha de texto a um arquivo no cartão SD.
 *
 * Abre o arquivo em modo "a" (append), escreve o texto seguido de uma
 * quebra de linha e fecha o arquivo. Se o arquivo não existir, ele é criado.
 *
 * @param path Caminho completo do arquivo (ex.: "/sdcard/data.csv").
 * @param text Texto a ser gravado, sem necessidade de incluir '\n'.
 *
 * @return ESP_OK em sucesso.
 * @return ESP_ERR_INVALID_ARG se algum parâmetro for NULL.
 * @return ESP_FAIL se o arquivo não puder ser aberto para escrita.
 */
esp_err_t sdcard_append_log(const char *path, const char *text);

/**
 * @brief Lê o conteúdo de um arquivo do cartão SD para um buffer em memória.
 *
 * Lê até (buffer_size - 1) bytes do arquivo e garante a terminação
 * nula da string resultante. Útil para inspecionar/depurar o conteúdo
 * de logs gravados anteriormente (ex.: via terminal UART).
 *
 * @param path        Caminho completo do arquivo (ex.: "/sdcard/data.csv").
 * @param[out] buffer Buffer de destino que receberá o conteúdo lido.
 * @param buffer_size Tamanho total do buffer, incluindo espaço para o
 *                    terminador nulo.
 *
 * @return ESP_OK em sucesso (mesmo que o arquivo esteja vazio).
 * @return ESP_ERR_INVALID_ARG se algum parâmetro for NULL ou buffer_size == 0.
 * @return ESP_ERR_NOT_FOUND se o arquivo não existir ou não puder ser aberto.
 */
esp_err_t sdcard_read_log(const char *path, char *buffer, size_t buffer_size);

/**
 * @brief Lê e imprime (via printf) as últimas N linhas de um arquivo de log.
 *
 * Percorre o arquivo linha a linha e mantém apenas as últimas @p max_lines
 * em um buffer circular simples, imprimindo-as ao final. Pensado para uso
 * em comandos de terminal interativo (ex.: "dump", "tail").
 *
 * @param path      Caminho completo do arquivo.
 * @param max_lines Número máximo de linhas finais a exibir.
 *
 * @return ESP_OK em sucesso.
 * @return ESP_ERR_NOT_FOUND se o arquivo não existir.
 */
esp_err_t sdcard_print_tail(const char *path, unsigned int max_lines);

#ifdef __cplusplus
}
#endif

#endif // SDCARD_H