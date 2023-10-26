#ifndef __WWDG_H__
#define __WWDG_H__

#include "main.h"

extern WWDG_HandleTypeDef WWDG_HandleStruct;

void WWDG_Init(uint8_t tr, uint8_t wr, uint32_t fprer);

// void HAL_WWDG_MspInit(WWDG_HandleTypeDef *hwwdg);

// void WWDG_IRQHandler();

#endif