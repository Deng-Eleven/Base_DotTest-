#ifndef _LED_MATRIX_H_
#define _LED_MATRIX_H_

#include "main.h"
#include "led_font.h"

/**
  * @brief LED矩阵驱动头文件
  * 
  * 这个头文件定义了LED矩阵驱动的接口和数据结构，用于控制和管理LED点阵显示。
  * 包括初始化、设置点亮状态、设置灰度级别、更新显示等功能。
  *
  * 使用说明：
  *   01 - 使用前需要先定义点阵结构体,然后调用LEDMatrix_Init()函数来进行MSP和数据的初始化，包括有定时器、GPIO、灰度等级设定
  *   02 - 点阵中如果数据发生更改，需要调用一次LEDMatrix_AllRam2ColData()函数来对列选择的数据进行更新
  *   03 - 通过设置宏REFRESH_RATE来修改帧率，建议设定90Hz,120Hz考虑到主频不够快可能会出现死机情况，90Hz会有一半时间的冗余
  *   04 - 如果要对数据进行转换，请使用行扫描的格式，一个字节代表8个点，一行需要两个字节，通过调用LoadBitmapToMatrix()函数实现
  *   05 - 通过调用LEDMatrix_Update()函数来刷新显示 需要自己重构定时器中断回调函数调用LEDMatrix_Update()
  *   06 - 可以调用LEDMatrix_Text()来进行刷新测试
  *
  *
  *
  * @copyright 风翎科技
  * @author 邓思忆
  * @date 2024/06/16
  * @version 1.1
  */


extern TIM_HandleTypeDef TimHandle;  // 外部声明定时器句柄
extern SPI_HandleTypeDef Spi1Handle; // 外部声明SPI句柄


/*********************** 定义硬件端口 ************************/

// 行扫描接口定义
#define SCAN_CS_PORT GPIOF
#define SCAN_CS_PIN  GPIO_PIN_3


#define SCAN_PORT_1 GPIOA
#define SCAN_A1_PIN GPIO_PIN_0
#define SCAN_B1_PIN GPIO_PIN_1
#define SCAN_C1_PIN GPIO_PIN_2     // 前八行扫描接口


#define SCAN_PORT_2 GPIOA
#define SCAN_A2_PIN GPIO_PIN_3
#define SCAN_B2_PIN GPIO_PIN_4
#define SCAN_C2_PIN GPIO_PIN_5     // 后八行扫描接口

// 列扫描接口定义
#define MBI_LE_PORT GPIOB
#define MBI_LE_PIN  GPIO_PIN_2

#define MBI_OE_PORT GPIOA
#define MBI_OE_PIN  GPIO_PIN_10


/*********************** 枚举和结构体定义 ************************/

/**
  * @brief 灰度级别枚举
  * 
  * 这个枚举定义了LED点阵显示的灰度级别，用于控制点亮的亮度。
  */
typedef enum
{
	Grayscale_Off     = 0,		  // 灰度级别0，LED点阵灭
    Grayscale_VeryLow = 1,    	  // 灰度级别1，特别低亮度
    Grayscale_Low	    = 2,      // 灰度级别2，低等亮度
    Grayscale_Medium  = 3,  	  // 灰度级别3，中亮度
    Grayscale_High    = 4,     	  // 灰度级别4, 高亮度
} GrayscaleLevel;

typedef enum
{
  Draw = 0,   //画图模式，用户可以独立设置每个点的灰度
  Picture,    //图片格式，用户可以通过led_font.c中的数据对图片进行显示
}LED_Matrix_ShowMode_Type;

/**
  * @brief LED点阵结构体
  * 
  * 这个结构体定义了LED点阵的状态和数据，包括开关机状态、灰度数据缓存和列数据缓存。
  */
typedef struct
{
    uint8_t IsOn;                          //开关机状态字节
    LED_Matrix_ShowMode_Type mode;         //显示模式

    /*绘图模式*/
    uint32_t Dis_Buff[32][4];              //画布，单独用于绘图模式
    uint32_t Col_Data[16][8];              //画布列数据16行，每行刷新8次

    /*图片显示模式*/
	  uint32_t (*dis_p)[4];				   //显存指针 - 用来指向需要显示的列数据
    Picture_Type* pic_array;               //当前的图片组             
    uint8_t pic_flag;                      //图片装载标志，开启后说明需要装载下一张图片
    uint8_t pic_max;                       //该组图片最大长度
    uint8_t pic_count;                     //当前第几个图片
    uint8_t frame_cnt;                     //当前该图片的在当前帧率下刷新了多少次
} LED_Matrix_Type;



/*********************** 函数原型声明 ************************/

void LEDMatrix_SetPoint(LED_Matrix_Type *matrix, int x, int y, GrayscaleLevel lev);
GrayscaleLevel LEDMatrix_GetPoint(LED_Matrix_Type *matrix, int x, int y);
void LEDMatrix_AllRam2ColData(LED_Matrix_Type *matrix);
/*以上函数仅用于画图模式*/
void LEDMatrix_Init(LED_Matrix_Type *matrix, GrayscaleLevel lev);

void LEDMatrix_TurnOn(LED_Matrix_Type *matrix);
void LEDMatrix_TurnOff(LED_Matrix_Type *matrix);

void LoadBitmapToMatrix(LED_Matrix_Type *matrix,uint32_t (*data)[4]);
void Loading_Animation(LED_Matrix_Type * matrix,const Picture_Type* pic_arr,uint8_t pic_max);
void Loading_Animation_Handle(LED_Matrix_Type * matrix);

void LEDMatrix_Update(LED_Matrix_Type* matrix);




/*********************** 测试函数用例 ************************/
/**
 * @brief  测试函数 - 每秒修改点阵所有点的灰度值，放在主循环中执行
 * @param  matrix: 点阵屏幕的结构体指针
 * @retval None
 */
void LEDMatrix_Text_Draw(LED_Matrix_Type *matrix);

#endif /* _LED_MATRIX_H_ */
