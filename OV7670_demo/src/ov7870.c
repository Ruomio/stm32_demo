/*
 * @Author: Ruomio 1065940593@qq.com
 * @Date: 2024-03-27 16:04:49
 * @LastEditors: Ruomio 1065940593@qq.com
 * @LastEditTime: 2024-03-31 19:03:45
 * @FilePath: /OV7670_demo/src/ov7870.c
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include "ov7670.h"
#include "ov7670cfg.h"
#include "sccb.h"
#include "i2c.h"
#include "systick.h"


uint8_t ov7670_init() {
    uint8_t temp;
	uint16_t i=0;
	 
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();
    __HAL_RCC_AFIO_CLK_ENABLE();

 	GPIO_InitTypeDef  GPIO_InitStructure = {0};

    //PB0 输入 上拉  VSYNC  帧同步信号
	GPIO_InitStructure.Pin  = GPIO_PIN_0; 	
	GPIO_InitStructure.Mode = GPIO_MODE_INPUT;
	GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStructure);

    //PB1		HREF  行同步信号
    GPIO_InitStructure.Pin  = GPIO_PIN_1;  			
	GPIO_InitStructure.Mode = GPIO_MODE_INPUT;
 	HAL_GPIO_Init(GPIOB, &GPIO_InitStructure);

    //PB10  端口配置			 PCLK  像素时钟
	GPIO_InitStructure.Pin =  GPIO_PIN_10;			
 	GPIO_InitStructure.Mode = GPIO_MODE_INPUT; 		
 	HAL_GPIO_Init(GPIOB, &GPIO_InitStructure);

    //PA8  端口配置			 MCLK  时钟, 
	GPIO_InitStructure.Pin =  GPIO_PIN_8;			
 	GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP; 	
    GPIO_InitStructure.Speed = 	GPIO_SPEED_FREQ_LOW;
 	HAL_GPIO_Init(GPIOA, &GPIO_InitStructure);
    HAL_RCC_MCOConfig(RCC_MCO1, RCC_MCO1SOURCE_HSE, RCC_MCODIV_1);
	
	//PB3 端口配置			PWDN  正常使用拉低
 	// GPIO_InitStructure.Pin = GPIO_PIN_3;				 
 	// GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP; 		 //推挽输出
 	// HAL_GPIO_Init(GPIOB, &GPIO_InitStructure);

	//PB4  RESET		正常使用拉高
	// GPIO_InitStructure.Pin  = GPIO_PIN_4;  		
	// GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
 	// HAL_GPIO_Init(GPIOB, &GPIO_InitStructure);

    //PA0~7 输入 上拉			D0~7
	GPIO_InitStructure.Pin  = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7; 
	GPIO_InitStructure.Mode = GPIO_MODE_INPUT;
 	HAL_GPIO_Init(GPIOA, &GPIO_InitStructure);
	
    //初始化SCCB 的IO口
    // Sccb_init();
    MX_I2C1_Init();
	
 	if(SCCB_WriteReg(0x12, 0x80))    return 1;	//复位SCCB
	delay_ms(50); 
	// temp=SCCB_ReadReg(0x12);
	//读取产品型号
 	temp=SCCB_ReadReg(0x0b);
	if(temp!=0x73)  return 2;  
 	temp=SCCB_ReadReg(0x0a);	
	if(temp!=0x76)  return 3;
	//初始化序列	  对OV7670寄存器进行操作
	for(i=0;i<sizeof(ov7670_init_reg_tbl)/sizeof(ov7670_init_reg_tbl[0])/2;i++)
	{
	   	SCCB_WriteReg(ov7670_init_reg_tbl[i][0],ov7670_init_reg_tbl[i][1]);
		delay_ms(2);
 	}
   	return 0x00; 	//ok

}