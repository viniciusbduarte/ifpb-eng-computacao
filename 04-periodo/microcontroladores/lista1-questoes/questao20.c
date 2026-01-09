/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "Utility.h"
#include "time.h"
#include "stdio.h"
#include "stdlib.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
int RODADAS = 50;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  /* USER CODE BEGIN 2 */
  Utility_Init();
  GPIO_Clock_Enable(GPIOA);
  GPIO_Clock_Enable(GPIOE);

  // LEDs nas saídas PA2, PA3, PA4, PA5
  uint16_t leds[4] = {PIN_2, PIN_3, PIN_4, PIN_5};
  for (int i = 0; i < 4; i++) {
      GPIO_Pin_Mode(GPIOA, leds[i], OUTPUT);
      GPIO_Write_Pin(GPIOA, leds[i], LOW); // LEDs apagados inicialmente
  }

  // Botões nas entradas PE2, PE3, PE4, PE5 (com pull-up)
  uint16_t botoes[4] = {PIN_2, PIN_3, PIN_4, PIN_5};
  for (int i = 0; i < 4; i++) {
      GPIO_Pin_Mode(GPIOE, botoes[i], INPUT);
      GPIO_Resistor_Enable(GPIOE, botoes[i], PULL_UP);
  }

  // Inicializa gerador aleatório apenas uma vez
  srand(HAL_GetTick());
  uint16_t sequencia[RODADAS];
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
      {
          // Gera uma nova sequência para cada jogo
          for (int i = 0; i < 50; i++) {
              sequencia[i] = Random_Number() % 4;
          }

          int rodada = 0;
          int delayTempo = 400; // tempo base entre piscadas

          while (1) {
              // Mostra sequência até a rodada atual
              for (int i = 0; i <= rodada; i++) {
                  GPIO_Write_Pin(GPIOA, leds[sequencia[i]], HIGH);
                  Delay_ms(delayTempo);
                  GPIO_Write_Pin(GPIOA, leds[sequencia[i]], LOW);
                  Delay_ms(delayTempo / 2);
              }

              // Espera o jogador repetir a sequência
              int n = 0;
              int perdeu = 0;

              while (n <= rodada && !perdeu) {
                  for (int i = 0; i < 4; i++) {
                      if (GPIO_Read_Pin(GPIOE, botoes[i]) == 0) {
                          // Pisca LED correspondente
                          GPIO_Write_Pin(GPIOA, leds[i], HIGH);
                          Delay_ms(200);
                          GPIO_Write_Pin(GPIOA, leds[i], LOW);

                          if (sequencia[n] == i) {
                              n++; // acertou o passo
                          } else {
                              perdeu = 1; // errou
                          }

                          // Espera soltar o botão
                          while (GPIO_Read_Pin(GPIOE, botoes[i]) == 0);
                          Delay_ms(50);
                      }
                  }
              }

              if (perdeu) {
                  // Pisca todos os LEDs 3x
                  for (int j = 0; j < 3; j++) {
                      GPIO_Write_Port(GPIOA, 0b11111100); // pinos 2–5
                      Delay_ms(250);
                      GPIO_Write_Port(GPIOA, 0b00000000);
                      Delay_ms(250);
                  }
                  Delay_ms(500);
                  break; // reinicia o jogo
              }

              rodada++;

              // Acelera a cada rodada
              if (delayTempo > 150) delayTempo -= 25;

              // Vitória se chegar ao fim
              if (rodada >= 50) {
                  for (int j = 0; j < 5; j++) {
                      GPIO_Write_Port(GPIOA, 0b11111100);
                      Delay_ms(150);
                      GPIO_Write_Port(GPIOA, 0b00000000);
                      Delay_ms(150);
                  }
                  break;
              }
          }


    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 168;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  /* USER CODE BEGIN MX_GPIO_Init_1 */

  /* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOH_CLK_ENABLE();

  /* USER CODE BEGIN MX_GPIO_Init_2 */

  /* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}
#ifdef USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
