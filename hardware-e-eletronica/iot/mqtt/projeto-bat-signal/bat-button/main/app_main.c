#include "esp_event.h"
#include "esp_netif.h"
#include "mqtt_publisher.h"
#include "nvs_flash.h"
#include "protocol_examples_common.h"

void app_main(void)
{
    ESP_ERROR_CHECK(nvs_flash_init());
    ESP_ERROR_CHECK(esp_netif_init());
    ESP_ERROR_CHECK(esp_event_loop_create_default());
    ESP_ERROR_CHECK(example_connect());

    mqtt_publisher_start();
}