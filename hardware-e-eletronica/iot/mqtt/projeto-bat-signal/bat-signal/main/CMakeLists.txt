idf_component_register(SRCS "app_main.c" "mqtt_subscriber.c"
                    INCLUDE_DIRS "."
                    REQUIRES esp_driver_gpio esp_wifi esp_event esp_netif nvs_flash mqtt)