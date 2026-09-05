/**
 * @file sdcard.c
 * @brief Implementação do driver de cartão SD (montagem via SPI, escrita e leitura de logs).
 */

#include "sdcard.h"
#include <stdio.h>
#include <string.h>
#include "esp_vfs_fat.h"
#include "sdmmc_cmd.h"
#include "esp_log.h"

static const char *TAG_SD = "SDCARD";

#define MOUNT_POINT      "/sdcard"
#define SD_SPI_HOST      SPI2_HOST
#define SD_MAX_FILES     5
#define SD_ALLOC_UNIT    (16 * 1024)

/** Handle global do cartão montado, usado para desmontar em sdcard_deinit(). */
static sdmmc_card_t *s_card = NULL;

/** Indica se o barramento SPI já foi inicializado, para evitar reinicialização. */
static bool s_spi_bus_initialized = false;

esp_err_t sdcard_init(int miso, int mosi, int sclk, int cs) {
    esp_vfs_fat_sdmmc_mount_config_t mount_config = {
        .format_if_mount_failed = true,
        .max_files = SD_MAX_FILES,
        .allocation_unit_size = SD_ALLOC_UNIT
    };

    spi_bus_config_t bus_cfg = {
        .mosi_io_num = mosi,
        .miso_io_num = miso,
        .sclk_io_num = sclk,
        .quadwp_io_num = -1,
        .quadhd_io_num = -1,
    };

    esp_err_t ret = spi_bus_initialize(SD_SPI_HOST, &bus_cfg, SDSPI_DEFAULT_DMA);
    if (ret != ESP_OK && ret != ESP_ERR_INVALID_STATE) {
        // ESP_ERR_INVALID_STATE só ocorre se o barramento já estava inicializado,
        // o que não é necessariamente um erro fatal aqui.
        ESP_LOGE(TAG_SD, "Falha ao inicializar o barramento SPI: %s", esp_err_to_name(ret));
        return ret;
    }
    s_spi_bus_initialized = true;

    sdmmc_host_t host = SDSPI_HOST_DEFAULT();
    host.slot = SD_SPI_HOST;

    sdspi_device_config_t slot_config = SDSPI_DEVICE_CONFIG_DEFAULT();
    slot_config.gpio_cs = cs;
    slot_config.host_id = SD_SPI_HOST;

    ret = esp_vfs_fat_sdspi_mount(MOUNT_POINT, &host, &slot_config, &mount_config, &s_card);
    if (ret != ESP_OK) {
        if (ret == ESP_FAIL) {
            ESP_LOGE(TAG_SD, "Falha ao montar o sistema de arquivos. "
                              "Verifique se o cartão está formatado corretamente.");
        } else {
            ESP_LOGE(TAG_SD, "Falha ao inicializar o cartão SD (%s). "
                              "Verifique as conexões SPI (MISO=%d, MOSI=%d, SCLK=%d, CS=%d).",
                     esp_err_to_name(ret), miso, mosi, sclk, cs);
        }
        return ret;
    }

    ESP_LOGI(TAG_SD, "Cartão SD montado em '%s'.", MOUNT_POINT);
    return ESP_OK;
}

esp_err_t sdcard_deinit(void) {
    if (s_card == NULL) {
        return ESP_OK; // nada a fazer
    }

    esp_err_t ret = esp_vfs_fat_sdcard_unmount(MOUNT_POINT, s_card);
    s_card = NULL;

    if (s_spi_bus_initialized) {
        spi_bus_free(SD_SPI_HOST);
        s_spi_bus_initialized = false;
    }

    if (ret != ESP_OK) {
        ESP_LOGE(TAG_SD, "Falha ao desmontar o cartão SD: %s", esp_err_to_name(ret));
    } else {
        ESP_LOGI(TAG_SD, "Cartão SD desmontado com segurança.");
    }
    return ret;
}

esp_err_t sdcard_append_log(const char *path, const char *text) {
    if (path == NULL || text == NULL) {
        return ESP_ERR_INVALID_ARG;
    }

    FILE *f = fopen(path, "a");
    if (f == NULL) {
        ESP_LOGE(TAG_SD, "Não foi possível abrir '%s' para escrita.", path);
        return ESP_FAIL;
    }

    fprintf(f, "%s\n", text);
    fclose(f);
    return ESP_OK;
}

esp_err_t sdcard_read_log(const char *path, char *buffer, size_t buffer_size) {
    if (path == NULL || buffer == NULL || buffer_size == 0) {
        return ESP_ERR_INVALID_ARG;
    }

    FILE *f = fopen(path, "r");
    if (f == NULL) {
        ESP_LOGW(TAG_SD, "Arquivo '%s' não encontrado para leitura.", path);
        buffer[0] = '\0';
        return ESP_ERR_NOT_FOUND;
    }

    size_t read_bytes = fread(buffer, 1, buffer_size - 1, f);
    buffer[read_bytes] = '\0';
    fclose(f);

    return ESP_OK;
}

esp_err_t sdcard_print_tail(const char *path, unsigned int max_lines) {
    if (path == NULL || max_lines == 0) {
        return ESP_ERR_INVALID_ARG;
    }

    FILE *f = fopen(path, "r");
    if (f == NULL) {
        ESP_LOGW(TAG_SD, "Arquivo '%s' não encontrado.", path);
        return ESP_ERR_NOT_FOUND;
    }

    // Buffer circular simples para guardar as últimas N linhas.
    const size_t MAX_LINE_LEN = 96;
    char (*lines)[MAX_LINE_LEN] = calloc(max_lines, MAX_LINE_LEN);
    if (lines == NULL) {
        fclose(f);
        return ESP_ERR_NO_MEM;
    }

    unsigned int count = 0;
    unsigned int idx = 0;
    char line_buf[MAX_LINE_LEN];

    while (fgets(line_buf, sizeof(line_buf), f) != NULL) {
        strncpy(lines[idx], line_buf, MAX_LINE_LEN - 1);
        lines[idx][MAX_LINE_LEN - 1] = '\0';
        idx = (idx + 1) % max_lines;
        count++;
    }
    fclose(f);

    unsigned int to_print = (count < max_lines) ? count : max_lines;
    unsigned int start = (count < max_lines) ? 0 : idx;

    printf("---- Últimas %u linha(s) de '%s' ----\n", to_print, path);
    for (unsigned int i = 0; i < to_print; i++) {
        unsigned int pos = (start + i) % max_lines;
        printf("%s", lines[pos]);
    }
    printf("--------------------------------------\n");

    free(lines);
    return ESP_OK;
}