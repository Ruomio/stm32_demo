/*
 * @Author: Ruomio 1065940593@qq.com
 * @Date: 2024-03-27 16:03:16
 * @LastEditors: Ruomio 1065940593@qq.com
 * @LastEditTime: 2024-03-27 20:09:27
 * @FilePath: /OV7670_demo/include/ov7670.h
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#ifndef __OV7670_H__
#define __OV7670_H__

#include "main.h"


#define CHANGE_REG_NUM 							171			        //需要配置的寄存器总数		
extern const uint8_t ov7670_init_reg_tbl[CHANGE_REG_NUM][2];		//寄存器及其配置表

uint8_t ov7670_init();

#endif