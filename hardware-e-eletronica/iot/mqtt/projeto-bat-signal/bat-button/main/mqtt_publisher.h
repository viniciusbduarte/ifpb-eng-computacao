#pragma once

/**
 * @brief Inicializa o cliente MQTT e o publicador do botão.
 *
 * Configura a conexão com o broker, registra o callback de eventos MQTT,
 * inicia o keep-alive e prepara a leitura do botão.
 */
void mqtt_publisher_start(void);
