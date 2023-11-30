#include "sys.h"
#include "oled.h"
#include "usart.h"

#define OLED
#define USART

int _write(int file, char* ptr, int len) {

#ifdef OLED
    int pos_x = ptr[0] - '0';
    int pos_y = ptr[2] - '0';
    // OLED_NewFrame();
    for(int i=3; i< len; i++) {
        OLED_PrintASCIIChar((pos_x + i-3)*6, pos_y*12, ptr[i], &afont12x6, OLED_COLOR_NORMAL);
        // OLED_PrintASCIIChar(6, 12, (len + '0'), &afont12x6, OLED_COLOR_NORMAL);
        // OLED_PrintASCIIChar(i*6, 12, (char)i + 'a', &afont12x6, OLED_COLOR_NORMAL);
    }
    OLED_ShowFrame();
#endif


#ifdef USART

    for (int i = 0; i < len; i++)  
    {  
        while((USART1->SR&0X40)==0);//等待上一次串口数据发送完成  
        USART1->DR = (uint8_t) ptr[i];       //写DR,串口1将发送数据
    }  

#endif

    return 0;
}