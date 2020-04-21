/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define Led_out_Pin GPIO_PIN_13
#define Led_out_GPIO_Port GPIOC
#define A_pin_Pin GPIO_PIN_1
#define A_pin_GPIO_Port GPIOA
#define B_pin_Pin GPIO_PIN_2
#define B_pin_GPIO_Port GPIOA
#define OE_pin_Pin GPIO_PIN_3
#define OE_pin_GPIO_Port GPIOA
#define LAT_pin_Pin GPIO_PIN_4
#define LAT_pin_GPIO_Port GPIOA
#define CLK_pin_Pin GPIO_PIN_5
#define CLK_pin_GPIO_Port GPIOA
#define R1_pin_Pin GPIO_PIN_3
#define R1_pin_GPIO_Port GPIOB
#define B1_pin_Pin GPIO_PIN_4
#define B1_pin_GPIO_Port GPIOB
#define G1_pin_Pin GPIO_PIN_5
#define G1_pin_GPIO_Port GPIOB
#define R2_pin_Pin GPIO_PIN_6
#define R2_pin_GPIO_Port GPIOB
#define B2_pin_Pin GPIO_PIN_7
#define B2_pin_GPIO_Port GPIOB
#define G2_pin_Pin GPIO_PIN_8
#define G2_pin_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
