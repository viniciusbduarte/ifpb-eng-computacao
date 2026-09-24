#include <stdio.h>

#include "esp_event.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "mqtt_client.h"

#include "mqtt_publisher.h"

static const char *TAG = "PUBLISHER";
static esp_mqtt_client_handle_t client;

static void mqtt_event_handler(void *handler_args, esp_event_base_t base,
                               int32_t event_id, void *event_data)
{
    switch ((esp_mqtt_event_id_t)event_id) {
    case MQTT_EVENT_CONNECTED:
        ESP_LOGI(TAG, "Conectado ao broker");
        break;
    case MQTT_EVENT_DISCONNECTED:
        ESP_LOGI(TAG, "Desconectado do broker");
        break;
    default:
        break;
    }
}

static void publish_task(void *pvParameters)
{
    int contador = 0;
    char payload[16];
    while (1) {
        snprintf(payload, sizeof(payload), "%d", contador++);
        esp_mqtt_client_publish(client, "casa/sensor/contador", payload, 0, 1, 0);
        ESP_LOGI(TAG, "Publicado: %s", payload);
        vTaskDelay(pdMS_TO_TICKS(5000));
    }
}

void mqtt_publisher_start(void)
{
    esp_mqtt_client_config_t mqtt_cfg = {
        .broker.address.uri = "mqtt://192.168.1.102:1883",
        .credentials.username = "esp32user",
        .credentials.authentication.password = "esp32pwd",
    };

    client = esp_mqtt_client_init(&mqtt_cfg);
    esp_mqtt_client_register_event(client, ESP_EVENT_ANY_ID, mqtt_event_handler, NULL);
    esp_mqtt_client_start(client);

    xTaskCreate(publish_task, "publish_task", 4096, NULL, 5, NULL);
}