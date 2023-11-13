#include "gtim.h"


TIM_HandleTypeDef g_timx_pwm_chy_handle = {0};
void gtim_timx_pwn_chy_init(uint16_t psc, uint16_t arr) {
    

    g_timx_pwm_chy_handle.Instance = TIM3;
    g_timx_pwm_chy_handle.Init.Prescaler = psc;
    g_timx_pwm_chy_handle.Init.Period = arr;
    g_timx_pwm_chy_handle.Init.CounterMode = TIM_COUNTERMODE_UP;
    g_timx_pwm_chy_handle.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    

    HAL_TIM_PWM_Init(&g_timx_pwm_chy_handle);

    TIM_OC_InitTypeDef timx_oc_pwn_chy = {0};
    timx_oc_pwn_chy.OCMode = TIM_OCMODE_PWM1;
    timx_oc_pwn_chy.Pulse = arr/2;                      // 脉宽
    timx_oc_pwn_chy.OCPolarity = TIM_OCPOLARITY_LOW;
    HAL_TIM_PWM_ConfigChannel(&g_timx_pwm_chy_handle, &timx_oc_pwn_chy, TIM_CHANNEL_1);
    HAL_TIM_PWM_Start(&g_timx_pwm_chy_handle, TIM_CHANNEL_1);
}

void HAL_TIM_PWM_MspInit(TIM_HandleTypeDef *htim) {
    if(htim->Instance == TIM3) {
        GPIO_InitTypeDef GPIO_InitStruct = {0};
        __HAL_RCC_GPIOB_CLK_ENABLE();
        __HAL_RCC_TIM3_CLK_ENABLE();
        

        GPIO_InitStruct.Pin = GPIO_PIN_6;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Pull = GPIO_PULLUP;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
        HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

        __HAL_RCC_AFIO_CLK_ENABLE();
        // __HAL_AFIO_REMAP_TIM3_PARTIAL();    // 复用端口重定义
        
    }
}