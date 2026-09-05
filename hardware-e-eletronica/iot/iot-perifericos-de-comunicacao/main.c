/**
 * @file main.c
 * @author Vinicius Batista Duarte
 * @brief Aplicação principal: lê o MPU6050, exibe no SSD1306, grava no
 *        cartão SD e disponibiliza um terminal interativo via UART.
 *
 * Estrutura de tarefas (FreeRTOS):
 *  - task_i2c_display:   lê o acelerômetro e atualiza o display a cada 500 ms.
 *  - task_sd_logger:     grava a última leitura no cartão SD a cada 1000 ms.
 *  - task_sd_reader:      a cada SD_READ_INTERVAL gravações, imprime o
 *                        conteúdo do arquivo de log no monitor serial.
 *  - task_uart_terminal: processa comandos digitados no monitor serial.
 */

#include <stdio.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"

#include "mpu6050.h"
#include "ssd1306.h"
#include "sdcard.h"

#define TAG "MAIN_APP"
#define LOG_LOCAL_LEVEL ESP_LOG_INFO

// Mapeamento dos pinos no ESP32-S3
#define SDA_PIN   8
#define SCL_PIN   9
#define MISO_PIN  13
#define MOSI_PIN  11
#define SCLK_PIN  12
#define CS_PIN    10

#define SD_LOG_PATH "/sdcard/data.csv"

/**
 * @brief A cada quantas gravações no SD o conteúdo do log é impresso no serial.
 *
 * Ex.: com valor 5 e gravação a cada 1000 ms (@ref task_sd_logger),
 * o dump no serial ocorre aproximadamente a cada 5 segundos.
 * Ajuste este valor conforme a frequência de leitura desejada.
 */
#define SD_READ_INTERVAL 5

/** Última leitura válida do acelerômetro, compartilhada entre tarefas. */
static mpu6050_data_t current_accel = {0};

/** Indica se o cartão SD foi montado com sucesso (evita I/O em cartão ausente). */
static bool sdcard_ready = false;

/** Handle da tarefa de leitura periódica do SD, usado para notificá-la. */
static TaskHandle_t sd_reader_task_handle = NULL;

/** Contador de gravações bem-sucedidas no SD, usado para disparar a leitura. */
static uint32_t sd_write_count = 0;

/**
 * @brief Tarefa responsável por ler o MPU6050 e atualizar o display OLED.
 *
 * Executa a cada 500 ms. Em caso de falha de leitura, apenas registra
 * o erro no log e mantém os últimos valores válidos na tela.
 *
 * @param pvParameters Não utilizado.
 */
void task_i2c_display(void *pvParameters) {
    char str_x[16], str_y[16], str_z[16];
    while (1) {
        if (mpu6050_read_accel(&current_accel) == ESP_OK) {
            snprintf(str_x, sizeof(str_x), "X:%0.2f", current_accel.accel_x);
            snprintf(str_y, sizeof(str_y), "Y:%0.2f", current_accel.accel_y);
            snprintf(str_z, sizeof(str_z), "Z:%0.2f", current_accel.accel_z);

            ssd1306_print_string(1, 0, str_x);
            ssd1306_print_string(3, 0, str_y);
            ssd1306_print_string(5, 0, str_z);

            ESP_LOGI(TAG, "I2C: Leitura do MPU6050 OK -> X:%.2f Y:%.2f Z:%.2f",
                     current_accel.accel_x, current_accel.accel_y, current_accel.accel_z);
        } else {
            ESP_LOGE(TAG, "I2C: Falha na leitura do MPU6050!");
        }
        vTaskDelay(pdMS_TO_TICKS(500));
    }
}

/**
 * @brief Tarefa responsável por gravar periodicamente os dados no cartão SD.
 *
 * Executa a cada 1000 ms. Não realiza I/O caso o cartão não tenha sido
 * montado com sucesso na inicialização (@ref sdcard_ready).
 *
 * @param pvParameters Não utilizado.
 */
void task_sd_logger(void *pvParameters) {
    char log_line[64];
    while (1) {
        if (sdcard_ready) {
            snprintf(log_line, sizeof(log_line), "X=%.2f, Y=%.2f, Z=%.2f",
                     current_accel.accel_x, current_accel.accel_y, current_accel.accel_z);

            if (sdcard_append_log(SD_LOG_PATH, log_line) == ESP_OK) {
                ESP_LOGI(TAG, "SD: Dados salvos no cartão SD com sucesso.");

                sd_write_count++;
                if (sd_write_count % SD_READ_INTERVAL == 0 && sd_reader_task_handle != NULL) {
                    // Acorda a tarefa de leitura sem bloquear esta tarefa.
                    xTaskNotifyGive(sd_reader_task_handle);
                }
            } else {
                ESP_LOGE(TAG, "SD: Falha ao escrever no cartão SD!");
            }
        }
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

/**
 * @brief Tarefa que imprime o conteúdo do log do SD no serial periodicamente.
 *
 * Fica bloqueada aguardando uma notificação (ver xTaskNotifyGive), que é
 * enviada por @ref task_sd_logger a cada SD_READ_INTERVAL gravações bem
 * sucedidas. Ao ser notificada, lê o arquivo de log inteiro e o imprime
 * no monitor serial.
 *
 * Usar notificação de tarefa (em vez de polling) evita I/O desnecessário
 * no cartão SD e mantém a CPU ociosa entre uma leitura e outra.
 *
 * @param pvParameters Não utilizado.
 */
void task_sd_reader(void *pvParameters) {
    static char file_buf[1024];

    while (1) {
        // Bloqueia indefinidamente até receber uma notificação.
        ulTaskNotifyTake(pdTRUE, portMAX_DELAY);

        if (!sdcard_ready) {
            continue;
        }

        if (sdcard_read_log(SD_LOG_PATH, file_buf, sizeof(file_buf)) == ESP_OK) {
            ESP_LOGI(TAG, "SD-READER: %d gravações completadas, exibindo log no serial.", SD_READ_INTERVAL);
            printf("==== [%s] (a cada %d leituras) ====\n%s\n=====================================\n",
                   SD_LOG_PATH, SD_READ_INTERVAL, file_buf);
        } else {
            ESP_LOGE(TAG, "SD-READER: Falha ao ler '%s'.", SD_LOG_PATH);
        }
    }
}

/**
 * @brief Tarefa de terminal interativo via UART/stdin.
 *
 * Comandos suportados:
 *  - "status": imprime o estado geral do sistema.
 *  - "read"  : lê e imprime o conteúdo completo do arquivo de log do SD.
 *  - "tail"  : imprime as últimas linhas do arquivo de log do SD.
 *
 * @param pvParameters Não utilizado.
 */
void task_uart_terminal(void *pvParameters) {
    char rx_buf[64];
    static char file_buf[512];

    while (1) {
        if (fgets(rx_buf, sizeof(rx_buf), stdin) != NULL) {
            rx_buf[strcspn(rx_buf, "\r\n")] = 0; // Remove quebras de linha
            if (strlen(rx_buf) > 0) {
                if (strcmp(rx_buf, "status") == 0) {
                    ESP_LOGI(TAG, "TERMINAL: Sistema operacional. Módulos I2C e SPI %s.",
                             sdcard_ready ? "ativos" : "com SD indisponível");

                } else if (strcmp(rx_buf, "read") == 0) {
                    if (!sdcard_ready) {
                        ESP_LOGW(TAG, "TERMINAL: Cartão SD não disponível.");
                    } else if (sdcard_read_log(SD_LOG_PATH, file_buf, sizeof(file_buf)) == ESP_OK) {
                        printf("---- Conteúdo de %s ----\n%s\n------------------------\n",
                               SD_LOG_PATH, file_buf);
                    } else {
                        ESP_LOGE(TAG, "TERMINAL: Falha ao ler '%s'.", SD_LOG_PATH);
                    }

                } else if (strcmp(rx_buf, "tail") == 0) {
                    if (!sdcard_ready) {
                        ESP_LOGW(TAG, "TERMINAL: Cartão SD não disponível.");
                    } else {
                        sdcard_print_tail(SD_LOG_PATH, 5);
                    }

                } else {
                    ESP_LOGW(TAG, "TERMINAL: Comando '%s' desconhecido. "
                                  "Use 'status', 'read' ou 'tail'.", rx_buf);
                }
            }
        }
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}

/**
 * @brief Ponto de entrada da aplicação ESP-IDF.
 *
 * Inicializa o barramento I2C, o MPU6050, o display OLED e o cartão SD,
 * e então dispara as três tarefas do FreeRTOS que compõem a aplicação.
 */
void app_main(void) {
    esp_log_level_set("*", ESP_LOG_INFO);
    ESP_LOGI(TAG, "=== Iniciando Sistema Multi-módulo ESP32-S3 ===");

    // 1. Inicialização do barramento I2C único
    if (i2c_bus_init(SDA_PIN, SCL_PIN) == ESP_OK) {
        ESP_LOGI(TAG, "Barramento I2C ativado (SDA: %d, SCL: %d)", SDA_PIN, SCL_PIN);
    } else {
        ESP_LOGE(TAG, "Erro ao inicializar o barramento I2C!");
    }

    // 2. Inicialização dos periféricos I2C
    if (mpu6050_init(SDA_PIN, SCL_PIN) == ESP_OK && mpu6050_is_connected()) {
        ESP_LOGI(TAG, "MPU6050 detectado e configurado.");
    } else {
        ESP_LOGE(TAG, "Falha ao inicializar/detectar o MPU6050!");
    }

    ssd1306_init();
    ssd1306_clear();
    ESP_LOGI(TAG, "Display SSD1306 inicializado.");

    // 3. Inicialização do Cartão SD via SPI
    if (sdcard_init(MISO_PIN, MOSI_PIN, SCLK_PIN, CS_PIN) == ESP_OK) {
        ESP_LOGI(TAG, "Cartão SD montado via SPI.");
        sdcard_ready = true;
    } else {
        ESP_LOGE(TAG, "Falha ao montar o Cartão SD! Log em SD será desativado.");
    }

    // 4. Início das Tarefas no FreeRTOS
    // task_sd_reader é criada antes de task_sd_logger para garantir que
    // sd_reader_task_handle já esteja válido quando a primeira notificação
    // puder ser enviada.
    xTaskCreate(task_sd_reader, "task_sd_read", 4096, NULL, 3, &sd_reader_task_handle);
    xTaskCreate(task_i2c_display, "task_i2c", 4096, NULL, 5, NULL);
    xTaskCreate(task_sd_logger, "task_sd", 4096, NULL, 4, NULL);
    xTaskCreate(task_uart_terminal, "task_uart", 3072, NULL, 3, NULL);
}