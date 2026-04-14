/*
 * Utility.h for STM32CubeIDE
 *
 *  Created on: 04 de dez de 2024
 *  Author: Prof. Dr. Fagner de Araujo Pereira e Luiz Oliveira
 *
 */

#ifndef UTILITY_H_
#define UTILITY_H_

//Definições Globais
//Números dos pinos GPIO
enum{
	PIN_0,
	PIN_1,
	PIN_2,
	PIN_3,
	PIN_4,
	PIN_5,
	PIN_6,
	PIN_7,
	PIN_8,
	PIN_9,
	PIN_10,
	PIN_11,
	PIN_12,
	PIN_13,
	PIN_14,
	PIN_15
};

//Modos de operação de um pino GPIO
enum{
	INPUT,		//modo de entrada digital
	OUTPUT,		//modo de saída digital
	ALTERNATE,	//modo de função alternativa
	ANALOG		//modo analógico
};

//Tipos de saída de um pino GPIO
enum{
	PUSH_PULL,	//saída push-pull
	OPEN_DRAIN	//saída open-drain
};

//Níveis lógicos de saída de um pino
enum{
	LOW,	//nível lógico baixo
	HIGH	//nível lógico alto
};

//Modos de operação dos resistores de pull-up e pull-down
enum{
	PULL_UP = 0b01,		//resistor de pull-up
	PULL_DOWN = 0b10	//resistor de pull-down
};

//Funções alternativas dos pinos GPIOS
enum{
	AF0,
	AF1,
	AF2,
	AF3,
	AF4,
	AF5,
	AF6,
	AF7,
	AF8,
	AF9,
	AF10,
	AF11,
	AF12,
	AF13,
	AF14,
	AF15
};

//Interrupções externas
enum{
	EXTI0,
	EXTI1,
	EXTI2,
	EXTI3,
	EXTI4,
	EXTI5,
	EXTI6,
	EXTI7,
	EXTI8,
	EXTI9,
	EXTI10,
	EXTI11,
	EXTI12,
	EXTI13,
	EXTI14,
	EXTI15
};

//Bordas de gatilho de EXTI
enum{
	FALLING_EDGE = 1,
	RISING_EDGE = 2
};

//Canais do DAC
enum
{
	DAC_CHANNEL1,
	DAC_CHANNEL2
};

//Resoluções do DAC (em bits)
enum
{
	DAC_RES_12BITS,
	DAC_RES_8BITS
};

//Formas de onda automáticas do DAC
enum
{
	AUTO_TRIANGLE,
	AUTO_NOISE
};

//Amplitudes do DAC
enum
{
	AMP_1BIT,
	AMP_2BITS,
	AMP_3BITS,
	AMP_4BITS,
	AMP_5BITS,
	AMP_6BITS,
	AMP_7BITS,
	AMP_8BITS,
	AMP_9BITS,
	AMP_10BITS,
	AMP_11BITS,
	AMP_12BITS
};

//Modos de operação do ADC
enum
{
	SINGLE_CHANNEL,
	MULTI_CHANNEL
};

//Resoluções do ADC (em bits)
enum
{
	ADC_RES_12BITS,
	ADC_RES_10BITS,
	ADC_RES_8BITS,
	ADC_RES_6BITS
};

//Canais ADC
enum
{
	ADC_IN0,
	ADC_IN1,
	ADC_IN2,
	ADC_IN3,
	ADC_IN4,
	ADC_IN5,
	ADC_IN6,
	ADC_IN7,
	ADC_IN8,
	ADC_IN9,
	ADC_IN10,
	ADC_IN11,
	ADC_IN12,
	ADC_IN13,
	ADC_IN14,
	ADC_IN15
};



//Protótipos de funções úteis

//Funções de configuração do sistema de clock
void Utility_Init(void);		//inicialização de funções da biblioteca
void Configure_Clock(void);		//configuração do sistema de clock

//Funções de timers e temporização
void TIM2_Setup(void);				//configuração do Timer2 como base de tempo de 1us
void Delay_us(uint32_t delay);		//atraso em us
void Delay_ms(uint32_t delay);		//atraso em ms

//Funções de manipulação de GPIO
void GPIO_Clock_Enable(GPIO_TypeDef* GPIOx);								//habilita o clock de um GPIO
void GPIO_Pin_Mode(GPIO_TypeDef* GPIOx, uint8_t pin, uint8_t mode);			//configura o modo de operação de um pino de um GPIO
void GPIO_Output_Type(GPIO_TypeDef* GPIOx, uint8_t pin, uint8_t mode);		//configura o tipo de saída de um pino de um GPIO
void GPIO_Alternate_Function(GPIO_TypeDef* GPIOx, uint8_t pin, uint8_t function);	//configura a função alternativa de um pino de um GPIO
static inline void GPIO_Write_Pin(GPIO_TypeDef* GPIOx, uint8_t pin, uint8_t level);	//escreve um nível lógico em um pino de um GPIO
static inline void GPIO_Toggle_Pin(GPIO_TypeDef* GPIOx, uint8_t pin);				//inverte o nível lógico em um pino de um GPIO
static inline void GPIO_Write_Port(GPIO_TypeDef* GPIOx, uint16_t value);			//escreve um valor numa porta GPIO
void GPIO_Resistor_Enable(GPIO_TypeDef* GPIOx, uint8_t pin, uint8_t mode);	//habilita os resistores de pull-up ou pull-down
static inline uint8_t GPIO_Read_Pin(GPIO_TypeDef* GPIOx, uint8_t pin);		//lê e retorna o nível lógico em um pino de um GPIO
static inline uint16_t GPIO_Read_Port(GPIO_TypeDef* GPIOx);					//lê e retorna os níveis lógicos de uma porta GPIO

//Função de configuração de interrupções externas
#define GET_MACRO(_1, _2, _3, _4, NAME, ...) NAME
#define EXTI_Config(...) GET_MACRO(__VA_ARGS__, EXTI_Config4, EXTI_Config3)(__VA_ARGS__)
//#define EXTI_Config(...)	EXTI_Config_Helper(__VA_ARGS__)
void EXTI_Config_Helper(uint8_t exti_line, GPIO_TypeDef* GPIOx, uint8_t trigger1, uint8_t trigger2);
void EXTI_Config3(uint8_t exti_line, GPIO_TypeDef* GPIOx, uint8_t trigger1); //Função de configuração com 3 argumentos
void EXTI_Config4(uint8_t exti_line, GPIO_TypeDef* GPIOx, uint8_t trigger1, uint8_t trigger2);	//Função de configuração com 4 argumentos
static inline void EXTI_Clear_Pending(uint8_t exti_line);	//limpa bit de pendência da interrupção EXTI

//Funções de manipulação do DAC
#define GET_DAC_MACRO(_1, _2, _3, NAME, ...) NAME
#define DAC_Init(...) GET_DAC_MACRO(__VA_ARGS__, DAC_Init3, _, DAC_Init1)(__VA_ARGS__)
void DAC_Init1(uint8_t channel);  //inicializa apenas o canal
void DAC_Init3(uint8_t channel, uint8_t waveform, uint8_t amplitude);  //inicializa o canal + tipo de sinal automático + amplitude
void DAC_SetValue(uint8_t channel, uint16_t value, uint8_t resolution);	//escreve um valor com a resolução especificada no DAC selecionado
void DAC_SWTrigger(uint8_t channel);	//gatilhamento do DAC por software

//Funções de manipulação do ADC
void ADC_Init(ADC_TypeDef *ADCx, uint8_t mode, uint8_t resolution);			//inicializa o ADC em SINGLE_CHANNEL ou MULTI_CHANNEL e especifica resolução
void ADC_SingleChannel(ADC_TypeDef *ADCx, uint8_t channel);					//configura o ADC para converter um único canal
uint16_t ADC_GetSingleConversion(ADC_TypeDef *ADCx);						//lê o valor convertido de um único canal
void ADC_MultiChannel(ADC_TypeDef *ADCx, uint8_t numChannels, uint8_t *channels);			//configura o ADC para converter múltiplos canais
void ADC_GetMultiConversions(ADC_TypeDef *ADCx, uint8_t numChannels, uint16_t *results);	//lê os valores convertidos de múltiplos canais

//Funções de periféricos de comunicação
void USART1_Init(void);				//configuração da USART1 para debug com printf

//Funções de geração de números aleatórios
uint32_t Random_Number(void);		//retorna um número aleatório de 32 bits



//Declarações de funções úteis

//Funções de configuração do sistema de clock do STM32
//Inicialização de funções da biblioteca
void Utility_Init(void)
{
	Configure_Clock();	//inicializa o sistema de clock
	TIM2_Setup();		//configura o Timer2 como base de tempo de 1us
}

//Configuração do sistema de clock para velocidade máxima em todos os barramentos utilizando um cristal externo de 8MHz
//HCLK = 168 MHz
//APB1 = 42 MHz
//APB2 = 84 MHz
//USB, RNG, SDIO = 48 MHz
void Configure_Clock(void)
{
	//Parâmetros do PLL principal
	#define PLL_M	4
	#define PLL_N	168
	#define PLL_P	2
	#define PLL_Q	7

	//Configurações da Flash e do regulador de tensão para permitir operação em alta velocidade
	FLASH->ACR = FLASH_ACR_PRFTEN | FLASH_ACR_ICEN |FLASH_ACR_DCEN |FLASH_ACR_LATENCY_5WS;	//habilita prefetch, caches e a latência da flash
	RCC->APB1ENR |= RCC_APB1ENR_PWREN;	//habilita o clock da interface de energia
	PWR->CR |= PWR_CR_VOS;				//regulador de tensão no modo 2

	//Configuração do modo de agrupamento de prioridades das interrupções
	NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4);

	//Reseta os registradores do módulo RCC para o estado inicial
	RCC->CIR = 0;				//desabilita todas as interrupções de RCC
	RCC->CR |= RCC_CR_HSION;	//liga o oscilador HSI
	RCC->CFGR = 0;				//reseta o registrador CFGR
	//Desliga HSE, CSS e o PLL e o bypass de HSE
	RCC->CR &= ~(RCC_CR_HSEON | RCC_CR_CSSON | RCC_CR_PLLON | RCC_CR_HSEBYP);
	RCC->PLLCFGR = 0x24003010;	//reseta o registrador PLLCFGR

	//Configura a fonte de clock (HSE), os parâmetros do PLL e prescalers dos barramentos AHB, APB
	RCC->CR |= RCC_CR_HSEON;				//habilita HSE
	while(!((RCC->CR) & RCC_CR_HSERDY));	//espera HSE ficar pronto
    RCC->CFGR |= 0x9400;	//HCLK = SYSCLK/1, PCLK2 = HCLK/2, PCLK1 = HCLK/4

    //Configura a fonte de clock e os parâmetros do PLL principal
    RCC->PLLCFGR = PLL_M | (PLL_N << 6) | (((PLL_P >> 1) -1) << 16) | (0x400000) | (PLL_Q << 24);

    RCC->CR |= RCC_CR_PLLON;			//habilita o PLL
    while(!(RCC->CR & RCC_CR_PLLRDY));	//espera o PLL ficar pronto verificando a flag PLLRDY

    RCC->CFGR |= 0x2;					//seleciona o PLL como fonte de SYSCLK
    while((RCC->CFGR & 0xC) != 0x8);	//espera o PLL ser a fonte de SYSCLK
}



//Funções de timers e temporização
//Configura o timer 2 como base de tempo de 1us
void TIM2_Setup(void)
{
	//O modo padrão do contador é com contagem crescente
	RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;	//liga o clock do Timer2
	TIM2->PSC = 83;						//prescaler para incrementos a cada 1uS
	TIM2->EGR = TIM_EGR_UG;				//update event para escrever o valor do prescaler
	TIM2->CR1 |= TIM_CR1_CEN;			//habilita o timer
}

//Criação de atraso em us
void Delay_us(uint32_t delay)
{
	TIM2->CNT = 0;				//inicializa o contador com 0
	while(TIM2->CNT < delay);	//aguarda o tempo passar
}

//Criação de atraso em ms
void Delay_ms(uint32_t delay)
{
	uint32_t max = 1000*delay;
	TIM2->CNT = 0;				//inicializa o contador com 0
	while(TIM2->CNT < max);		//aguarda o tempo passar
}



//Funções de manipulação de GPIO
//Habilita o clock de um GPIO
void GPIO_Clock_Enable(GPIO_TypeDef* GPIOx)
{
	RCC->AHB1ENR |= (1 << ((uint32_t)GPIOx - (GPIOA_BASE)) / ((GPIOB_BASE) - (GPIOA_BASE)));
}

//Configura o modo de operação de um pino de um GPIO
void GPIO_Pin_Mode(GPIO_TypeDef* GPIOx, uint8_t pin, uint8_t mode)
{
	GPIOx->MODER &= ~(0b11 << 2*pin);	//reseta os 2 bits do modo de operação
	GPIOx->MODER |= (mode << 2*pin);	//configura o modo selecionado
}

//Configura o tipo de saída de um pino de um GPIO
void GPIO_Output_Type(GPIO_TypeDef* GPIOx, uint8_t pin, uint8_t mode)
{
	GPIOx->OTYPER &= ~(1 << pin);	//reseta o tipo de saída
	GPIOx->OTYPER |= (mode << pin);	//configura o tipo selecionado
}

//Configura a função alternativa de um pino de um GPIO
void GPIO_Alternate_Function(GPIO_TypeDef* GPIOx, uint8_t pin, uint8_t function)
{
	GPIOx->AFR[pin/8] &= ~(0b1111 << ((pin % 8) * 4));	//reseta os 4 bits da função alternativa
	GPIOx->AFR[pin/8] |= (function << ((pin % 8) * 4));	//configura a função selecionada
}

//Escreve um nível lógico em um pino de um GPIO
static inline void GPIO_Write_Pin(GPIO_TypeDef* GPIOx, uint8_t pin, uint8_t level)
{
	if(level)
		GPIOx->ODR |= (1 << pin);	//nível alto no pino
	else
		GPIOx->ODR &= ~(1 << pin);	//nível baixo no pino

	//GPIOx->BSRR |= (1 << (pin + 16 * (1 - level)));	//alternativa usando o registrador BSRR
}

//Inverte o nível lógico em um pino de um GPIO
static inline void GPIO_Toggle_Pin(GPIO_TypeDef* GPIOx, uint8_t pin)
{
	GPIOx->ODR ^= (1 << pin);	//inverte o nível lógico no pino
}

//Escreve um valor numa porta GPIO
static inline void GPIO_Write_Port(GPIO_TypeDef* GPIOx, uint16_t value)
{
	GPIOx->ODR = value;
}

//Habilita os resistores de pull-up ou pull-down
void GPIO_Resistor_Enable(GPIO_TypeDef* GPIOx, uint8_t pin, uint8_t mode)
{
	GPIOx->PUPDR &= ~(0b11 << 2*pin);	//desabilita qualquer resistor
	GPIOx->PUPDR |= (mode << 2*pin);	//habilita o resistor selecionado
}

//Lê e retorna o nível lógico em um pino de um GPIO
static inline uint8_t GPIO_Read_Pin(GPIO_TypeDef* GPIOx, uint8_t pin)
{
	return ((GPIOx->IDR & (1 << pin)) >> pin);
}

//Lê e retorna os níveis lógicos de uma porta GPIO
static inline uint16_t GPIO_Read_Port(GPIO_TypeDef* GPIOx)
{
	return GPIOx->IDR;
}



//Funções de manipulação das interrupções externas
//Função de configuração
//#define EXTI_Config(...)	EXTI_Config_Helper(__VA_ARGS__)
void EXTI_Config_Helper(uint8_t exti_line, GPIO_TypeDef* GPIOx, uint8_t trigger1, uint8_t trigger2)
{
	uint8_t index = exti_line / 4;          //calcula o índice de EXTICR[]
	uint8_t shift = (exti_line % 4) * 4;    //calcula o campo de bits dentro do EXTICR[index]
	uint8_t port = ((uint32_t)GPIOx - (GPIOA_BASE)) / ((GPIOB_BASE) - (GPIOA_BASE)); //calcula o número da porta GPIO

	RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;		//habilita o clock de SYSCFG
	SYSCFG->EXTICR[index] |= (port << shift);	//seleciona a porta/pino como gatilho de EXTI

	if((trigger1 == FALLING_EDGE) || (trigger2 == FALLING_EDGE))
		EXTI->FTSR |= 1 << exti_line;	//seleciona borda de descida
	if((trigger1 == RISING_EDGE) || (trigger2 == RISING_EDGE))
		EXTI->RTSR |= 1 << exti_line;	//seleciona borda de subida

	EXTI->IMR |= 1 << exti_line;	//habilita a interrupção EXTI
}

//Função de configuração com 3 argumentos
void EXTI_Config3(uint8_t exti_line, GPIO_TypeDef* GPIOx, uint8_t trigger1)
{
    EXTI_Config_Helper(exti_line, GPIOx, trigger1, 0);
}

//Função de configuração com 4 argumentos
void EXTI_Config4(uint8_t exti_line, GPIO_TypeDef* GPIOx, uint8_t trigger1, uint8_t trigger2)
{
    EXTI_Config_Helper(exti_line, GPIOx, trigger1, trigger2);
}

//Função de limpeza de flag de pendência
static inline void EXTI_Clear_Pending(uint8_t exti_line)
{
	EXTI->PR |= 1 << exti_line;	//limpa o flag de pendência em EXTI
}



//Funções de manipulação do DAC
//Inicializa o DAC e os pinos GPIO de acordo com o canal selecionado.
//Esta função configura o pino GPIO associado ao DAC, habilita a interface digital
//e seleciona o canal apropriado com base no valor do parâmetro channel.
//@param  channel: identifica o canal DAC desejado (DAC_CHANNEL1 ou DAC_CHANNEL2).
void DAC_Init1(uint8_t channel)
{
	GPIO_Clock_Enable(GPIOA);			//liga o clock do GPIOA
	RCC->APB1ENR |= RCC_APB1ENR_DACEN;	//habilita o clock da interface digital do DAC

	GPIO_Pin_Mode(GPIOA, 4+channel, ANALOG);	//configura o pino no modo analógico
	DAC->CR |= 1 << 16*channel;					//habilita o canal
}

//Inicializa o DAC e os pinos GPIO de acordo com canal selecionado.
//Esta função configura o pino GPIO associado ao DAC, habilita a interface digital
//seleciona o canal apropriado com base no valor do parâmetro channel,
//habilita a geração de forma de onda automática com uma determinada amplitude.
//@param  channel: identifica o canal DAC desejado (DAC_CHANNEL1 ou DAC_CHANNEL2).
//@param  waveform: forma de onda (AUTO_TRIANGLE ou AUTO_NOISE).
//@param  amplitude: amplitude da forma de onda (AMP_1BIT, AMP_2BITS, ..., AMP_12BITS).
void DAC_Init3(uint8_t channel, uint8_t waveform, uint8_t amplitude)
{
	GPIO_Clock_Enable(GPIOA);			//liga o clock do GPIOA
	RCC->APB1ENR |= RCC_APB1ENR_DACEN;	//habilita o clock da interface digital do DAC

	GPIO_Pin_Mode(GPIOA, 4+channel, ANALOG);		//configura o pino no modo analógico
	DAC->CR |= (2-waveform) << (6 + 16*channel);	//seleciona a forma de onda
	DAC->CR |= amplitude << (8 + 16*channel);		//seleciona a amplitude
	DAC->CR |= 0b111 << (3 + 16*channel);			//seleciona disparo por software
	DAC->CR |= 1 << (2 + 16*channel);				//habilita gatilhamento
	DAC->CR |= 1 << 16*channel;						//habilita o canal
}

//Escreve o valor de saída, com a resolução especificada, no canal selecionado do DAC.
//Esta função escreve o valor de saída no DAC selecionado com base no canal e resolução especificados.
//@param  channel: identifica o canal do DAC desejado (DAC_CHANNEL1 ou DAC_CHANNEL2).
//@param  value: valor a ser escrito no DAC (12 bits ou 8 bits conforme a resolução).
//@param  resolution: resolução do DAC (DAC_RES_12BITS ou DAC_RES_8BITS)
void DAC_SetValue(uint8_t channel, uint16_t value, uint8_t resolution)
{
	switch((channel << 1) | resolution)
	{
		case 0b00:
			DAC->DHR12R1 = value;	//escrita de 12 bits no canal 1
			break;

		case 0b01:
			DAC->DHR8R1 = value;	//escrita de 8 bits no canal 1
			break;

		case 0b10:
			DAC->DHR12R2 = value;	//escrita de 12 bits no canal 2
			break;

		case 0b11:
			DAC->DHR8R2 = value;	//escrita de 8 bits no canal 2
			break;
	}
}

//Faz o gatilhamento por software no canal selecionado do DAC.
//@param  channel: identifica o canal do DAC desejado (DAC_CHANNEL1 ou DAC_CHANNEL2).
void DAC_SWTrigger(uint8_t channel)
{
	DAC->SWTRIGR |= 1 << channel;
}



//Funções de manipulação do ADC
//Inicializa o periférico ADCx de acordo com a configuração do clock e outros parâmetros.
//Configura o clock do ADC selecionado e habilita o ADC.
//@param  ADCx: onde x pode ser 1, 2 ou 3 para selecionar o ADC desejado.
//@param  mode: modo de operação do ADC (SINGLE_CHANNEL ou MULTI_CHANNEL).
//@param  resolution: resolução da conversão do ADC (ADC_RES_12BITS, ADC_RES_10BITS, ADC_RES_8BITS ou ADC_RES_6BITS).
void ADC_Init(ADC_TypeDef *ADCx, uint8_t mode, uint8_t resolution)
{
	//Configuração do Clock do ADCx
	//Habilitação do Clock
	RCC->APB2ENR |= (1 << ((uint32_t)ADCx - (ADC1_BASE)) / ((ADC2_BASE) - (ADC1_BASE))) << 8;

	//Configuração do prescaler do ADC
	ADC->CCR |= (0b01 << 16);	//prescaler /4 (84MHz/4 = 21MHz)

	//Configura modo de operação
	if(!mode)	//SINGLE_CHANNEL
	{
		ADCx->CR1 &= ~ADC_CR1_SCAN;	//desabilita o escaneamento de canais
		ADC1->CR2 &= ~ADC_CR2_EOCS;
	}
	else		//MULTI_CHANNEL
	{
		ADCx->CR1 |= ADC_CR1_SCAN;	//habilita o escaneamento de canais
		ADC1->CR2 |= ADC_CR2_EOCS;	//bit EOC setado ao final de cada conversão
	}

	//Definição da resolução
	ADCx->CR1 &= ~ADC_CR1_RES;		//limpa o campo da resolução
	ADCx->CR1 |= resolution << 24;	//escreve a resolução

	ADCx->SMPR2 |= 0b111;			//seleção do tempo de amostragem (máximo)

	//Liga o ADCx
	ADCx->CR2 |= ADC_CR2_ADON;
	Delay_ms(1);	//aguarda o ADC iniciar
}

//Inicializa o ADC e configura o canal específico para conversão.
//Esta função configura o pino de entrada do canal selecionado como analógico
//e configura o sequenciador do ADC para realizar a conversão nesse canal.
//@param  ADCx: onde x pode ser 1, 2 ou 3 para selecionar o periférico ADC.
//@param  canal: número do canal a ser convertido (ADC_IN0 a ADC_IN15).
void ADC_SingleChannel(ADC_TypeDef *ADCx, uint8_t channel)
{
	//Configuração do canal a ser convertido pelo ADCx
	if(channel < 8)
	{
		GPIO_Clock_Enable(GPIOA);				//habilita o clock do GPIOA
		GPIO_Pin_Mode(GPIOA, channel, ANALOG);	//configura o pino PAx como função analógica
	}
	else if(channel == 8 || channel == 9)
	{
		GPIO_Clock_Enable(GPIOB);					//habilita o clock do GPIOB
		GPIO_Pin_Mode(GPIOB, channel - 8, ANALOG);	//configura o pino PB(x-8) como função analógica
	}
	else if(channel >= 10 && channel <= 15)
	{
		GPIO_Clock_Enable(GPIOC);					//habilita o clock do GPIOC
		GPIO_Pin_Mode(GPIOC, channel - 10, ANALOG);	//configura o pino PC(x-10) como função analógica
	}

	//Seleciona o canal a ser convertido pelo ADCx
	ADCx->SQR1 &= ~0xF << 20;	//seleciona a quantidade de canais (1 canal)
	ADCx->SQR3 &= ~0x1F;		//limpa o campo do canal
	ADCx->SQR3 |= channel;		//escreve o canal
}

//Inicia a conversão do ADC e retorna o valor lido.
//Esta função ativa a conversão do canal configurado e aguarda até que a conversão
//esteja completa antes de retornar o valor lido.
//@param  ADCx: onde x pode ser 1, 2 ou 3 para selecionar o ADC.
//@retval Retorna o valor da conversão realizada pelo ADC.
uint16_t ADC_GetSingleConversion(ADC_TypeDef *ADCx)
{
	ADCx->CR2 |= ADC_CR2_SWSTART;		//inicia a conversão
	while (!(ADCx->SR & ADC_SR_EOC));	//aguarda o fim da conversão
	return ADCx->DR;					//retorna o valor convertido
}

//Configura o ADC para múltiplos canais.
//Configura os pinos de entrada como analógicos para os canais selecionados
//e configura o sequenciador do ADC para realizar a sequência de conversões.
//@param  ADCx: onde x pode ser 1, 2 ou 3 para selecionar o ADC.
//@param  numChannels: quantidade de canais a serem convertidos.
//@param  channels: array contendo, ordenadamente, os canais a serem convertidos.
void ADC_MultiChannel(ADC_TypeDef *ADCx, uint8_t numChannels, uint8_t *channels)
{
    //Configuração dos pinos de entrada dos canais como analógicos
    for(int i = 0; i < numChannels; i++)
    {
        if(channels[i] < 8)
        {
            GPIO_Clock_Enable(GPIOA); 					//habilita o clock do GPIOA
            GPIO_Pin_Mode(GPIOA, channels[i], ANALOG);	//configura o pino PAx como analógico
        }
        else if(channels[i] >= 8 && channels[i] <= 9)
        {
            GPIO_Clock_Enable(GPIOB);						//habilita o clock do GPIOB
            GPIO_Pin_Mode(GPIOB, channels[i] - 8, ANALOG);	//configura o pino (PBx - 8) como analógico
        }
        else if(channels[i] >= 10 && channels[i] <= 15)
        {
            GPIO_Clock_Enable(GPIOC);						//habilita o clock do GPIOC
            GPIO_Pin_Mode(GPIOC, channels[i] - 10, ANALOG);	//configura o pino (PCx - 10) como analógico
        }
    }

    //Configuração do sequenciador do ADC com os canais selecionados
    int deslocamento = 0;
    for (int i = 0; i < numChannels; i++)
    {
        if(i < 6)
        {
            ADCx->SQR3 &= ~(0x1F << (i * 5));		//limpa os bits do campo do canal
            ADCx->SQR3 |= (channels[i] << (i * 5));	//configura o canal na posição do registrador
        }
        else if(i < 12)
        {
            deslocamento = (i - 6) * 5;
            ADCx->SQR2 &= ~(0x1F << deslocamento);			//limpa os bits do campo do canal
            ADCx->SQR2 |= (channels[i] << deslocamento);	//configura o canal na posição
        }
        else
        {
            deslocamento = (i - 12) * 5;
            ADCx->SQR1 &= ~(0x1F << deslocamento); 			//limpa os bits do campo do canal
            ADCx->SQR1 |= (channels[i] << deslocamento);	//configura o canal na posição
        }
    }

    //Define a quantidade de conversões no sequenciador
    ADCx->SQR1 &= ~(0xF << 20);				//limpa o campo de bits
    ADCx->SQR1 |= (numChannels - 1) << 20;	//escreve a quantidade de canais a ser convertido
}

//Realiza a conversão de múltiplos canais e armazena os resultados.
//Lê os valores convertidos pelo ADC para cada canal configurado no sequenciador.
//@param  ADCx: onde x pode ser 1, 2 ou 3 para selecionar o ADC.
//@param  numChannels: quantidade de canais a serem convertidos.
//@param  results: ponteiro do array onde os resultados serão armazenados.
void ADC_GetMultiConversions(ADC_TypeDef *ADCx, uint8_t numChannels, uint16_t *results)
{
    ADCx->CR2 |= ADC_CR2_SWSTART;  			//inicia a sequência de conversão
    for (int i = 0; i < numChannels; i++)
    {
        while (!(ADCx->SR & ADC_SR_EOC)); 	//aguarda o fim da conversão
        results[i] = ADCx->DR;            	//armazena o valor convertido no array
	}
}









//Funções de periféricos de comunicação
//Configuração básica da USART1
void USART1_Init(void)
{
	//Configuração da USART1
	RCC->APB2ENR |= RCC_APB2ENR_USART1EN;				//habilita o clock da USART1
	USART1->BRR = 84;									//ajusta baud rate para 1 Mbps (frequência do periférico de 84MHz)
	//O estado default do registrador USART1->CR1 garante:
	//1 stop bit, 8 bits de dados, sem bit de paridade,
	//oversampling de 16 amostras por bit
	USART1->CR1 |= (USART_CR1_TE | USART_CR1_UE);		//habilita apenas o transmissor e a USART1
	//USART1->CR1 |= (USART_CR1_TE | USART_CR1_RE | USART_CR1_RXNEIE | USART_CR1_UE);	//habilita o transmissor, receptor, interrupção de RX e a USART1

	//Habilita a interrupção da USART1 no NVIC
	//NVIC_SetPriority(USART1_IRQn, 0);	//seta a prioridade da USART1
	//NVIC_EnableIRQ(USART1_IRQn);		//habilita a interrupção da USART1

	//Configuração dos pinos PA9 (TX) e PA10(RX)
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;			//habilita o clock do GPIOA
	GPIOA->MODER |= (0b10 << 20) | (0b10 << 18);	//pinos PA10 e PA9 em função alternativa
	GPIOA->AFR[1] |= (0b0111 << 8) | (0b0111 << 4);	//função alternativa 7 (USART1)
}

//Redefinição da função de envio de dados pela USART1
int __io_putchar(int ch)
{
	USART1->DR = ch;						//transmite o dado
	while (!(USART1->SR & USART_SR_TXE));	//espera pelo fim da transmissão
	return ch;
}

//Redefinição da função de recebimento de dados pela USART1
int __io_getchar(void)
{
   return (uint16_t)(USART1->DR);	//lê o dado recebido
}

//ISR da USART1. Todas as ISR's estão definidas no arquivo startup_stm32f407vetx.s
void USART1_IRQHandler(void)
{
	__io_putchar(__io_getchar());	//lê o dado e reenvia pela USART1
}



//Funções de geração de números aleatórios
//Retorna um número aleatório de 32 bits
uint32_t Random_Number(void)
{
	RCC->AHB2ENR |= RCC_AHB2ENR_RNGEN;	//habilita o clock do RNG
	RNG->CR |= RNG_CR_RNGEN;			//liga o RNG
	while(!(RNG->SR & RNG_SR_DRDY));	//aguarda um número aleatório estar pronto
	(void)RNG->DR;						//despreza o primeiro número aleatório gerado
	while(!(RNG->SR & RNG_SR_DRDY));	//aguarda novo número aleatório estar pronto
	RNG->CR &= ~RNG_CR_RNGEN;			//desliga o RNG
	return RNG->DR;						//retorna o número aleatório
}


#endif /* UTILITY_H_ */
