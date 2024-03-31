/*
 * @Author: Ruomio 1065940593@qq.com
 * @Date: 2024-03-26 20:46:34
 * @LastEditors: Ruomio 1065940593@qq.com
 * @LastEditTime: 2024-03-31 19:04:08
 * @FilePath: /OV7670_demo/include/sccb.h
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#ifndef __SCCB_H__
#define __SCCB_H__

#include "main.h"

#define SCCB_ID 0x42

#define SCCB_SCL_H() HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, GPIO_PIN_SET)
#define SCCB_SCL_L() HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, GPIO_PIN_RESET)
#define SCCB_SDA_H() HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, GPIO_PIN_SET)
#define SCCB_SDA_L() HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, GPIO_PIN_RESET)


#define SCCB_SDA_STATE HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_7)
// #define SCCB_SDA_STATE GPIOB->IDR&GPIO_PIN_7



extern I2C_HandleTypeDef hi2c1;


void Sccb_init();
void Sccb_sda_output();
void Sccb_sda_input();
void StartSCCB();
void StopSCCB();
void NoAck();

uint8_t SCCB_WriteByte(uint8_t m_data);
uint8_t SCCB_ReadByte();

uint8_t SCCB_WriteReg(uint8_t reg, uint8_t data);
uint8_t SCCB_ReadReg(uint8_t reg);

#endif