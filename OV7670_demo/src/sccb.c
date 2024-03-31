/*
 * @Author: Ruomio 1065940593@qq.com
 * @Date: 2024-03-26 20:50:09
 * @LastEditors: Ruomio 1065940593@qq.com
 * @LastEditTime: 2024-03-31 19:09:37
 * @FilePath: /OV7670_demo/src/sccb.c
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include "sccb.h"
#include "systick.h"
#include "sys.h"

void Sccb_init() {
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    __HAL_RCC_GPIOB_CLK_ENABLE();
    /**I2C1 GPIO Configuration
    PB6     ------> I2C1_SCL
    PB7     ------> I2C1_SDA
    */

    GPIO_InitStruct.Pin = GPIO_PIN_6 | GPIO_PIN_7;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    // HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6 | GPIO_PIN_7, GPIO_PIN_SET);
}

void Sccb_sda_output() {
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    __HAL_RCC_GPIOB_CLK_ENABLE();
    /**I2C1 GPIO Configuration
    PB6     ------> I2C1_SCL
    PB7     ------> I2C1_SDA
    */

    GPIO_InitStruct.Pin = GPIO_PIN_7;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
}


void Sccb_sda_input() {
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    __HAL_RCC_GPIOB_CLK_ENABLE();
    /**I2C1 GPIO Configuration
    PB6     ------> I2C1_SCL
    PB7     ------> I2C1_SDA
    */

    GPIO_InitStruct.Pin = GPIO_PIN_7;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

}

void StartSCCB() {

    SCCB_SDA_H();
    delay_us(50);
    
    SCCB_SCL_H();
    delay_us(50);

    SCCB_SDA_L();
    delay_us(50);

    SCCB_SCL_L();
    delay_us(50);
}

void StopSCCB() {

    SCCB_SDA_L();
    delay_us(50);
    
    SCCB_SCL_H();
    delay_us(50);

    SCCB_SDA_H();
    delay_us(50);

}

void NoAck() {
    delay_us(50);
    
    SCCB_SDA_H();
    delay_us(50);

    SCCB_SCL_H();
    delay_us(50);

    SCCB_SCL_L();
    delay_us(50);

    SCCB_SDA_L();
    delay_us(50);
}

uint8_t SCCB_WriteByte(uint8_t m_data) {
    uint8_t res = 0;
    for(uint8_t j=0; j<8; j++) {
        if((m_data)&0x80) {
            SCCB_SDA_H();
        }
        else {
            SCCB_SDA_L();
        }
        m_data <<= 1;
        delay_us(50);
        SCCB_SCL_H();
        delay_us(50);
        SCCB_SCL_L();
        delay_us(50);
    }
    Sccb_sda_input();
    delay_us(50);

    SCCB_SCL_H();
    delay_us(50);
    res = SCCB_SDA_STATE;
    SCCB_SCL_L();
    delay_us(50);
    Sccb_sda_output();
    delay_us(100);

    // printf("SCCB_WriteByte return %d\r\n", res);

    return res; // 1:错误，  0:正确
}

uint8_t SCCB_ReadByte() {
    uint8_t res = 0;
    Sccb_sda_input();
    for(uint8_t i=8; i>0; i--) {
        delay_us(50);
        SCCB_SCL_H();
        res <<= 1;
        if(SCCB_SDA_STATE) res++;
        delay_us(50);
        SCCB_SCL_L();
    }
    Sccb_sda_output();

    

    // printf("SCCB_ReadByte res %d\r\n", res);
    return res;
}

/**
 * @description: 写操作 无法连续写
 * @param {uint8_t} reg
 * @param {uint8_t} data
 * @return {*} 状态码
 */
uint8_t SCCB_WriteReg(uint8_t reg, uint8_t data) {
    uint8_t res = 0;
    StartSCCB();
    if(SCCB_WriteByte(SCCB_ID)) res |= 0b00000001;       // 写入从机地址 失败返回 1
    delay_us(50);
    Sccb_sda_input();
    delay_us(50);
    if(SCCB_SDA_STATE) res |= 0b00000010;         // 从机返回应答 失败
    delay_us(50);
    Sccb_sda_output();
    delay_us(50);
    if(SCCB_WriteByte(reg)) res |= 0b00000100;    // 写入从机寄存器地址 失败返回 3
    delay_us(50);
    Sccb_sda_input();
    delay_us(50);
    if(SCCB_SDA_STATE) res |= 0b00001000;         // 从机返回应答 失败
    delay_us(50);
    Sccb_sda_output();
    delay_us(50);
    if(SCCB_WriteByte(data)) res |= 0b00010000;   // 写入从机地址 失败返回 1
    delay_us(50);
    Sccb_sda_input();
    delay_us(50);
    if(SCCB_SDA_STATE) res |= 0b00100000;         // 从机返回应答 失败
    delay_us(50);
    Sccb_sda_output();
    delay_us(50);
    StopSCCB();

    // uint8_t res=0;
	// StartSCCB(); 					//启动SCCB传输
	// if(SCCB_WriteByte(SCCB_ID))res=1;	//写器件ID	  
	// delay_us(100);
  	// if(SCCB_WriteByte(reg))res=1;		//写寄存器地址	  
	// delay_us(100);
  	// if(SCCB_WriteByte(data))res=1; 	//写数据	 
  	// StopSCCB();	  

    // uint8_t data_a[1] = {data};
    // res = HAL_I2C_Mem_Write(&hi2c1, SCCB_ID, reg, 1, data_a, 1, 100);

    printf("SCCB_WriteReg res %d\r\n", res);

    return res;
}


uint8_t SCCB_ReadReg(uint8_t reg) {
    uint8_t res = 0; 
    uint8_t val = 0;
    StartSCCB();
    delay_us(50);
    if(SCCB_WriteByte(SCCB_ID)) res |= 0b00000001;       // 写入从机地址 失败返回 1
    delay_us(50);
    Sccb_sda_input();
    delay_us(50);
    if(SCCB_SDA_STATE) res |= 0b00000010;         // 从机返回应答 失败
    delay_us(50);
    Sccb_sda_output();
    delay_us(100);
    if(SCCB_WriteByte(reg)) res |= 0b00000100;    // 写入从机寄存器地址 失败返回 3
    delay_us(50);
    StopSCCB();
    delay_us(100);

    StartSCCB();
    delay_us(100);
    if(SCCB_WriteByte(SCCB_ID|0x01)) res |= 0b00001000;       // 写入从机地址 失败返回 
    delay_us(50);
    Sccb_sda_input();
    delay_us(100);
    if(SCCB_SDA_STATE) res |= 0b00010000;         // 从机返回应答 失败
    delay_us(50);

    val = SCCB_ReadByte();
    delay_us(50);
    NoAck();
    delay_us(50);
    StopSCCB();

    printf("SCCB_ReadReg res %x\r\n", res);
    printf("SCCB_ReadReg val %d\r\n", val);

    // uint8_t recive[1] = {0};
    // res = HAL_I2C_Mem_Read(&hi2c1, SCCB_ID, reg, 1, recive, 1, 100);
    // printf("SCCB_ReadReg res %d\r\n", res);
    // printf("SCCB_ReadReg recive %d\r\n", recive[0]);

    // 若状态码不为0则返回错误代码，否则返回读取到的值
    if(res) return res; 
    else    return val;

}