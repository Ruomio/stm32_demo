/*
 * @Author: PapillonAz 1065940593@q.com
 * @Date: 2023-10-25 22:33:47
 * @LastEditors: PapillonAz 1065940593@q.com
 * @LastEditTime: 2023-10-25 22:48:00
 * @FilePath: /IWDG_demo/include/uart.h
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#ifndef __USART_H__
#define __USART_H__

#include "main.h"

extern UART_HandleTypeDef huart1;

void USART1_UART_Init(void);

#endif