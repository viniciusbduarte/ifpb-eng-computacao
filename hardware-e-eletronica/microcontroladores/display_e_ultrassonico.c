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
/* USER CODE END Includes */
#include <stdio.h>
#include <string.h>
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





  GPIO_Pin_Mode(GPIOA, PIN_0, OUTPUT);
  GPIO_Pin_Mode(GPIOA, PIN_1, OUTPUT);
  GPIO_Pin_Mode(GPIOA, PIN_2, OUTPUT);
  GPIO_Pin_Mode(GPIOA, PIN_3, OUTPUT);
  GPIO_Pin_Mode(GPIOA, PIN_4, OUTPUT);
  GPIO_Pin_Mode(GPIOA, PIN_5, OUTPUT);
  GPIO_Pin_Mode(GPIOA, PIN_6, OUTPUT);
  GPIO_Pin_Mode(GPIOA, PIN_7, OUTPUT);

  GPIO_Pin_Mode(GPIOA, PIN_12, OUTPUT);
  GPIO_Pin_Mode(GPIOA, PIN_11, OUTPUT);
  GPIO_Pin_Mode(GPIOA, PIN_8, OUTPUT);
  GPIO_Pin_Mode(GPIOA, PIN_15, OUTPUT);


  GPIO_Pin_Mode(GPIOE, PIN_2, INPUT); //echo
  GPIO_Pin_Mode(GPIOE, PIN_3, OUTPUT); //trig


  uint8_t seg[10] = {
    0b0111111, // 0
    0b0000110, // 1
    0b1011011, // 2
    0b1001111, // 3
    0b1100110, // 4
    0b1101101, // 5
    0b1111101, // 6
    0b0000111, // 7
    0b1111111, // 8
    0b1101111  // 9
  };

  GPIO_Write_Pin(GPIOA, PIN_15, HIGH); //d1
  GPIO_Write_Pin(GPIOA, PIN_12, HIGH); //d2
  GPIO_Write_Pin(GPIOA, PIN_11, HIGH); //d3
  GPIO_Write_Pin(GPIOA, PIN_8, HIGH); //d4



  void conversor_d4(float valor_display)
  {
      char buffer[6];
      int d1, d2, d3, d4;


      int valor_inteiro = (int)(valor_display * 100);
      sprintf(buffer, "%04d", valor_inteiro);

      d1 = buffer[0] - '0';
      d2 = buffer[1] - '0';
      d3 = buffer[2] - '0';
      d4 = buffer[3] - '0';

      GPIO_Write_Pin(GPIOA, PIN_15, LOW);
      GPIOA->ODR = (GPIOA->ODR & ~(0xFF)) | seg[d4];
      HAL_Delay(2);
      GPIO_Write_Pin(GPIOA, PIN_15, HIGH);

      GPIO_Write_Pin(GPIOA, PIN_12, LOW);
      GPIOA->ODR = (GPIOA->ODR & ~(0xFF)) | seg[d3];
      HAL_Delay(2);
      GPIO_Write_Pin(GPIOA, PIN_12, HIGH);

      GPIO_Write_Pin(GPIOA, PIN_11, LOW);
      GPIOA->ODR = (GPIOA->ODR & ~(0xFF)) | (seg[d2] | 0x80);
      HAL_Delay(2);
      GPIO_Write_Pin(GPIOA, PIN_11, HIGH);

      GPIO_Write_Pin(GPIOA, PIN_8, LOW);
      GPIOA->ODR = (GPIOA->ODR & ~(0xFF)) | seg[d1];
      HAL_Delay(2);
      GPIO_Write_Pin(GPIOA, PIN_8, HIGH);

  }

  float leitura(void) {
      unsigned long us = 0;
      const unsigned long timeout_us = 30000;

      GPIO_Write_Pin(GPIOE, PIN_3, HIGH);
      Delay_us(10);
      GPIO_Write_Pin(GPIOE, PIN_3, LOW);

      unsigned long count = 0;
      while (!GPIO_Read_Pin(GPIOE, PIN_2)) {
          Delay_us(1);
          if (++count >= timeout_us) return -1.0f;
      }

      while (GPIO_Read_Pin(GPIOE, PIN_2)) {
          Delay_us(1);
          if (++us >= timeout_us) return -1.0f;
      }


      float distancia_cm = us * 0.01715f;

      return distancia_cm;
  }


  float distancia_cm = 0.0;
  int n = 0;
  /* USER CODE END 2 */
  /* Infinite loop */
  /* USER CODE BEGIN WHILE */

  while (1)
  {



	 conversor_d4(distancia_cm);

	 if ( n == 10 ){
		 distancia_cm = leitura();
		 n = 0;
	 }

	 n++;
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
