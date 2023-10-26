/*
 * @Author: PapillonAz 1065940593@q.com
 * @Date: 2023-10-25 20:56:10
 * @LastEditors: PapillonAz 1065940593@q.com
 * @LastEditTime: 2023-10-26 17:53:01
 * @FilePath: /IWDG_demo/src/main.c
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include "main.h"
#include "systemclock.h"
#include "gpio.h"
#include "usart.h"
#include "wwdg.h"


int main(){
    // 外设 闪存 系统tick
    HAL_Init();

    // clock
    SystemClock_Config();

    // 外设
    GPIO_Init();
    USART1_UART_Init();

    /* 代码逻辑 */
    if(__HAL_RCC_GET_FLAG(RCC_FLAG_WWDGRST) != RESET ){
        HAL_UART_Transmit(&huart1, "窗口看门狗复位\r\n", strlen("窗口看门狗复位\r\n"), 1000);
        __HAL_RCC_CLEAR_RESET_FLAGS();
    }
    else{
        HAL_UART_Transmit(&huart1, "外部复位\r\n", strlen("外部复位\r\n"), 1000);
    }

    HAL_Delay(1000);
    HAL_UART_Transmit(&huart1, "WWDG: 请喂狗!\r\n", strlen("WWDG: 请喂狗!\r\n"), 1000);
    /**
      * 29ms    内喂狗会产生复位
      * 29-58ms 喂狗不会产生复位
      * 在58ms 之后 也会产生复位  
      */
    WWDG_Init(0x7f, 0x5f, WWDG_PRESCALER_8);
    while(1){
        HAL_Delay(60);

        // HAL_WWDG_Refresh(&WWDG_HandleStruct);    // 在中断服务函数中喂狗，同样地效果
    
        HAL_UART_Transmit(&huart1, "WWDG: 已经在窗口器内喂狗!\r\n", strlen("WWDG: 已经在窗口器内喂狗!\r\n"), 1000);
    }
}
