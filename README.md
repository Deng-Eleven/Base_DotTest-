# Base_DotTest-
/**
  * @brief LED矩阵驱动头文件
  * 
  * 这个头文件定义了LED矩阵驱动的接口和数据结构，用于控制和管理LED点阵显示。
  * 包括初始化、设置点亮状态、设置灰度级别、更新显示等功能。
  *
  * 使用说明：
  *   01 - 使用前需要先定义点阵结构体,然后调用LEDMatrix_Init()函数来进行MSP和数据的初始化，包括有定时器、GPIO、灰度等级设定
  *   02 - 在绘图模式下点阵中如果数据发生更改，需要调用一次LEDMatrix_AllRam2ColData()函数来对列选择的数据进行更新
  *   03 - 通过设置宏REFRESH_RATE来修改帧率
  *   04 - Loading_Animation()用于显示图片模式，图片数据可以在LED_Font.c中查看，并在LED_Font.h中引用
  *   05 - 通过调用LEDMatrix_Update()函数来刷新显示 需要自己重构定时器中断回调函数调用LEDMatrix_Update()
  *   06 - 可以调用LEDMatrix_Text()来进行刷新测试
  *   07 - 在User.c中提供了部分参考代码
  *
  *
  * @copyright 风翎科技
  * @author 邓思忆
  * @date 2024/07/13
  * @version 1.1
  */
