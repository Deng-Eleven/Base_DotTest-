#include "User.h"
#include "led_font.h"
#include "led_matrix.h"


LED_Matrix_Type Matrix = {0};

uint16_t ADC_Light_Value = 0;

extern TIM_HandleTypeDef TimHandle;

/**
  * @brief  中断回调函数
  * @param  
  * @retval 
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if(htim == &TimHandle)
	{
		LEDMatrix_Update(&Matrix);
		//LEDMatrix_Text_Draw(&Matrix);
	}
}



/**
 * @brief 用户初始化函数
 * @retval None
 */
void User_Init(void)
{	
    //初始化点阵并将所有点设定为关闭状态
	LEDMatrix_Init(&Matrix,Grayscale_Off);	
	//加载动画组到点阵结构体的内部显存
	Loading_Animation(&Matrix,&full,1);
	
	//Loading_Animation(&Matrix,animation_wait,8);
}

/**
 * @brief  用户循环函数
 * @retval None
 */
void User_Loop(void)
{
	
}
