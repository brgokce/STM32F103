/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "string.h"
#include "stdio.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
UART_HandleTypeDef huart1;
DMA_HandleTypeDef dma_usart1_tx;

ADC_HandleTypeDef hadc1;
DMA_HandleTypeDef dma_adc1;
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
static char* UartTx = "MERHABA UART BASLADI\t\n";
char rxBuffer[4];
char buffer[25];
int ADCValue[3];


/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
/* USER CODE BEGIN PFP */
static void MX_UART_Init(void);
static void MX_DMA_Init(void);
static void MX_ADC1_Init(void);
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

  MX_DMA_Init();

  MX_UART_Init();

  MX_ADC1_Init();

  while(HAL_UART_GetState(&huart1)!= HAL_UART_STATE_READY);
  if(HAL_UART_Transmit_IT(&huart1, (uint8_t *)UartTx, 25)!=HAL_OK){
	  Error_Handler();
  }

  while(HAL_UART_GetState(&huart1)!= HAL_UART_STATE_READY);
  if(HAL_UART_Transmit_DMA(&huart1, (uint8_t *)buffer, strlen(buffer))!=HAL_OK){
	  Error_Handler();
  }

  if(HAL_ADC_Start_DMA(&hadc1, (uint32_t*)ADCValue, 3)!=HAL_OK){
	  Error_Handler();
  }

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
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

  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
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

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();

	GPIO_InitTypeDef PinTanimla = {0};
	PinTanimla.Pin = GPIO_PIN_5 |GPIO_PIN_6 |GPIO_PIN_7;
	PinTanimla.Mode = GPIO_MODE_OUTPUT_PP;
	PinTanimla.Speed = GPIO_SPEED_FREQ_HIGH;
	PinTanimla.Pull  = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOA, &PinTanimla);
}

/* USER CODE BEGIN 4 */
static void MX_UART_Init(void)
{
	huart1.Instance = USART1;
	huart1.Init.BaudRate  = 9600;
	huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	huart1.Init.Mode = UART_MODE_TX_RX ;
	huart1.Init.OverSampling = UART_OVERSAMPLING_16;
	huart1.Init.Parity = UART_PARITY_NONE;
	huart1.Init.StopBits = UART_STOPBITS_1;
	huart1.Init.WordLength = UART_WORDLENGTH_8B;
	if(HAL_UART_Init(&huart1)!= HAL_OK)
	{
		Error_Handler();
	}
}


 void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	  if(HAL_UART_Receive_IT(&huart1, (uint8_t *)rxBuffer, 4)!=HAL_OK){
		  Error_Handler();
	  }
	  if(strncmp (rxBuffer, "LED1", 4)==0){
		  if(HAL_UART_Transmit_IT(&huart1, (uint8_t *)"LED1 YANDI\t\n", 12)!=HAL_OK){
			  Error_Handler();
		  }
		  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_PIN_SET);
		  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, GPIO_PIN_RESET);
	  }
	  else if(strncmp (rxBuffer, "LED2", 4)==0){
		  if(HAL_UART_Transmit_IT(&huart1, (uint8_t *)"LED2 YANDI\t\n", 12)!=HAL_OK){
			  Error_Handler();
		  }
		  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_PIN_RESET);
		  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, GPIO_PIN_SET);
	  }

}

 void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
 {
	 sprintf(buffer,"A1:%4d A2:%4d A3:%4d\r\n", ADCValue[0],ADCValue[1],ADCValue[2]);
 }

 static void MX_DMA_Init(void)
 {
	__HAL_RCC_DMA1_CLK_ENABLE();
	 HAL_NVIC_SetPriority(DMA1_Channel4_IRQn, 0, 0);
	 HAL_NVIC_EnableIRQ(DMA1_Channel4_IRQn);

	 HAL_NVIC_SetPriority(DMA1_Channel1_IRQn, 0, 0);
	 HAL_NVIC_EnableIRQ(DMA1_Channel1_IRQn);
 }


 static void MX_ADC1_Init(void)
 {
	 ADC_ChannelConfTypeDef KanalKonfigurasyonu = {0};

	 hadc1.Instance = ADC1;
	 hadc1.Init.ContinuousConvMode = ENABLE;
	 hadc1.Init.DataAlign=ADC_DATAALIGN_RIGHT;
	 hadc1.Init.DiscontinuousConvMode = DISABLE;
	 hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
	 hadc1.Init.NbrOfConversion = 3;
	 hadc1.Init.NbrOfDiscConversion = 0;
	 hadc1.Init.ScanConvMode = ADC_SCAN_ENABLE;
	 if(HAL_ADC_Init(&hadc1) != HAL_OK)
	 {
		 Error_Handler();
	 }
	 // A1 A2 ve A3 pinleri kullanılacak
	 KanalKonfigurasyonu.Channel = ADC_CHANNEL_1;
	 KanalKonfigurasyonu.Rank = ADC_REGULAR_RANK_1;
	 KanalKonfigurasyonu.SamplingTime = ADC_SAMPLETIME_28CYCLES_5;
	 if(HAL_ADC_ConfigChannel(&hadc1, &KanalKonfigurasyonu) != HAL_OK)
	 {
		 Error_Handler();
	 }

	 KanalKonfigurasyonu.Channel = ADC_CHANNEL_2;
	 KanalKonfigurasyonu.Rank = ADC_REGULAR_RANK_2;
	 KanalKonfigurasyonu.SamplingTime = ADC_SAMPLETIME_28CYCLES_5;
	 if(HAL_ADC_ConfigChannel(&hadc1, &KanalKonfigurasyonu) != HAL_OK)
	 {
		 Error_Handler();
	 }

	 KanalKonfigurasyonu.Channel = ADC_CHANNEL_3;
	 KanalKonfigurasyonu.Rank = ADC_REGULAR_RANK_3;
	 KanalKonfigurasyonu.SamplingTime = ADC_SAMPLETIME_28CYCLES_5;
	 if(HAL_ADC_ConfigChannel(&hadc1, &KanalKonfigurasyonu) != HAL_OK)
	 {
		 Error_Handler();
	 }

 }
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
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
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
