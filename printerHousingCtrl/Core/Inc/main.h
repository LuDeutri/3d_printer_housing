/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
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

void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define debug_led_Pin GPIO_PIN_13
#define debug_led_GPIO_Port GPIOC
#define btn_PrinterSply_Pin GPIO_PIN_0
#define btn_PrinterSply_GPIO_Port GPIOA
#define btn_led_Pin GPIO_PIN_1
#define btn_led_GPIO_Port GPIOA
#define btn_fire_ExGuisher_Pin GPIO_PIN_2
#define btn_fire_ExGuisher_GPIO_Port GPIOA
#define beeper_Pin GPIO_PIN_4
#define beeper_GPIO_Port GPIOA
#define valve_open_Pin GPIO_PIN_6
#define valve_open_GPIO_Port GPIOA
#define gas_sens_analog_Pin GPIO_PIN_1
#define gas_sens_analog_GPIO_Port GPIOB
#define gas_sens_digital_Pin GPIO_PIN_10
#define gas_sens_digital_GPIO_Port GPIOB
#define printer_sply_ctrl_Pin GPIO_PIN_11
#define printer_sply_ctrl_GPIO_Port GPIOB
#define unused_0_Pin GPIO_PIN_12
#define unused_0_GPIO_Port GPIOA
#define unused_1_Pin GPIO_PIN_15
#define unused_1_GPIO_Port GPIOA
#define unused_2_Pin GPIO_PIN_3
#define unused_2_GPIO_Port GPIOB
#define unused_4_Pin GPIO_PIN_4
#define unused_4_GPIO_Port GPIOB
#define pi_printer_sply_ctrl_Pin GPIO_PIN_6
#define pi_printer_sply_ctrl_GPIO_Port GPIOB
#define pi_led_data_1_Pin GPIO_PIN_7
#define pi_led_data_1_GPIO_Port GPIOB
#define pi_led_data_2_Pin GPIO_PIN_8
#define pi_led_data_2_GPIO_Port GPIOB
#define pi_led_data_3_Pin GPIO_PIN_9
#define pi_led_data_3_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
