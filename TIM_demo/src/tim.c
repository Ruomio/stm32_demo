/*
 * @Author: PapillonAz 1065940593@q.com
 * @Date: 2023-10-29 14:41:02
 * @LastEditors: PapillonAz 1065940593@q.com
 * @LastEditTime: 2023-10-29 15:42:27
 * @FilePath: /TIM_demo/src/tim.c
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include "tim.h"
#include "usart.h"
TIM_HandleTypeDef tim_HandleX = {0};

void TIM_GENERAL_Init(uint16_t psc, uint16_t arr){

    tim_HandleX.Instance = TIM2;
    tim_HandleX.Init.CounterMode = TIM_COUNTERMODE_UP;
    tim_HandleX.Init.Prescaler = psc;
    tim_HandleX.Init.Period = arr;
    tim_HandleX.Init.ClockDivision = TIM_CLOCKPRESCALER_DIV1;
    tim_HandleX.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;

    HAL_TIM_Base_Init(&tim_HandleX);

    HAL_TIM_Base_Start_IT(&tim_HandleX);
}

void HAL_TIM_Base_MspInit(TIM_HandleTypeDef *htim) {
    if(htim->Instance == TIM2) {
        
        __HAL_RCC_TIM2_CLK_ENABLE();

        HAL_NVIC_SetPriority(TIM2_IRQn, 0, 0);
        HAL_NVIC_EnableIRQ(TIM2_IRQn);

        
    }
}


/* 中断写到了 it.c 中 */

// 回调
uint8_t cnt = 0;
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
    if( htim->Instance == TIM2) {
        
        if( __HAL_TIM_GET_ITSTATUS(&tim_HandleX, TIM_IT_UPDATE) == SET) {
            __HAL_TIM_CLEAR_IT(&tim_HandleX, TIM_IT_UPDATE);
            HAL_UART_Transmit(&huart1, "程序进入回调!!\r\n", strlen("程序进入回调!!\r\n"), 20);

            cnt++;
            if(cnt > 50 ) {
                HAL_UART_Transmit(&huart1, "反转led!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\r\n", strlen("反转led!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\r\n"),20);
                HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
                cnt = 0;
            }

            
        }
    }
}
