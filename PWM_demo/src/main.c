/*
 * @Author: PapillonAz 1065940593@q.com
 * @Date: 2023-10-25 20:56:10
 * @LastEditors: PapillonAz 1065940593@q.com
 * @LastEditTime: 2023-10-26 16:04:33
 * @FilePath: /IWDG_demo/src/main.c
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include "main.h"
#include "systemclock.h"
#include "gpio.h"
#include "usart.h"
#include "gtim.h"


int main(){
    // 外设 闪存 系统tick
    HAL_Init();

    // clock
    SystemClock_Config();

    // 外设
    GPIO_Init();
    USART1_UART_Init();

    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, RESET);

    uint8_t mess[] = "请喂狗!\r\n";
    HAL_UART_Transmit(&huart1, mess, sizeof(mess), 1000);
    // ARR 499 PSC 71  --> T_out = 2kHz
    gtim_timx_pwn_chy_init(71, 499);

    uint16_t led_rpm_val = 0;
    uint8_t dir = 1;
    while(1){
        HAL_Delay(10);
        // HAL_UART_Transmit(&huart1, "38line!\r\n", sizeof("38line!\r\n"), 1000);
        if(dir) led_rpm_val++;
        else led_rpm_val--;

        if(led_rpm_val > 300) dir=0;
        if(led_rpm_val == 0) dir=1;
        __HAL_TIM_SET_COMPARE(&g_timx_pwm_chy_handle, TIM_CHANNEL_2, led_rpm_val);
    }
}
