#pragma once

/**
 * @brief Inicializa o cliente MQTT e o assinante do Bat-Sinal.
 *
 * Configura a conexão com o broker, registra o callback de eventos MQTT,
 * inicia a assinatura do tópico de controle e o keep-alive.
 */
void mqtt_subscriber_start(void);