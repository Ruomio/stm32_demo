/*
 * @Author: PapillonAz 1065940593@q.com
 * @Date: 2023-10-26 16:11:30
 * @LastEditors: PapillonAz 1065940593@q.com
 * @LastEditTime: 2023-10-29 15:43:40
 * @FilePath: /WWDG_demo/src/wwdg.c
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include "wwdg.h"
#include "usart.h"

WWDG_HandleTypeDef WWDG_HandleStruct;
/* 初始化函数 */
void WWDG_Init(uint8_t tr, uint8_t wr, uint32_t fprer){

    
    WWDG_HandleStruct.Instance = WWDG;
    WWDG_HandleStruct.Init.Counter = tr;
    WWDG_HandleStruct.Init.Window = wr;
    WWDG_HandleStruct.Init.Prescaler = fprer;
    WWDG_HandleStruct.Init.EWIMode = WWDG_EWI_ENABLE;

    HAL_WWDG_Init(&WWDG_HandleStruct);
}

/*  回调函数 */
void HAL_WWDG_MspInit(WWDG_HandleTypeDef *hwwdg){
    __HAL_RCC_WWDG_CLK_ENABLE();

    HAL_NVIC_SetPriority(WWDG_IRQn, 4, 0);
    HAL_NVIC_EnableIRQ(WWDG_IRQn);
}

/* 中断服务函数 写在 it.c中 */


/* 提前唤醒函数  递减到0x40(64时产生中断) */
void HAL_WWDG_EarlyWakeupCallback(WWDG_HandleTypeDef *hwwdg){
    HAL_WWDG_Refresh(&WWDG_HandleStruct);
    HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
    HAL_UART_Transmit(&huart1, "WWDG:进入提前唤醒回调函数!\r\n", strlen("WWDG:进入提前唤醒回调函数!\r\n"), 1000);
}