#ifndef __LED_FONT_H__
#define __LED_FONT_H__

#include "main.h"

typedef struct 
{
  uint32_t (*ptr)[4]; //指向当前需要显示的图片
  uint8_t frame_len;  //画面显示次数
}Picture_Type;

extern const Picture_Type animation_wait[8];        //等待
extern const Picture_Type full;		

#endif 
