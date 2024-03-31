/*
 * @Author: Ruomio 1065940593@qq.com
 * @Date: 2024-03-26 20:29:34
 * @LastEditors: Ruomio 1065940593@qq.com
 * @LastEditTime: 2024-03-31 19:25:52
 * @FilePath: /OV7670_demo/src/main.c
 * @Description: 使用 I2C来兼容SCCB通讯
 */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "sys.h"
#include "i2c.h"
#include "sccb.h"
#include "usart.h"
#include "gpio.h"
#include "ov7670.h"
#include "system_clock.h"
#include "systick.h"
#include "stm32f1xx_it.h"



extern uint8_t Receive[1];


uint8_t Call[] = "CallBack\r\n";

/**
 * @brief  The application entry point.
 * @retval int
 */
int main(void)
{

    HAL_Init();

    SystemClock_Config();

    // delay_init();

    MX_GPIO_Init();
    
    // MX_I2C1_Init();

    MX_USART1_UART_Init();
    HAL_Delay(20);
    // MX_USART2_UART_Init();
    /* USER CODE BEGIN 2 */

    HAL_Delay(20);
    // OLED_Init();
    //  OLED_Test();

    // HAL_UARTEx_ReceiveToIdle_IT(&huart1, Receive, sizeof(Receive));
    // HAL_UARTEx_ReceiveToIdle_IT(&huart2, Receive, sizeof(Receive));
    // HAL_UART_Receive_IT(&huart1, Receive, sizeof(Receive));
    // HAL_UART_Receive_IT(&huart2, Receive, sizeof(Receive));
    /* USER CODE END 2 */
    char tmp[] = "Hello\r\n";
    HAL_UART_Transmit_IT(&huart1,(uint8_t*)tmp, sizeof(tmp));
    // HAL_UART_Transmit_IT(&huart2,(uint8_t*)tmp, sizeof(tmp));
    int res = ov7670_init();
    printf("res code = %d\r\n", res);
    /* Infinite loop */
    /* USER CODE BEGIN WHILE */
    // Sccb_init();
    // MX_I2C1_Init();


    while (1)
    {
        delay_ms(500);
        HAL_Delay(500);
        HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
        // Sccb_sda_output();
        // HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_7);
        // printf("PB7 = %d\r\n", SCCB_SDA_STATE);
        // printf("PC13 = %d\r\n", HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13));
        // for (int i = 0; i < 64; i++)
        // {
        //     OLED_NewFrame();
        //     OLED_DrawCircle(64, 32, i, OLED_COLOR_NORMAL);
        //     OLED_DrawCircle(64, 32, 2 * i, OLED_COLOR_NORMAL);
        //     OLED_DrawCircle(64, 32, 3 * i, OLED_COLOR_NORMAL);
        //     OLED_ShowFrame();
        // }
        /* USER CODE END WHILE */

        /* USER CODE BEGIN 3 */
    }
    /* USER CODE END 3 */
}



/* USER CODE BEGIN 4 */

/* USER CODE END 4 */


