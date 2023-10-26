/*
 * @Author: PapillonAz 1065940593@q.com
 * @Date: 2023-10-25 23:06:46
 * @LastEditors: PapillonAz 1065940593@q.com
 * @LastEditTime: 2023-10-25 23:18:26
 * @FilePath: /IWDG_demo/src/iwdg.c
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include "iwdg.h"

IWDG_HandleTypeDef IWDG_HandleStruct;

void IWDG_Init(uint8_t prer, uint16_t rlr){

    IWDG_HandleStruct.Instance = IWDG;
    IWDG_HandleStruct.Init.Prescaler = prer;
    IWDG_HandleStruct.Init.Reload = rlr;


    HAL_IWDG_Init(&IWDG_HandleStruct);

}

void IWDG_Refresh(){
    
    HAL_IWDG_Refresh(&IWDG_HandleStruct);
    
}