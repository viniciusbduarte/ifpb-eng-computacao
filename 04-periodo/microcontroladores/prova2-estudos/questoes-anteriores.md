**Questões Anteriores - Prova 2**

---

### **1.**

Um microcontrolador possui um conversor digital-analógico (DAC) de **16 bits**, cuja saída opera entre **0 e 3,3 V**.

a) Qual é a **resolução**, em volts, deste DAC?

DAC de **16 bits** →
Número de níveis = (2^{16} = 65536)

[
\text{Resolução} = \frac{3,3}{65536} \approx \boxed{50,35\ \mu V}
]

b) Se o registrador de dados do DAC for carregado com o valor **0x33FF** (em hexadecimal), qual será a **tensão de saída**?

[
0x33FF = 13311_{10}
]

[
V_{out} = \frac{13311}{65535} \cdot 3,3
]

[
V_{out} \approx \boxed{0,67\ V}
]

---

### **2.**

O trecho de código mostrado abaixo é utilizado para armazenar as amostras do sinal de um sensor conectado a um canal do ADC do **STM32F407** no array `leitura[]`. Considerando que o sinal será amostrado durante um intervalo de **2 minutos**, qual o **tamanho mínimo, em MB**, necessário para armazenar as amostras digitalizadas pelo ADC?

```c
while(1)
{
    ADC1->CR2 |= ADC_CR2_SWSTART;   // inicia a conversão
    while(!(ADC1->SR & ADC_SR_EOC)); // aguarda o fim da conversão
    uint16_t leitura[cont] = ADC1->DR; // faz a leitura do valor convertido
    ++cont;                         // incrementa o ponteiro
    Delay_us(50);                   // aguarda para converter a próxima amostra
}
```


* Delay entre amostras = **50 μs**
* Frequência de amostragem:

[
f = \frac{1}{50 \times 10^{-6}} = 20,000\ \text{amostras/s}
]

* Tempo total:
  [
  2\ \text{min} = 120\ \text{s}
  ]

* Total de amostras:

[
20,000 \times 120 = 2,400,000
]

* Cada amostra: `uint16_t` = **2 bytes**

[
2,400,000 \times 2 = 4,800,000\ \text{bytes}
]

[
\approx \boxed{4,58\ MB}
]

---

### **3.**

Um conversor **ADC de 6 bits** é usado para fazer a leitura de um sensor de temperatura que fornece uma tensão de **0 a 3,3 V** para uma faixa de temperatura de **20°C a 180°C**. Em um determinado instante, o valor de saída do conversor é **0x3C**. Qual a **temperatura medida** pelo sistema?


* ADC de 6 bits → (2^6 = 64) níveis
* Valor lido:

[
0x3C = 60_{10}
]

* Tensão medida:

[
V = \frac{60}{63} \cdot 3,3 \approx 3,14\ V
]

* Mapeamento temperatura:

[
\text{Faixa} = 180 - 20 = 160^\circ C
]

[
T = 20 + \frac{60}{63} \cdot 160
]

[
T \approx \boxed{172,4^\circ C}
]

---

---

### **4.**

Um microcontrolador STM32 está configurado para usar o **TIM2 (timer de 32 bits)** em modo de contagem crescente para gerar uma interrupção periódica por estouro.

* Clock do timer: **42 MHz**
* Prescaler (**PSC**) = **41999**
* Auto-Reload Register (**ARR**) = **999**

a) Qual será a **frequência da interrupção** gerada?

Clock após prescaler:

[
f_{timer} = \frac{42,000,000}{41999 + 1} = 1000\ Hz
]

* ARR = 999 → conta **1000 ciclos**

[
f_{int} = \frac{1000}{1000} = \boxed{1\ Hz}
]


b) Se quisermos gerar uma interrupção a cada **50 ms**, quais valores de **PSC e ARR** poderíamos usar, mantendo o clock de entrada inalterado?

[
T = 50\ ms = 0,05\ s \Rightarrow f = 20\ Hz
]

Uma solução possível:

* PSC = 41999 → 1 kHz
* ARR = 49 → 50 contagens

✔️ **Resposta válida:**

[
\boxed{PSC = 41999,\ ARR = 49}
]
---

### **5.**

Um microcontrolador STM32 está configurado com três fontes de interrupção:

1. Timer TIM3 (Overflow) — prioridade NVIC = **8**
2. ADC (End of Conversion) — prioridade NVIC = **6**
3. EXTI0 (botão no pino PA0) — prioridade NVIC = **3**

Durante a execução do programa principal, ocorre a seguinte sequência de eventos, com um intervalo de **3 μs** entre eles:

1. O botão em PA0 é pressionado (EXTI0)
2. O Timer TIM3 gera interrupção
3. O ADC conclui a conversão e gera interrupção

a) Considerando que cada ISR dura **5 μs**, explique como ocorrerá o atendimento dessas interrupções.
b) Em quanto tempo, após a ocorrência da primeira interrupção, o processador estará livre para executar o programa principal? (desconsidere tempo de troca de contexto)

---

# ✏️ **Resolução**

---

## ✅ **Questão 1**

### a) Resolução do DAC

DAC de **16 bits** →
Número de níveis = (2^{16} = 65536)

[
\text{Resolução} = \frac{3,3}{65536} \approx \boxed{50,35\ \mu V}
]

---

### b) Tensão para 0x33FF

[
0x33FF = 13311_{10}
]

[
V_{out} = \frac{13311}{65535} \cdot 3,3
]

[
V_{out} \approx \boxed{0,67\ V}
]

---

## ✅ **Questão 2**

* Delay entre amostras = **50 μs**
* Frequência de amostragem:

[
f = \frac{1}{50 \times 10^{-6}} = 20,000\ \text{amostras/s}
]

* Tempo total:
  [
  2\ \text{min} = 120\ \text{s}
  ]

* Total de amostras:

[
20,000 \times 120 = 2,400,000
]

* Cada amostra: `uint16_t` = **2 bytes**

[
2,400,000 \times 2 = 4,800,000\ \text{bytes}
]

[
\approx \boxed{4,58\ MB}
]

---

## ✅ **Questão 3**

* ADC de 6 bits → (2^6 = 64) níveis
* Valor lido:

[
0x3C = 60_{10}
]

* Tensão medida:

[
V = \frac{60}{63} \cdot 3,3 \approx 3,14\ V
]

* Mapeamento temperatura:

[
\text{Faixa} = 180 - 20 = 160^\circ C
]

[
T = 20 + \frac{60}{63} \cdot 160
]

[
T \approx \boxed{172,4^\circ C}
]

---
