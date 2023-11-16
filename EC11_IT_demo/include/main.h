
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"



void Error_Handler(void);

void delay_ms(uint16_t time);

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
