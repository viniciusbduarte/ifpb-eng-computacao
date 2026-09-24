#include "driver/gpio.h"
#include "esp_event.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "mqtt_client.h"

#include "mqtt_publisher.h"

static const char *TAG = "PUBLISHER";
static esp_mqtt_client_handle_t client;
static QueueHandle_t button_queue;

#define BUTTON_GPIO GPIO_NUM_4
#define MQTT_TOPIC "gotham/dpgc/batsignal"

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

static void IRAM_ATTR button_isr_handler(void *arg)
{
    int button_level = gpio_get_level(BUTTON_GPIO);
    BaseType_t higher_priority_task_woken = pdFALSE;
    xQueueSendFromISR(button_queue, &button_level, &higher_priority_task_woken);
    if (higher_priority_task_woken) {
        portYIELD_FROM_ISR();
    }
}

static void button_publish_task(void *pvParameters)
{
    int button_event;
    bool signal_on = false;

    while (xQueueReceive(button_queue, &button_event, portMAX_DELAY)) {
        signal_on = !signal_on;
        const char *payload = signal_on ? "BAT_SIGNAL_ON" : "BAT_SIGNAL_OFF";
        esp_mqtt_client_publish(client, MQTT_TOPIC, payload, 0, 1, 0);
        ESP_LOGI(TAG, "Publicado: %s", payload);
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

    gpio_config_t button_config = {
        .pin_bit_mask = 1ULL << BUTTON_GPIO,
        .mode = GPIO_MODE_INPUT,
        .pull_up_en = GPIO_PULLUP_ENABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_NEGEDGE,
    };
    ESP_ERROR_CHECK(gpio_config(&button_config));
    button_queue = xQueueCreate(10, sizeof(int));
    ESP_ERROR_CHECK(gpio_install_isr_service(0));
    ESP_ERROR_CHECK(gpio_isr_handler_add(BUTTON_GPIO, button_isr_handler, NULL));
    xTaskCreate(button_publish_task, "button_publish_task", 4096, NULL, 5, NULL);
}