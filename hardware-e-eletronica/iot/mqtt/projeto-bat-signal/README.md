# Projeto Bat-Signal

Projeto IoT com dois dispositivos ESP32 comunicando-se por MQTT:

- **bat-button**: Node A, responsável por ler o botão e publicar os comandos do Bat-Sinal.
- **bat-signal**: Node B, responsável por receber os comandos e controlar o LED indicador.

Os dois nós também publicam periodicamente uma mensagem de estado para indicar que continuam operacionais.

## Arquitetura

```text
[Botão - Node A] -- MQTT --> [Broker] -- MQTT --> [LED - Node B]
       bat-button                         bat-signal
```

O projeto utiliza ESP-IDF, FreeRTOS e a biblioteca ESP-MQTT.

## Comunicação MQTT

### Broker

Os dois projetos estão configurados atualmente para usar:

- URI: `mqtt://192.168.1.102:1883`
- Usuário: `esp32user`
- Senha: `esp32pwd`

Altere esses valores no arquivo `main/mqtt_publisher.c` ou `main/mqtt_subscriber.c` quando o broker estiver em outro endereço ou usar credenciais diferentes.

### Tópicos

| Tópico | Publicador | Função |
|---|---|---|
| `gotham/dpgc/batsignal` | `bat-button` | Envia o estado do botão |
| `gotham/dpgc/status` | Os dois nós | Envia o estado operacional e o uptime |

### Comandos do Bat-Sinal

O Node A alterna entre os seguintes payloads no tópico `gotham/dpgc/batsignal`:

```text
BAT_SIGNAL_ON
BAT_SIGNAL_OFF
```

O Node B assina esse tópico e controla o LED:

- `BAT_SIGNAL_ON`: liga o LED conectado ao GPIO 2.
- `BAT_SIGNAL_OFF`: desliga o LED conectado ao GPIO 2.

### Keep-alive

A cada 30 segundos, cada nó publica no tópico `gotham/dpgc/status` um JSON semelhante a:

```json
{
  "device": "bat_button",
  "status": "ONLINE",
  "uptime_s": 120
}
```

Os valores de `device` são:

- `bat_button` para o Node A.
- `bat_signal` para o Node B.

As mensagens são publicadas com QoS 1 e sem retenção. O envio só ocorre quando o cliente MQTT está conectado ao broker.

## Hardware

### bat-button

- Botão no GPIO 4.
- Pull-up interno habilitado.
- Interrupção configurada na borda de descida.

### bat-signal

- LED no GPIO 2.
- Saída digital para indicar o estado recebido.

Os números dos GPIOs podem ser alterados nas constantes definidas nos arquivos-fonte de cada projeto.

## Estrutura

```text
projeto-bat-signal/
├── README.md
├── bat-button/
│   └── main/
│       ├── app_main.c
│       ├── mqtt_publisher.c
│       └── mqtt_publisher.h
└── bat-signal/
    └── main/
        ├── app_main.c
        ├── mqtt_subscriber.c
        └── mqtt_subscriber.h
```

As pastas `build/` e seus arquivos são gerados pelo ESP-IDF e estão ignorados pelo Git.

## Requisitos

- ESP-IDF instalado e configurado.
- Duas placas ESP32, uma para cada nó.
- Broker MQTT acessível pela rede local.
- Botão conectado ao GPIO 4 do Node A.
- LED conectado ao GPIO 2 do Node B.

A conexão de rede é feita pela rotina `example_connect()`, configurada pelo menu de configuração do ESP-IDF.

## Compilação e gravação

Execute os comandos dentro da pasta do nó correspondente.

### Node A: bat-button

```bash
cd bat-button
idf.py set-target esp32
idf.py menuconfig
idf.py build
idf.py -p PORT flash monitor
```

### Node B: bat-signal

```bash
cd bat-signal
idf.py set-target esp32
idf.py menuconfig
idf.py build
idf.py -p PORT flash monitor
```

Substitua `PORT` pela porta serial da placa, por exemplo `/dev/ttyUSB0`.

Para sair do monitor serial, use `Ctrl-]`.

## Execução

1. Inicie o broker MQTT na rede configurada.
2. Configure Wi-Fi ou Ethernet nos dois projetos pelo `idf.py menuconfig`.
3. Grave e execute o `bat-signal`.
4. Grave e execute o `bat-button`.
5. Pressione o botão do Node A.
6. Observe o LED do Node B e as mensagens no monitor serial.
7. Verifique no tópico `gotham/dpgc/status` os keep-alives dos dois dispositivos.

## Organização do código

- `app_main.c`: inicializa NVS, rede e o módulo MQTT.
- `mqtt_publisher.c`: configura o Node A, trata a interrupção do botão, publica comandos e envia keep-alive.
- `mqtt_subscriber.c`: configura o Node B, assina comandos, controla o LED e envia keep-alive.
- Arquivos `.h`: expõem as funções públicas de inicialização dos módulos MQTT.
