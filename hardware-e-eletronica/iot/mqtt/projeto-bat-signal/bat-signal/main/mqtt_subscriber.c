#include <stdio.h>
#include <string.h>

#include "driver/gpio.h"
#include "esp_timer.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "mqtt_client.h"

#include "mqtt_subscriber.h"

#define LED_GPIO GPIO_NUM_2
#define STATUS_TOPIC "gotham/dpgc/status"
#define KEEP_ALIVE_INTERVAL_MS 30000

static const char *TAG = "SUBSCRIBER";
static esp_mqtt_client_handle_t client;
static bool mqtt_connected;

/**
 * @brief Publica periodicamente o estado operacional do Node B.
 *
 * A tarefa aguarda 30 segundos entre as publicações e só envia o payload
 * quando o cliente MQTT está conectado.
 *
 * @param pvParameters Parâmetros da tarefa, não utilizados.
 */
static void keep_alive_task(void *pvParameters)
{
    char payload[96];

    while (true) {
        vTaskDelay(pdMS_TO_TICKS(KEEP_ALIVE_INTERVAL_MS));

        if (!mqtt_connected) {
            continue;
        }

        int uptime_s = (int)(esp_timer_get_time() / 1000000);
        int payload_len = snprintf(payload, sizeof(payload),
                                   "{\"device\":\"bat_signal\",\"status\":\"ONLINE\",\"uptime_s\":%d}",
                                   uptime_s);
        /* Publica o keep-alive no tópico de status, com QoS 1 e sem retenção. */
        esp_mqtt_client_publish(client, STATUS_TOPIC, payload, payload_len, 1, 0);
        ESP_LOGI(TAG, "Keep alive publicado: %s", payload);
    }
}

/**
 * @brief Processa conexão, desconexão e mensagens recebidas via MQTT.
 *
 * Ao conectar, o Node B assina `gotham/dpgc/batsignal`. As mensagens
 * `BAT_SIGNAL_ON` e `BAT_SIGNAL_OFF` controlam o LED local.
 *
 * @param handler_args Argumento definido no registro do callback.
 * @param base Base do evento recebido.
 * @param event_id Identificador do evento MQTT.
 * @param event_data Dados associados ao evento MQTT.
 */
static void mqtt_event_handler(void *handler_args, esp_event_base_t base,
                                int32_t event_id, void *event_data)
{
    esp_mqtt_event_handle_t event = event_data;
    esp_mqtt_client_handle_t client = event->client;

    switch ((esp_mqtt_event_id_t)event_id) {
    case MQTT_EVENT_CONNECTED:
        mqtt_connected = true;
        ESP_LOGI(TAG, "Conectado, assinando tópico");
        /* Assina os comandos enviados pelo Node A, com QoS 1. */
        esp_mqtt_client_subscribe(client, "gotham/dpgc/batsignal", 1);
        break;
    case MQTT_EVENT_DISCONNECTED:
        mqtt_connected = false;
        break;
    case MQTT_EVENT_DATA:
        ESP_LOGI(TAG, "TOPIC=%.*s DATA=%.*s",
                 event->topic_len, event->topic,
                 event->data_len, event->data);
        if (event->data_len == strlen("BAT_SIGNAL_ON") &&
            strncmp(event->data, "BAT_SIGNAL_ON", event->data_len) == 0) {
            gpio_set_level(LED_GPIO, 1);
            ESP_LOGI(TAG, "[ALERTA] Bat-Sinal Ativado! O Cavaleiro das Trevas foi convocado.");
        } else if (event->data_len == strlen("BAT_SIGNAL_OFF") &&
                   strncmp(event->data, "BAT_SIGNAL_OFF", event->data_len) == 0) {
            gpio_set_level(LED_GPIO, 0);
            ESP_LOGI(TAG, "[INFO] Bat-Sinal Desativado.");
        }
        break;
    default:
        break;
    }
}

/**
 * @brief Inicializa o cliente MQTT, o assinante e o keep-alive.
 *
 * O Node B assina o tópico `gotham/dpgc/batsignal` e publica seu estado
 * operacional em `gotham/dpgc/status`.
 */
void mqtt_subscriber_start(void)
{
    gpio_reset_pin(LED_GPIO);
    gpio_set_direction(LED_GPIO, GPIO_MODE_OUTPUT);

    esp_mqtt_client_config_t mqtt_cfg = {
        .broker.address.uri = "mqtt://192.168.1.102:1883",
        .credentials.username = "esp32user",
        .credentials.authentication.password = "esp32pwd",
    };

    /* Cria o cliente MQTT usando o broker e as credenciais configuradas. */
    client = esp_mqtt_client_init(&mqtt_cfg);
    /* Registra o callback que processa conexão, dados recebidos e falhas. */
    esp_mqtt_client_register_event(client, ESP_EVENT_ANY_ID, mqtt_event_handler, NULL);
    /* Inicia a conexão MQTT e permite o processamento dos eventos. */
    esp_mqtt_client_start(client);
    xTaskCreate(keep_alive_task, "keep_alive_task", 4096, NULL, 5, NULL);
}