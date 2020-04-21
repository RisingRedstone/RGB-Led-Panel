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
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "usb_device.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "Bitmaps.c"
#include <stdlib.h>
#include "../MDK-ARM/HemGfxWrapper.h"
#include <stdlib.h>
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
SPI_HandleTypeDef hspi2;

TIM_HandleTypeDef htim2;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_SPI2_Init(void);
static void MX_TIM2_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

const uint8_t Sequence[64] = {
  0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87,
  0x07, 0x06, 0x05, 0x04, 0x03, 0x02, 0x01, 0x00,
  0x88, 0x89, 0x8A, 0x8B, 0x8C, 0x8D, 0x8E, 0x8F,
  0x0F, 0x0E, 0x0D, 0x0C, 0x0B, 0x0A, 0x09, 0x08,
  0x90, 0x91, 0x92, 0x93, 0x94, 0x95, 0x96, 0x97,
  0x17, 0x16, 0x15, 0x14, 0x13, 0x12, 0x11, 0x10,
  0x98, 0x99, 0x9A, 0x9B, 0x9C, 0x9D, 0x9E, 0x9F,
  0x1F, 0x1E, 0x1D, 0x1C, 0x1B, 0x1A, 0x19, 0x18
};

const uint16_t BrightnessTimestep[16] = {
	0x0000,
	0x0001,
	0x0101,
	0x0111,
	0x1111,
	0x1115,
	0x1515,
	0x1555,
	0x5555,
	0x555D,
	0x5D5D,
	0x5DDD,
	0x7DDD,
	0x7DDF,
	0x7FDF,
	0x7FFF
};

uint16_t *MarioVid[2];

const uint8_t ra[] = {0, 1, 0, 1};
const uint8_t rb[] = {0, 0, 1, 1};

uint16_t map1[512];
uint16_t map2[512];
uint8_t count = 0;

HemGfx_t *h_Gfx;
bool Ready = true;

void WritePin1(uint8_t);
void uploadMatrix1(void);
void uploadMatrix2(void);
void uploadMatrix3(void);

void HemWriteImage(uint16_t *image, int16_t x, int16_t y){
	HemdrawImage(h_Gfx, (image + 2), image[0], image[1], x, y);
}

void SwitchBuffer(HemGfx_t *h_gfx, bool copy, bool ready){
	while(ready == false)
		__NOP();
	
	HemSwitchBuff(h_Gfx, copy);
}

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
	h_Gfx = newHemGfx(32, 16, (uint16_t *)map1, (uint16_t *)map2);
	
	MarioVid[0] = (uint16_t *)MarioVid2;
	MarioVid[1] = (uint16_t *)MarioVid4;
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
  MX_SPI2_Init();
  MX_USB_DEVICE_Init();
  MX_TIM2_Init();
  /* USER CODE BEGIN 2 */
	
	HAL_TIM_Base_Start_IT(&htim2);
	int16_t temp1 = 0;
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
		int16_t temp0;
		for(temp0 = 0; temp0 < 2; temp0++){
			if(temp1 > 32)
				temp1 = -11;
			
			HAL_Delay(100);
			HAL_GPIO_TogglePin(Led_out_GPIO_Port, Led_out_Pin);
			HemClearScreen(h_Gfx);
			HemWriteImage(MarioVid[temp0], temp1, (1 - temp0));
			SwitchBuffer(h_Gfx, true, Ready);
			temp1 += ((temp0 == 0) ? 4 : 3);
		}
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
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

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
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USB;
  PeriphClkInit.UsbClockSelection = RCC_USBCLKSOURCE_PLL_DIV1_5;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief SPI2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI2_Init(void)
{

  /* USER CODE BEGIN SPI2_Init 0 */

  /* USER CODE END SPI2_Init 0 */

  /* USER CODE BEGIN SPI2_Init 1 */

  /* USER CODE END SPI2_Init 1 */
  /* SPI2 parameter configuration*/
  hspi2.Instance = SPI2;
  hspi2.Init.Mode = SPI_MODE_SLAVE;
  hspi2.Init.Direction = SPI_DIRECTION_2LINES_RXONLY;
  hspi2.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi2.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi2.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi2.Init.NSS = SPI_NSS_SOFT;
  hspi2.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_2;
  hspi2.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi2.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi2.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi2.Init.CRCPolynomial = 10;
  if (HAL_SPI_Init(&hspi2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI2_Init 2 */

  /* USER CODE END SPI2_Init 2 */

}

/**
  * @brief TIM2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM2_Init(void)
{

  /* USER CODE BEGIN TIM2_Init 0 */

  /* USER CODE END TIM2_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM2_Init 1 */

  /* USER CODE END TIM2_Init 1 */
  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 7200;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 200;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM2_Init 2 */

  /* USER CODE END TIM2_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(Led_out_GPIO_Port, Led_out_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, A_pin_Pin|B_pin_Pin|OE_pin_Pin|LAT_pin_Pin 
                          |CLK_pin_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, R1_pin_Pin|B1_pin_Pin|G1_pin_Pin|R2_pin_Pin 
                          |B2_pin_Pin|G2_pin_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : Led_out_Pin */
  GPIO_InitStruct.Pin = Led_out_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(Led_out_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : A_pin_Pin B_pin_Pin OE_pin_Pin LAT_pin_Pin 
                           CLK_pin_Pin */
  GPIO_InitStruct.Pin = A_pin_Pin|B_pin_Pin|OE_pin_Pin|LAT_pin_Pin 
                          |CLK_pin_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : R1_pin_Pin B1_pin_Pin G1_pin_Pin R2_pin_Pin 
                           B2_pin_Pin G2_pin_Pin */
  GPIO_InitStruct.Pin = R1_pin_Pin|B1_pin_Pin|G1_pin_Pin|R2_pin_Pin 
                          |B2_pin_Pin|G2_pin_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){
	if(htim == &htim2){
		uploadMatrix3();
	}
}

void uploadMatrix3(){
	//HAL_TIM_Base_Stop_IT(&htim2);
	Ready = false;
	uint8_t row;
	for(row = 0; row < 4; row ++){
		HAL_GPIO_WritePin(A_pin_GPIO_Port, (A_pin_Pin * ra[row]) | (B_pin_Pin * rb[row]), GPIO_PIN_SET);
		HAL_GPIO_WritePin(A_pin_GPIO_Port, (A_pin_Pin * !ra[row]) | (B_pin_Pin * !rb[row]), GPIO_PIN_RESET);
		
		for(count = 0; count < 16; count++){
				
			HAL_GPIO_WritePin(A_pin_GPIO_Port, (A_pin_Pin * ra[row]) | (B_pin_Pin * rb[row]), GPIO_PIN_SET);
			HAL_GPIO_WritePin(A_pin_GPIO_Port, (A_pin_Pin * !ra[row]) | (B_pin_Pin * !rb[row]), GPIO_PIN_RESET);
			
			WritePin1(row);
				
			HAL_GPIO_WritePin(LAT_pin_GPIO_Port, LAT_pin_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(LAT_pin_GPIO_Port, LAT_pin_Pin, GPIO_PIN_RESET);
			
			HAL_GPIO_WritePin(OE_pin_GPIO_Port, OE_pin_Pin, GPIO_PIN_RESET);
			uint16_t q;
			for(q = 0;q < 20; q++)
				__NOP();
			HAL_GPIO_WritePin(OE_pin_GPIO_Port, OE_pin_Pin, GPIO_PIN_SET);
		}
	}
	Ready = true;
	//HAL_TIM_Base_Start_IT(&htim2);
}

void WritePin1(uint8_t row){
	uint8_t R = (row << 5);
	uint8_t i;
	uint16_t pos;
	
	uint16_t T;
	uint16_t B;
	uint8_t count_t = 1 << count;
	
	uint16_t pinData;
	
	uint16_t pinCount = R1_pin_Pin | B1_pin_Pin | G1_pin_Pin | R2_pin_Pin | B2_pin_Pin | G2_pin_Pin;
	
	uint16_t* buffer = HemGetBuffer(h_Gfx);
	for(i = 0;i < 64; i++){
		pos = Sequence[i] + R;
		T = *(buffer + pos);
		B = *(buffer + pos + 256);
		
		pinData = 0x0000;
		pinData |= (R1_pin_Pin * !!(BrightnessTimestep[((T & 0x0F00) >> 8)] & count_t));
		pinData |= (B1_pin_Pin * !!(BrightnessTimestep[(T & 0x000F)] & count_t));
		pinData |= (G1_pin_Pin * !!(BrightnessTimestep[((T & 0x00F0) >> 4)] & count_t));
		pinData |= (R2_pin_Pin * !!(BrightnessTimestep[((B & 0x0F00) >> 8)] & count_t));
		pinData |= (B2_pin_Pin * !!(BrightnessTimestep[(B & 0x000F)] & count_t));
		pinData |= (G2_pin_Pin * !!(BrightnessTimestep[((B & 0x00F0) >> 4)] & count_t));
		
		HAL_GPIO_WritePin(R1_pin_GPIO_Port, pinData, GPIO_PIN_SET);
		HAL_GPIO_WritePin(R1_pin_GPIO_Port, (~pinData & pinCount), GPIO_PIN_RESET);
		
		HAL_GPIO_WritePin(CLK_pin_GPIO_Port, CLK_pin_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(CLK_pin_GPIO_Port, CLK_pin_Pin, GPIO_PIN_RESET);
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
