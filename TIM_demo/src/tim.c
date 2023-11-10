/*
 * @Author: PapillonAz 1065940593@q.com
 * @Date: 2023-10-29 14:41:02
 * @LastEditors: PapillonAz 1065940593@q.com
 * @LastEditTime: 2023-10-29 15:42:27
 * @FilePath: /TIM_demo/src/tim.c
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include "tim.h"

TIM_HandleTypeDef tim_HandleX;

void TIM_GENERAL_Init(uint16_t psc, uint16_t period){
    
    

    tim_HandleX.Instance = TIM2;
    tim_HandleX.Init.CounterMode = TIM_COUNTERMODE_UP;
    tim_HandleX.Init.Prescaler = psc;
    tim_HandleX.Init.Period = period;
    tim_HandleX.Init.ClockDivision = TIM_CLOCKPRESCALER_DIV1;

    HAL_TIM_Base_Init(&tim_HandleX);

    __HAL_RCC_TIM2_CLK_ENABLE();
    HAL_NVIC_SetPriority(TIM2_IRQn, 8, 0);
    HAL_NVIC_EnableIRQ(TIM2_IRQn);

    HAL_TIM_Base_Start_IT(&tim_HandleX);
}


/* 中断写到了 it.c 中 */

// 回调
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
    if( htim->Instance == &tim_HandleX) {
        HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
    }
}