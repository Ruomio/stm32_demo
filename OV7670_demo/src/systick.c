/*
 * @Author: Ruomio 1065940593@qq.com
 * @Date: 2024-03-26 21:23:19
 * @LastEditors: Ruomio 1065940593@qq.com
 * @LastEditTime: 2024-03-29 13:36:41
 * @FilePath: /OV7670_demo/src/systick.c
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include "systick.h"

// void delay_init() {
// 	SysTick->CTRL = 0;
// 	HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK_DIV8);

// }


void delay_us(uint32_t i)
{
	// uint32_t temp;
	// SysTick->LOAD=9*i;
	// SysTick->VAL=0;
	// SysTick->CTRL=0X01;
	// do
	// {
	// 	temp=SysTick->CTRL;	 
	// }
	// while((temp&0x01)&&(!(temp&(1<<16))));	
	// SysTick->CTRL &= ~1;	
	// SysTick->VAL=0;



	uint32_t ticks;
	uint32_t told,tnow,tcnt = 0;
	uint32_t reload = SysTick->LOAD;    					/*LOAD的值*/
	ticks = i * 72;             /*需要的节拍数*/

	told = SysTick->VAL;                /*刚进入时的计数器值*/
	while(1)
	{
		tnow = SysTick->VAL;
		if(tnow != told)
		{
			if(tnow < told)
			{
				tcnt += told - tnow; /*注意一下SYSTICK是一个递减的计数器*/ 
			}
			else
			{
				tcnt += reload - tnow + told;
			}
			told = tnow;
			if(tcnt >= ticks)
			{
				break;            /*时间超过/等于要延时的时间，则退出*/
			}
		}
	}


}

void delay_ms(uint32_t i)
{

	// __disable_irq();
	// uint32_t temp;
	// SysTick->LOAD=9000*i;	  
	// SysTick->VAL=0;		
	// SysTick->CTRL=0X01;		
	// do
	// {
	// 	temp=SysTick->CTRL;	 
	// }
	// while((temp&0x01)&&(!(temp&(1<<16))));	
	// SysTick->CTRL &= ~1;	
	// SysTick->VAL=0;		

	// __enable_irq();

	while (i--)
	{
		/* code */
		delay_us(1000);
	}
	
}
