#ifndef __GTIM_H__
#define __GTIM_H__

#include "main.h"

extern TIM_HandleTypeDef g_timx_pwm_chy_handle;

void gtim_timx_pwn_chy_init(uint16_t psc, uint16_t arr);
#endif