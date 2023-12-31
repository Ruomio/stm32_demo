/*
 * @Author: PapillonAz 1065940593@q.com
 * @Date: 2023-10-25 22:34:39
 * @LastEditors: PapillonAz 1065940593@q.com
 * @LastEditTime: 2023-10-25 23:00:15
 * @FilePath: /IWDG_demo/src/uart.c
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include "usart.h"

UART_HandleTypeDef huart1;

void USART1_UART_Init(void){
    huart1.Instance = USART1;
    huart1.Init.BaudRate = 115200;
    huart1.Init.WordLength = UART_WORDLENGTH_8B;
    huart1.Init.StopBits = USART_STOPBITS_1;
    huart1.Init.Parity = UART_PARITY_NONE;
    huart1.Init.Mode = UART_MODE_TX_RX;
    huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    huart1.Init.OverSampling = UART_OVERSAMPLING_16;
    if( HAL_UART_Init(&huart1) != HAL_OK ){
        Error_Handler();
    }   

}

void HAL_UART_MspInit(UART_HandleTypeDef *uartHandle){
    
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    if(uartHandle->Instance == USART1){
        __HAL_RCC_USART1_CLK_ENABLE();
        __HAL_RCC_GPIOA_CLK_ENABLE();

        /** 
         * PA9  -> USART1_TX
         * PA10 -> USART1_RX
         */
        GPIO_InitStruct.Pin = GPIO_PIN_9;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
        HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

        GPIO_InitStruct.Pin = GPIO_PIN_10;
        GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

        /* 中断配置 */

    }
}

void HAL_UART_MspDeInit(UART_HandleTypeDef* uartHandle){

    if(uartHandle->Instance == USART1){
        __HAL_RCC_USART1_CLK_DISABLE();
        HAL_GPIO_DeInit(GPIOA, GPIO_PIN_9 | GPIO_PIN_10);
    }
}