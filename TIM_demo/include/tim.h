#ifndef __TIM_H__
#define __TIM_H__

#include "main.h"

extern TIM_HandleTypeDef tim_HandleX;

void TIM_GENERAL_Init(uint16_t psc, uint16_t period);

#endif