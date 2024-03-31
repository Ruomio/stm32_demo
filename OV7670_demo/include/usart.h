/*
 * @Author: Ruomio 1065940593@qq.com
 * @Date: 2023-10-29 23:06:12
 * @LastEditors: Ruomio 1065940593@qq.com
 * @LastEditTime: 2024-03-02 21:58:20
 * @FilePath: /Oled_demo/include/usart.h
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    usart.h
  * @brief   This file contains all the function prototypes for
  *          the usart.c file
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
#ifndef __USART_H__
#define __USART_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"



extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart2;



void MX_USART1_UART_Init(void);

void MX_USART2_UART_Init(void);



#ifdef __cplusplus
}
#endif

#endif /* __USART_H__ */

