/*
 * @Author: PapillonAz 1065940593@q.com
 * @Date: 2023-10-25 20:56:10
 * @LastEditors: PapillonAz 1065940593@q.com
 * @LastEditTime: 2023-10-25 23:03:59
 * @FilePath: /IWDG_demo/src/main.c
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include "main.h"
#include "systemclock.h"
#include "gpio.h"
#include "usart.h"


int main(){
    // 外设 闪存 系统tick
    HAL_Init();

    // clock
    SystemClock_Config();
    USART1_UART_Init();

    // 外设
    GPIO_Init();
    USART1_UART_Init();

    const uint8_t mess[] = "hello world!\r\n";
    while(1){
        HAL_Delay(1000);
        HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
        HAL_UART_Transmit(&huart1, mess, sizeof(mess), 1000);
    }
}
