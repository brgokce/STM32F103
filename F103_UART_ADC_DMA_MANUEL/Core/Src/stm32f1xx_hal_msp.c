/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : stm32f1xx_hal_msp.c
  * Description        : This file provides code for the MSP Initialization 
  *                      and de-Initialization codes.
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
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN TD */
extern DMA_HandleTypeDef dma_usart1_tx;
extern DMA_HandleTypeDef dma_adc1;
/* USER CODE END TD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN Define */
 
/* USER CODE END Define */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN Macro */

/* USER CODE END Macro */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* External functions --------------------------------------------------------*/
/* USER CODE BEGIN ExternalFunctions */

/* USER CODE END ExternalFunctions */

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */
/**
  * Initializes the Global MSP.
  */
void HAL_MspInit(void)
{
  /* USER CODE BEGIN MspInit 0 */

  /* USER CODE END MspInit 0 */

  __HAL_RCC_AFIO_CLK_ENABLE();
  __HAL_RCC_PWR_CLK_ENABLE();

  /* System interrupt init*/

  /** NOJTAG: JTAG-DP Disabled and SW-DP Enabled 
  */
  __HAL_AFIO_REMAP_SWJ_NOJTAG();

  /* USER CODE BEGIN MspInit 1 */

  /* USER CODE END MspInit 1 */
}

/* USER CODE BEGIN 1 */
void HAL_UART_MspInit(UART_HandleTypeDef *huart)
{
	__HAL_RCC_USART1_CLK_ENABLE();

	/*usart1 A9 TX
	 * usart2 A10 RX
	 */
	__HAL_RCC_GPIOA_CLK_ENABLE();
	GPIO_InitTypeDef UartPinTanimla = {0};
	UartPinTanimla.Pin = GPIO_PIN_9;
	UartPinTanimla.Mode = GPIO_MODE_AF_PP;
	UartPinTanimla.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(GPIOA, &UartPinTanimla);

	UartPinTanimla.Pin = GPIO_PIN_10;
	UartPinTanimla.Mode = GPIO_MODE_INPUT;
	HAL_GPIO_Init(GPIOA, &UartPinTanimla);

	// Kesme önceliklendirilmesi ve kesme etkinleştirilmesi
	 HAL_NVIC_SetPriority(USART1_IRQn, 0, 1);
	 HAL_NVIC_EnableIRQ(USART1_IRQn);

	 dma_usart1_tx.Instance= DMA1_Channel4;
	 dma_usart1_tx.Init.Direction=DMA_MEMORY_TO_PERIPH;
	 dma_usart1_tx.Init.MemDataAlignment=DMA_MDATAALIGN_BYTE;
	 dma_usart1_tx.Init.MemInc=DMA_MINC_ENABLE;
	 dma_usart1_tx.Init.Mode= DMA_CIRCULAR;
	 dma_usart1_tx.Init.PeriphDataAlignment=DMA_PDATAALIGN_BYTE;
	 dma_usart1_tx.Init.PeriphInc=DMA_PINC_DISABLE;
	 dma_usart1_tx.Init.Priority=DMA_PRIORITY_MEDIUM;
	 if(HAL_DMA_Init(&dma_usart1_tx) != HAL_OK)
	 {
		 Error_Handler();
	 }
	 __HAL_LINKDMA(huart, hdmatx, dma_usart1_tx);
}

/**
  * @brief  UART MSP DeInit.
  * @param  huart  Pointer to a UART_HandleTypeDef structure that contains
  *                the configuration information for the specified UART module.
  * @retval None
  */
void HAL_UART_MspDeInit(UART_HandleTypeDef *huart)
{
	__HAL_RCC_USART1_CLK_DISABLE();
	HAL_GPIO_DeInit(GPIOA, GPIO_PIN_9 | GPIO_PIN_10);
}

 void HAL_ADC_MspInit(ADC_HandleTypeDef* hadc)
{
	 GPIO_InitTypeDef ADC_Pinleri = {0};
	 __HAL_RCC_ADC1_CLK_ENABLE();
	 __HAL_RCC_GPIOA_CLK_ENABLE();
	 ADC_Pinleri.Pin = GPIO_PIN_1 | GPIO_PIN_2 |GPIO_PIN_3;
	 ADC_Pinleri.Mode = GPIO_MODE_ANALOG;
	 HAL_GPIO_Init(GPIOA, &ADC_Pinleri);

	 HAL_NVIC_SetPriority(ADC1_2_IRQn, 0, 1);
	 HAL_NVIC_EnableIRQ(ADC1_2_IRQn);

	 dma_adc1.Instance= DMA1_Channel1;
	 dma_adc1.Init.Direction=DMA_PERIPH_TO_MEMORY;
	 dma_adc1.Init.MemDataAlignment=DMA_MDATAALIGN_WORD;
	 dma_adc1.Init.MemInc=DMA_MINC_ENABLE;
	 dma_adc1.Init.Mode= DMA_CIRCULAR;
	 dma_adc1.Init.PeriphDataAlignment=DMA_PDATAALIGN_WORD;
	 dma_adc1.Init.PeriphInc=DMA_PINC_DISABLE;
	 dma_adc1.Init.Priority=DMA_PRIORITY_LOW;
	 if(HAL_DMA_Init(&dma_adc1) != HAL_OK)
	 {
		 Error_Handler();
	 }
	 __HAL_LINKDMA(hadc, DMA_Handle, dma_adc1);
}

/**
  * @brief  DeInitializes the ADC MSP.
  * @param  hadc: ADC handle
  * @retval None
  */
 void HAL_ADC_MspDeInit(ADC_HandleTypeDef* hadc)
{
	 HAL_GPIO_DeInit(GPIOA, GPIO_PIN_1 | GPIO_PIN_2 |GPIO_PIN_3);
	 HAL_DMA_DeInit(hadc-> DMA_Handle);
	 HAL_NVIC_DisableIRQ(ADC1_2_IRQn);
}


/* USER CODE END 1 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
