#include <string.h>

#include "driver/gpio.h"
#include "esp_log.h"
#include "mqtt_client.h"

#include "mqtt_subscriber.h"

#define LED_GPIO GPIO_NUM_2

static const char *TAG = "SUBSCRIBER";

static void mqtt_event_handler(void *handler_args, esp_event_base_t base,
                                int32_t event_id, void *event_data)
{
    esp_mqtt_event_handle_t event = event_data;
    esp_mqtt_client_handle_t client = event->client;

    switch ((esp_mqtt_event_id_t)event_id) {
    case MQTT_EVENT_CONNECTED:
        ESP_LOGI(TAG, "Conectado, assinando tópico");
        esp_mqtt_client_subscribe(client, "gotham/dpgc/batsignal", 1);
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

void mqtt_subscriber_start(void)
{
    gpio_reset_pin(LED_GPIO);
    gpio_set_direction(LED_GPIO, GPIO_MODE_OUTPUT);

    esp_mqtt_client_config_t mqtt_cfg = {
        .broker.address.uri = "mqtt://192.168.1.102:1883",
        .credentials.username = "esp32user",
        .credentials.authentication.password = "esp32pwd",
    };

    esp_mqtt_client_handle_t client = esp_mqtt_client_init(&mqtt_cfg);
    esp_mqtt_client_register_event(client, ESP_EVENT_ANY_ID, mqtt_event_handler, NULL);
    esp_mqtt_client_start(client);
}