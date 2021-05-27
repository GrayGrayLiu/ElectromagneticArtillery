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
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
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
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "Printf.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
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
#define Key2_Pin GPIO_PIN_2
#define Key2_GPIO_Port GPIOE
#define Key3_Pin GPIO_PIN_3
#define Key3_GPIO_Port GPIOE
#define Key4_Pin GPIO_PIN_4
#define Key4_GPIO_Port GPIOE
#define Key5_Pin GPIO_PIN_5
#define Key5_GPIO_Port GPIOE
#define Key6_Pin GPIO_PIN_6
#define Key6_GPIO_Port GPIOE
#define LED_StepperMotor_Pin GPIO_PIN_15
#define LED_StepperMotor_GPIO_Port GPIOG
#define StepperMotorDirection_Pin GPIO_PIN_3
#define StepperMotorDirection_GPIO_Port GPIOB
#define StepperMotorENABLE_Pin GPIO_PIN_4
#define StepperMotorENABLE_GPIO_Port GPIOB
#define VoltageComparisonInput_Pin GPIO_PIN_8
#define VoltageComparisonInput_GPIO_Port GPIOB
#define ControlRelay_Pin GPIO_PIN_9
#define ControlRelay_GPIO_Port GPIOB
#define Key0_Pin GPIO_PIN_0
#define Key0_GPIO_Port GPIOE
#define Key1_Pin GPIO_PIN_1
#define Key1_GPIO_Port GPIOE
/* USER CODE BEGIN Private defines */
extern uint8_t KeyValue;
/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
