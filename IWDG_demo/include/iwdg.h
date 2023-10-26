/*
 * @Author: PapillonAz 1065940593@q.com
 * @Date: 2023-10-25 23:05:59
 * @LastEditors: PapillonAz 1065940593@q.com
 * @LastEditTime: 2023-10-25 23:18:39
 * @FilePath: /IWDG_demo/include/iwdg.h
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#ifndef __IWDG_H__
#define __IWDG_H__

#include "main.h"

void IWDG_Init(uint8_t prer, uint16_t rlr);
void IWDG_Refresh();

#endif