#ifndef _GTIM_H__
#define _GTIM_H__

#include "main.h"

extern TIM_HandleTypeDef htimx;

void gtimx_Init(uint8_t psc, uint16_t arr);

#endif //_GTIM_H__