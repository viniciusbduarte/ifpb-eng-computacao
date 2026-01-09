## 🧩 Exercícios – Programação de GPIO no STM32F407

Realize a programação do GPIO no STM32F407, escolhendo corretamente os pinos, para implementar as seguintes tarefas:

> ⚙️ Utilize resistores limitadores de 470Ω para os LEDs externos
> *(Solicite ao professor o acesso à biblioteca do Display LCD)*

---

### 1. Piscar LED

Piscar um LED numa frequência de **4 Hz**, com largura de pulso de **100 ms**.

---

### 2. Buzzer – Sinal Sonoro

Acionar um buzzer para emitir ciclicamente o seguinte sinal sonoro:
**1 beep curto**, aguarda um tempo e, em seguida, **2 beeps curtos**, aguardando mais um tempo.

---

### 3. LEDs com Intensidade Variável

Acender dois LEDs com **diferentes intensidades de brilho**, alternando alternadamente a intensidade em tempo de execução:
enquanto um LED estiver **aumentando** o brilho, o outro deve estar **diminuindo** o brilho.

---

### 4. Acionamento com Botões

Utilizar os botões da placa **K0**, **K1** e **K_UP** para acionar 3 LEDs, independentemente.
Cada vez que um botão for pressionado, o LED correspondente deverá ser acionado.
Apenas **um dos LEDs** deve estar ativo por vez.

---

### 5. Sistema de Perguntas e Respostas

Utilizar 3 botões (**K0**, **K1**, **K_UP**) e 2 LEDs (**D2** e **D3**):

* Os botões K0 e K1 correspondem a dois participantes.
* O botão K_UP funciona como um botão de reinício.
* Quando K0 for pressionado, o LED D2 deve acender e **impedir o acionamento** do outro LED, mesmo que K1 seja pressionado em seguida.
* O mesmo vale para o inverso (K1 → D3).
* O LED só deve apagar quando o botão K_UP for pressionado.

Esse tipo de lógica é usada em **sistemas de quiz**, onde o primeiro jogador a apertar o botão bloqueia o outro até o sistema ser liberado novamente.

---

### 6. Contagem Binária

Apresentar uma **contagem binária de 8 bits** a partir de 8 LEDs externos.

> 💡 Dica: conecte os LEDs a pinos contíguos de um mesmo GPIO e use a função `GPIO_WritePort()` para acioná-los simultaneamente.

---

### 7. Efeito “LED Andante”

Implementar o efeito “**LED andante**” nos 8 LEDs da questão anterior:

* Ative o primeiro LED e faça com que ele **se desloque** do primeiro ao último.
* Ligue o primeiro LED, apague-o e acenda o próximo, até chegar ao oitavo LED.
* Em seguida, o movimento deve **voltar** (andar para trás).

---

### 8. Semáforo

Simular o funcionamento de um **cruzamento com sinais de trânsito** usando 6 LEDs.

---

### 9. Contagem Hexadecimal (1 Dígito)

Apresentar uma contagem **hexadecimal crescente e decrescente** de um dígito em um display de **7 segmentos**.
A contagem deve incrementar de `0x0` até `0xF` e depois decrementar até `0x0`, repetindo indefinidamente.

---

### 10. Contagem Hexadecimal (2 Dígitos)

Apresentar uma contagem **hexadecimal crescente e decrescente** de dois dígitos em **dois displays de 7 segmentos**.

* A contagem vai de `0x00` até `0xFF` e depois de `0xFF` até `0x00`.
* Utilize **multiplexação** para reduzir o número de terminais.
* Use **transistores como drivers de potência** na comutação.

---

### 11. Exibir Nome no Display LCD

Exibir:

* Seu **primeiro nome** na 1ª linha,
* O **segundo nome** na 2ª,
* O **terceiro nome** na 3ª,
* E uma **contagem regressiva de 10 até 0** na 4ª linha.

Repetir o processo indefinidamente.

---

### 12. Controle de Velocidade – Motor DC

Implementar o controle de velocidade de um **motor DC**, para que ele:

* Acelere suavemente até a velocidade máxima,
* Desacelere suavemente até parar,
* Inverta o sentido e repita.

> Use uma **ponte H** como driver e frequência **PWM de 2 kHz**.

---

### 13. Motor de Passo Bipolar

Acionar um **motor de passo bipolar** para que o eixo:

* Faça **dois giros completos no sentido horário**,
* Depois **dois giros completos no sentido anti-horário**,
* Repetindo o processo indefinidamente.

> Use **passos completos (8)**.

---

### 14. Controle Temporizado com Botões

Crie um programa que:

* Ao pressionar **K0**, o **LED D2** ligue por **2 s**.
* Ao pressionar **K1**, o **LED D3** ligue por **4 s**.

Após os períodos, os LEDs desligam e aguardam novos pressionamentos.
O sistema deve funcionar **sem travar**, permitindo que os dois LEDs operem independentemente. Se K0 for pressionado enquanto D2 está ligado, D2 deve iniciar um novo pulso imediatamente. Já se K1 for pressionado enquanto D3 está ligado, D3 deve esperar o pulso atual acabar para começar outro.

> Utilize interrupções de temporizador e flags de tempo.
> Pinos sugeridos: **PE4 → K0**, **PE3 → K1**.

---

### 15. Lógica de Sequência (K0 → K1)

Utilizar dois **push-buttons (K0 e K1)** para acionar um LED com a seguinte regra:

* O LED **só acende** se os dois botões forem pressionados **em sequência**,
* Primeiro **K0**, depois **K1**.

---

### 16. Lógica de Tempo (K1 → K0)

Utilizar dois **push-buttons (K0 e K1)** para acionar um LED:

* O LED **só acende** se os dois botões forem pressionados juntos,
* Primeiro **K1**, depois **K0**,
* O segundo botão (**K0**) deve ser pressionado em até **1 s** após o primeiro (**K1**).

---

### 17. Controle de Microservo

Controlar um **microservo motor** para que alterne suavemente entre **0° e 180°**:

* Um botão aumenta o ângulo,
* Outro diminui.

---

### 18. Teclado 4×4

Utilizar um **teclado de membrana 4×4**, fazendo sua **decodificação** e apresentando a tecla pressionada em um **display de 7 segmentos**.

---

### 19. Sensor Ultrassônico – Estacionamento

Fazer a leitura de um **sensor de proximidade ultrassônico**, semelhante aos sensores de estacionamento automotivos.

Definir três limites de distância:

* **D1 = 10 cm**, **D2 = 30 cm**, **D3 = 50 cm**

Regras:

* Distância > 50 cm → buzzer **desligado**
* 50 cm ≥ distância > 30 cm → **beeps lentos**
* 30 cm ≥ distância > 10 cm → **beeps médios**
* Distância ≤ 10 cm → **beeps rápidos**

---

### 20. Jogo “Genius”

Utilizando **4 botões e 4 LEDs externos**, implementar o antigo jogo da memória **Genius**.

> Para criar aleatoriedade, utilize a função
> `Random_Number()` da biblioteca **Utility.h**,
> que retorna um número inteiro sem sinal de 32 bits.

