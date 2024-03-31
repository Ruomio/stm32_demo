/*
 * @Author: Ruomio 1065940593@qq.com
 * @Date: 2024-03-26 21:23:19
 * @LastEditors: Ruomio 1065940593@qq.com
 * @LastEditTime: 2024-03-29 13:36:48
 * @FilePath: /OV7670_demo/include/systick.h
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#ifndef _SYSTICK_H
#define _SYSTICK_H
#include "main.h"

// void delay_init();
void delay_us(uint32_t i);
void delay_ms(uint32_t i);

#endif

