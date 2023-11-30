#include "gtim.h"

TIM_HandleTypeDef htimx = {0};
void gtimx_Init(uint8_t psc, uint16_t arr) {

    htimx.Instance = TIM2;
    htimx.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    htimx.Init.CounterMode = TIM_COUNTERMODE_UP ;
    htimx.Init.Prescaler = psc;
    htimx.Init.Period = arr;
    // htimx.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
    HAL_TIM_IC_Init(&htimx);


    TIM_IC_InitTypeDef timx_ic = {0};
    timx_ic.ICPolarity = TIM_ICPOLARITY_RISING;          // 上升沿捕获
    timx_ic.ICSelection = TIM_ICSELECTION_DIRECTTI;      // 映射到TI1上
    timx_ic.ICPrescaler = TIM_ICPSC_DIV1;
    timx_ic.ICFilter = 0U;
    HAL_TIM_IC_ConfigChannel(&htimx, &timx_ic, TIM_CHANNEL_4);

    __HAL_TIM_ENABLE_IT(&htimx, TIM_IT_UPDATE);
    HAL_TIM_IC_Start_IT(&htimx, TIM_CHANNEL_4);
}

void HAL_TIM_IC_MspInit(TIM_HandleTypeDef *htim) {
    if(htim->Instance == TIM2) {
        __HAL_RCC_TIM2_CLK_ENABLE();
        __HAL_RCC_GPIOB_CLK_ENABLE();

        // 捕获 GPIOB_11  <-->  TIM2 CH4  重定义引脚
        GPIO_InitTypeDef gpiox = {0};
        gpiox.Pin = GPIO_PIN_11;
        gpiox.Mode = GPIO_MODE_AF_PP;
        gpiox.Pull = GPIO_PULLDOWN;
        gpiox.Speed = GPIO_SPEED_FREQ_HIGH;
        HAL_GPIO_Init(GPIOB, &gpiox);
        __HAL_AFIO_REMAP_TIM2_ENABLE();     // 复用端口重定义

        HAL_NVIC_SetPriority(TIM2_IRQn, 5, 0);      
        HAL_NVIC_EnableIRQ(TIM2_IRQn);

        
    }
}

/** htimx_cap_sta 捕获状态说明
 * bit[7]: 是否成功捕获
 * bit[6]: 是否捕获到高电平
 * bit[5:0]: 捕获高电平的溢出次数，最多2^6 -1 = 63  所以最多 63*65536 + 65535 = 4194303 us = 4.19 s
*/
uint8_t htimx_cap_sta = 0;
uint16_t htimx_cap_val = 0;

void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim) {
    if(htim->Instance == TIM2) {
        if(!(htimx_cap_sta & 0x80)) {           // 第七位的值 --> 未捕获成功
            if(htimx_cap_sta & 0x40 ) {         // 第六位的值 --> 已经捕获高电平， 所以要捕获下降沿计算时差
                htimx_cap_sta |= 0x80;          // 标记捕获成功
                htimx_cap_val = HAL_TIM_ReadCapturedValue(&htimx, TIM_CHANNEL_4); // 获取当前计数器的值

                __HAL_TIM_DISABLE(&htimx);      // 关闭定时器
                __HAL_TIM_SetCounter(&htimx, 0);     
                TIM_RESET_CAPTUREPOLARITY(&htimx, TIM_CHANNEL_4);                           // 先清除原来的设置
                TIM_SET_CAPTUREPOLARITY(&htimx, TIM_CHANNEL_4, TIM_ICPOLARITY_RISING);      // 改为上升沿捕获
                __HAL_TIM_ENABLE(&htimx);
            }
            else {                              // 还未捕获高电平， 即第一次捕获到高电平
                htimx_cap_sta = 0;
                htimx_cap_val = 0;

                htimx_cap_sta |= 0x40;          // 标记捕获到高电平
                
                __HAL_TIM_DISABLE(&htimx);      // 关闭定时器
                __HAL_TIM_SetCounter(&htimx, 0);            
                TIM_RESET_CAPTUREPOLARITY(&htimx, TIM_CHANNEL_4);                           // 先清除原来的设置
                TIM_SET_CAPTUREPOLARITY(&htimx, TIM_CHANNEL_4, TIM_ICPOLARITY_FALLING);     // 改为下降沿捕获
                __HAL_TIM_ENABLE(&htimx);
            }
        }
    }
}

/* 定时器溢出中断 */
void HAL_TIM_IC_CaptureHalfCpltCallback(TIM_HandleTypeDef *htim) {
    if(htim->Instance == TIM2) {
        if(!(htimx_cap_sta & 0x80)) {                       // 未捕获成功
            if(htimx_cap_sta & 0x40) {                      // 已经捕获高电平
                if((htimx_cap_sta & 0x3f) == 0x3f) {        // 低六位表示溢出次数，已经上限

                    __HAL_TIM_DISABLE(&htimx);      // 关闭定时器
                    __HAL_TIM_SetCounter(&htimx, 0);  
                    TIM_RESET_CAPTUREPOLARITY(&htimx, TIM_CHANNEL_4);                           // 先清除原来的设置
                    TIM_SET_CAPTUREPOLARITY(&htimx, TIM_CHANNEL_4, TIM_ICPOLARITY_RISING);      // 改为上升沿捕获
                    __HAL_TIM_ENABLE(&htimx);
                    
                    htimx_cap_sta |= 0x80;
                    htimx_cap_val = 0xffff;
                }
                else {
                    htimx_cap_sta++;
                }
            }
        }
    }
}