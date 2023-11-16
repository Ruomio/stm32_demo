#include "encoder.h"

extern int encoder_cnt;


void Encoder_Init() {
    
    GPIO_InitTypeDef GPIOB_Init_Struct = {0};

    /* GPIO Ports Clock Enable */
    __HAL_RCC_GPIOC_CLK_ENABLE();
    __HAL_RCC_GPIOD_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();



    /*Configure GPIO pin : PB0 & PB1*/
    GPIOB_Init_Struct.Pin = GPIO_PIN_0 | GPIO_PIN_1;
    GPIOB_Init_Struct.Mode = GPIO_MODE_IT_RISING_FALLING;
    GPIOB_Init_Struct.Pull = GPIO_PULLUP;
    // GPIOB_Init_Struct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOB, &GPIOB_Init_Struct);

    HAL_NVIC_SetPriority(EXTI0_IRQn, 3, 0);             // 只判断一个引脚的中断
    HAL_NVIC_EnableIRQ(EXTI0_IRQn);

    // HAL_NVIC_SetPriority(EXTI1_IRQn, 3, 1);
    // HAL_NVIC_EnableIRQ(EXTI1_IRQn);

}


/* 中断服务函数在 stm32f1xx_it.c 中 */


uint8_t flag=0;
uint8_t CW_0=0;
uint8_t CW_1=0;

/* 中断回调服务函数 */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
    
    GPIO_PinState pb0 = HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_0);
    GPIO_PinState pb1 = HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_1);

    if(!flag && pb0==RESET) {
        flag = 1;
        CW_0 = pb1;
    }
    if(flag && pb0) {
        CW_1 = !pb1;
        if(CW_0 && CW_1) {
            encoder_cnt++;
        }
        if(!CW_0 && !CW_1) {
            encoder_cnt--;
        }
        flag=0;
    }

}





