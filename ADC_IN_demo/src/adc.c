#include "adc.h"

ADC_HandleTypeDef hadc = {0};

void ADC_Init() {
    hadc.Instance = ADC1;
    hadc.Init.DataAlign = ADC_DATAALIGN_RIGHT;
    hadc.Init.ScanConvMode = DISABLE;               // 扫描
    hadc.Init.ContinuousConvMode = DISABLE;         // 连续
    hadc.Init.NbrOfConversion = 1;                  // 规则个数
    hadc.Init.DiscontinuousConvMode = DISABLE;      // 间断
    hadc.Init.NbrOfDiscConversion = 0;
    hadc.Init.ExternalTrigConv = ADC_SOFTWARE_START;    // 软件触发
    HAL_ADC_Init(&hadc);

    HAL_ADCEx_Calibration_Start(&hadc);      // adc 校准

    ADC_ChannelConfTypeDef adc_channel = {0};
    adc_channel.Channel = ADC_CHANNEL_0;
    adc_channel.Rank = ADC_REGULAR_RANK_1;  // 编号
    adc_channel.SamplingTime = ADC_SAMPLETIME_239CYCLES_5;      // 采样时间
    HAL_ADC_ConfigChannel(&hadc, &adc_channel);
}

void HAL_ADC_MspInit(ADC_HandleTypeDef *hadc) {
    if(hadc->Instance == ADC1) {
        __HAL_RCC_GPIOA_CLK_ENABLE();
        __HAL_RCC_ADC1_CLK_ENABLE();

        // HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, GPIO_PIN_RESET);
        GPIO_InitTypeDef GPIO_InitStruct = {0};
        /*Configure GPIO pin : PA0 */
        GPIO_InitStruct.Pin = GPIO_PIN_0;
        GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
        HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

        RCC_PeriphCLKInitTypeDef adc_clk = {0};
        adc_clk.PeriphClockSelection = RCC_PERIPHCLK_ADC;
        adc_clk.AdcClockSelection = RCC_ADCPCLK2_DIV6;
        HAL_RCCEx_PeriphCLKConfig(&adc_clk);
    }
}


uint32_t ADC_get_value() {
    HAL_ADC_Start(&hadc);
    HAL_ADC_PollForConversion(&hadc, 10);    // 等待完成
    return (uint16_t)HAL_ADC_GetValue(&hadc);
}