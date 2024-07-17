#include "led_matrix.h"

TIM_HandleTypeDef TimHandle;

#define REFRESH_RATE     60 				//刷新率 Hz
#define REFRESH_TIMES    8          //灰度等级为4, 用8个刷新次数来做灰度效果

SPI_HandleTypeDef Spi1Handle;

/**
  * @brief 初始化 LED 矩阵控制的 GPIO 引脚
  * @param 无
  * @retval 无
  */
void ledmat_msp_init(void)
{
  GPIO_InitTypeDef  GPIO_InitStruct = {0};

  // 启用 GPIOA 和 GPIOB 时钟
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOF_CLK_ENABLE();

  
  //行扫IO初始化
  GPIO_InitStruct.Pin = SCAN_A1_PIN|SCAN_B1_PIN|SCAN_C1_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;          			  /* Push-pull output */
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;                   		  /* Enable pull-up */
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;     		  /* GPIO speed */  
  /* GPIO initialization */
  HAL_GPIO_Init(SCAN_PORT_1, &GPIO_InitStruct);
	
  GPIO_InitStruct.Pin = SCAN_A2_PIN|SCAN_B2_PIN|SCAN_C2_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;          			  /* Push-pull output */
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;                   		  /* Enable pull-up */
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;     		  /* GPIO speed */  
  /* GPIO initialization */
  HAL_GPIO_Init(SCAN_PORT_2, &GPIO_InitStruct);
  
    
  GPIO_InitStruct.Pin =  SCAN_CS_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;          			  /* Push-pull output */
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;                   		  /* Enable pull-up */
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;     		  /* GPIO speed */  
  /* GPIO initialization */
  HAL_GPIO_Init(SCAN_CS_PORT, &GPIO_InitStruct);
  
  
  //列扫IO初始化
  GPIO_InitStruct.Pin = MBI_LE_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;          			  /* Push-pull output */
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;                   		  /* Enable pull-up */
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;     		  /* GPIO speed */  
  /* GPIO initialization */
  HAL_GPIO_Init(MBI_LE_PORT, &GPIO_InitStruct);
  
  //列扫IO初始化
  GPIO_InitStruct.Pin = MBI_OE_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;          			  /* Push-pull output */
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;                   		  /* Enable pull-up */
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;     		  /* GPIO speed */  
  /* GPIO initialization */
  HAL_GPIO_Init(MBI_OE_PORT, &GPIO_InitStruct);

 
	
  // 使用SPI1来作为MBI5124的发送接口

  /* De-initialize SPI configuration */
  /*Deinitialize SPI configuration*/
  Spi1Handle.Instance               = SPI1;                       /* SPI1 */
  Spi1Handle.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_2;  /* Prescaler: 256 */
  Spi1Handle.Init.Direction         = SPI_DIRECTION_2LINES;       /* Full-duplex */
  Spi1Handle.Init.CLKPolarity       = SPI_POLARITY_LOW;           /* Clock polarity: Low */
  Spi1Handle.Init.CLKPhase          = SPI_PHASE_1EDGE ;           /* Data sampling on the first clock edge */
  Spi1Handle.Init.DataSize          = SPI_DATASIZE_8BIT;          /* SPI data size: 8-bit */
  Spi1Handle.Init.FirstBit          = SPI_FIRSTBIT_MSB;           /* MSB transmitted first */
  Spi1Handle.Init.NSS               = SPI_NSS_HARD_OUTPUT;        /* NSS software mode (hardware mode) */
  Spi1Handle.Init.Mode = SPI_MODE_MASTER;                         /* Configured as master */
  if (HAL_SPI_DeInit(&Spi1Handle) != HAL_OK)
  {
    APP_ErrorHandler();
  }
  
  /* SPI initialization */
  if (HAL_SPI_Init(&Spi1Handle) != HAL_OK)
  {
    APP_ErrorHandler();
  }
  
  /* Wait for the button to be pressed */
  while (BSP_PB_GetState(BUTTON_KEY) == 1)
  {
  }
  
  // 初始化定时器句柄  - 用作扫描
  TimHandle.Instance = TIM1;                                                  
  
  TimHandle.Init.Period            = 1000000.0/REFRESH_RATE/16.0/REFRESH_TIMES;                                  
  TimHandle.Init.Prescaler         = 24 - 1;                                 
  TimHandle.Init.ClockDivision     = TIM_CLOCKDIVISION_DIV1;                  
  TimHandle.Init.CounterMode       = TIM_COUNTERMODE_UP;                      
  TimHandle.Init.RepetitionCounter = 1 - 1;                                   
  TimHandle.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;          

  /* Initialize TIM1 */
  if (HAL_TIM_Base_Init(&TimHandle) != HAL_OK)                                
  {
    APP_ErrorHandler();
  }
  
  // 启动定时器并使能中断
  HAL_TIM_Base_Start_IT(&TimHandle);
}



/**
  * @brief 设置LED点阵的行扫描控制信号
  * @param row 行号，取值范围为 0 到 15，对应两个扫描组的8行
  * @retval 无
  */
void Set_LED_Row(uint8_t row)
{
    if (row < 8)
    {
        // 若行号小于8，则选择第一个扫描组（A1, B1, C1）
        SCAN_CS_PORT->BRR = SCAN_CS_PIN; // 片选控制，拉低片选信号

        // 设置对应的扫描行引脚状态
        HAL_GPIO_WritePin(SCAN_PORT_1, SCAN_A1_PIN, (row & 0x01) ? GPIO_PIN_SET : GPIO_PIN_RESET);
        HAL_GPIO_WritePin(SCAN_PORT_1, SCAN_B1_PIN, (row & 0x02) ? GPIO_PIN_SET : GPIO_PIN_RESET);
        HAL_GPIO_WritePin(SCAN_PORT_1, SCAN_C1_PIN, (row & 0x04) ? GPIO_PIN_SET : GPIO_PIN_RESET);
    }
    else
    {
        // 若行号大于等于8，则选择第二个扫描组（A2, B2, C2）
        SCAN_CS_PORT->BSRR = SCAN_CS_PIN; // 片选控制，拉高片选信号
        row -= 8; 					   // 调整行号为第二组的对应行号

        // 设置对应的扫描行引脚状态
        HAL_GPIO_WritePin(SCAN_PORT_2, SCAN_A2_PIN, (row & 0x01) ? GPIO_PIN_SET : GPIO_PIN_RESET);
        HAL_GPIO_WritePin(SCAN_PORT_2, SCAN_B2_PIN, (row & 0x02) ? GPIO_PIN_SET : GPIO_PIN_RESET);
        HAL_GPIO_WritePin(SCAN_PORT_2, SCAN_C2_PIN, (row & 0x04) ? GPIO_PIN_SET : GPIO_PIN_RESET);
    }
}



/**
  * @brief LED点阵列数据传输函数
  * @param col_data 列数据，32位表示LED点阵的一列数据，每位控制一个LED的亮灭状态
  * @retval 无
  */
void __ledmat_column_transmit(uint32_t col_data)
{
	uint8_t dat[4] = {0};
	
	dat[3] = ((col_data & (0x000000FF)));
	dat[2] = ((col_data & (0x0000FF00)) >> 8);
	dat[1] = ((col_data & (0x00FF0000)) >> 16);
	dat[0] = ((col_data & (0xFF000000)) >> 24);
	
	HAL_SPI_Transmit(&Spi1Handle,dat,4,100);
}




/**
  * @brief 应用LED点阵列数据
  * @param 无
  * @retval 无
  */
void __ledmat_column_apply(void)
{
    // 设置LE引脚为高电平，使LED点阵控制器接受列数据
    MBI_LE_PORT->BSRR = MBI_LE_PIN;

    // 设置LE引脚为低电平，完成数据应用过程
    MBI_LE_PORT->BRR  = MBI_LE_PIN;
}



/**
  * @brief LED点阵初始化函数
  * @param matrix LED矩阵结构体指针，用于存储LED矩阵相关信息和数据
  * @param lev 初始灰度级别，用于初始化LED点阵的灰度值
  * @retval 无
  */
void LEDMatrix_Init(LED_Matrix_Type *matrix, GrayscaleLevel lev)
{
	ledmat_msp_init();
    // 发送空列数据，确保LED点阵初始状态为全灭
    __ledmat_column_transmit(0);
    __ledmat_column_apply();

    // 默认打开LED点阵显示
    LEDMatrix_TurnOn(matrix);

    // 初始化所有LED点的灰度值
    for (int y = 0; y < 16; ++y)
    {
        for (int x = 0; x < 32; ++x) 
        {
            LEDMatrix_SetPoint(matrix,x,y,lev);
        }
    }
    LEDMatrix_AllRam2ColData(matrix); //计算列数据并存储在列缓存中

    //设置模式为画布模式,并且将显存的指针指向画布
    matrix->mode = Draw;
    matrix->dis_p = matrix->Dis_Buff;
}




/**
 * @brief  打开LED点阵显示
 * @param  matrix: 点阵屏幕的结构体指针
 * @retval None
 */
void LEDMatrix_TurnOn(LED_Matrix_Type *matrix)
{
	matrix->IsOn = 1;
}



/**
 * @brief  关闭LED点阵显示
 * @param  matrix: 点阵屏幕的结构体指针
 * @retval None
 */
void LEDMatrix_TurnOff(LED_Matrix_Type *matrix)
{
	matrix->IsOn = 0;
}



/**
 * @brief  设置一个点的灰度值 (函数实现需要将列选择数据重新计算后,建议批量操作完毕再进行计算)
 * @param  matrix: 点阵屏幕的结构体指针
 * @param  x: 设定点的x坐标
 * @param  y: 设定点的y坐标
 * @param  lev: 灰度值(0-4)
 * @retval None
 */
void LEDMatrix_SetPoint(LED_Matrix_Type *matrix, int x, int y, GrayscaleLevel lev)
{
    // 为了根据从左到右的坐标定位数据点，将点阵的 x 进行偏移
    if (x < 16)
        x += 16;
    else
        x -= 16;
    y = 15-y; //需要对y轴进行偏移

    // 确定在 arr 数组中的具体位置
    int row = y;
    int col = x / 8; // 每个 uint32_t 变量可以存储8个灰度数据，每个灰度数据占4个bit，因此一个uint32_t变量可以存储32个灰度数据

    // 计算在 uint32_t 数组中的偏移和掩码
    int offset = x % 8;
    uint32_t mask = 0xF << (offset * 4); // 每个灰度数据占4位，因此左移动4位

    // 清除当前位置的灰度数据
    matrix->dis_p[row][col] &= ~mask;

    // 设置新的灰度数据
    uint32_t grayscale = (lev & 0xF) << (offset * 4); // 确保灰度数据在4个位内
    matrix->dis_p[row][col] |= grayscale;
}



/**
 * @brief  获取一个点的灰度值
 * @param  matrix: 点阵屏幕的结构体指针
 * @param  x: 获取点的x坐标
 * @param  y: 获取点的y坐标
 * @retval None
 */
GrayscaleLevel LEDMatrix_GetPoint(LED_Matrix_Type *matrix, int x, int y)
{
    // 确定在 arr 数组中的具体位置
    int row = y;
    int col = x / 8; // 每个 uint32_t 变量可以存储8个灰度数据，每个灰度数据占4个bit，因此一个uint32_t变量可以存储32个灰度数据

    // 计算在 uint32_t 数组中的偏移和掩码
    int offset = x % 8;
    uint32_t mask = 0xF << (offset * 4); // 每个灰度数据占4位，因此左移动4位

    // 获取当前位置的灰度数据
    uint32_t grayscale = (matrix->dis_p[row][col] & mask) >> (offset * 4);

    return (GrayscaleLevel) grayscale;
}



/**
  * @brief 将RAM中的灰度数据转换为LED点阵的列数据
  * @param matrix LED矩阵结构体指针，包含LED点阵的灰度数据
  * @param row 当前行号，范围为0到8，表示LED点阵的行
  * @param cnt 计数器，用于灰度级别的控制
  * @retval uint32_t 返回32位的列数据，表示LED点阵的一行中的列数据
  */
uint32_t LEDMatrix_Ram2ColData(LED_Matrix_Type *matrix, uint8_t row, uint8_t cnt)
{
    uint32_t col_data = 0;
	
    // 根据当前行的灰度值设置对应的位
    for (uint8_t col = 0; col < 32; col++)
    {
        //根据当且列号取出对应的灰度值
        uint8_t temp = LEDMatrix_GetPoint(matrix,col,row);
        switch (temp)
        {
            case 0:	 // 灰度值为0, 不点亮
            break;
            case 1:  // 灰度值为1，仅在计数器小于2时点亮该列
              if (cnt < 1)
                col_data  |= (0x80000000 >> (31 - col));
            break;
            case 2:  // 灰度值为2，仅在计数器小于2时点亮该列
               if (cnt < 2)
                 col_data |= (0x80000000 >> (31 - col));
            break;
            case 3:  // 灰度值为3，仅在计数器小于4时点亮该列
               if (cnt < 4)
                 col_data |= (0x80000000 >> (31 - col));
            break;
            case 4:  // 灰度值为4，仅在计数器小于8时点亮该列
               if (cnt < 8)
                 col_data |= (0x80000000 >> (31 - col));
            break;
            default: break;
        }
    }
    return col_data;  // 返回生成的32位列数据
}



/**
  * @brief 将所有RAM中的灰度数据转换为LED点阵的列数据
  * @param matrix LED矩阵结构体指针，包含LED点阵的灰度数据和列数据
  * @retval 无
  */
void LEDMatrix_AllRam2ColData(LED_Matrix_Type *matrix)
{
    // 遍历所有行和计数器，将RAM中的灰度数据转换为列数据
    for(uint8_t row = 0; row < 16; row++)
    {
        for(uint8_t cnt = 0; cnt < 8; cnt++)
        {
            // 调用LEDMatrix_Ram2ColData函数，将当前行、计数器cnt的灰度数据转换为列数据并存储
            matrix->Col_Data[row][cnt] = LEDMatrix_Ram2ColData(matrix, row, cnt);
        }
    }
}



/**
 * @brief 将位图数据加载到LED点阵显示缓冲区中。
 *
 * 此函数遍历位图数据数组，并根据位图位设置LED点阵显示缓冲区中对应的元素。
 *
 * @param matrix 指向表示LED点阵的LED_Matrix_Type结构体的指针。
 * @param dat 指向位图数据数组的指针。
 * @param len 数组长度
 */
void LoadBitmapToMatrix(LED_Matrix_Type *matrix,uint32_t (*data)[4])
{
  matrix->dis_p = data; //指向需要显示的图片的数据量
}


void Loading_Animation(LED_Matrix_Type * matrix,const Picture_Type* pic_arr,uint8_t pic_max)
{
	matrix->pic_array = (Picture_Type*)pic_arr;
	matrix->pic_max = pic_max;
	
	matrix->pic_count = 0;
	matrix->frame_cnt = 0;

	LoadBitmapToMatrix(matrix,(uint32_t (*)[4])matrix->pic_array[matrix->pic_count].ptr);
  matrix->mode = Picture;   //图片显示模式
}


void Loading_Animation_Handle(LED_Matrix_Type * matrix)
{
  matrix->frame_cnt++;
  if(matrix->frame_cnt >= matrix->pic_array->frame_len)
  {
    matrix->frame_cnt = 0;
    matrix->pic_flag = 1;
  }
  //切换显示下一张图片
  if(matrix->pic_flag)
  {
    matrix->pic_count++;
    matrix->pic_count %= matrix->pic_max;

    LoadBitmapToMatrix(matrix,(uint32_t (*)[4])matrix->pic_array[matrix->pic_count].ptr);
    matrix->pic_flag = 0;
  }
}


/**
  * @brief 更新LED点阵显示
  * @param matrix LED矩阵结构体指针
  * @retval 无
  */
void LEDMatrix_Update(LED_Matrix_Type* matrix)
{
  static uint8_t row = 0;        // 当前扫描的行号
  static uint8_t cnt = 0;        // 扫描计数器，用于实现灰度效果，每行扫描16次

	if(matrix->IsOn == 0) return;

  if(matrix->mode == Picture) //图片显示模式
  {
    //根据当前刷新的次数来选择列数据
    if(cnt > 3)
      __ledmat_column_transmit(matrix->dis_p[row][3]);  
    else if(cnt > 1)
      __ledmat_column_transmit(matrix->dis_p[row][2]);  
    else if(cnt > 0)
      __ledmat_column_transmit(matrix->dis_p[row][1]); 
    else
      __ledmat_column_transmit(matrix->dis_p[row][0]); 
  }
  if(matrix->mode == Draw)    //画图模式
  {
    __ledmat_column_transmit(matrix->Col_Data[row][cnt]);
  }


  __ledmat_column_apply(); // 应用列数据到LED点阵显示
	// 选中当前行
	MBI_OE_PORT->BSRR = MBI_OE_PIN;
	Set_LED_Row(row);
	MBI_OE_PORT->BRR = MBI_OE_PIN;
	row++;  // 行号加1


	// 如果已经刷新到最后一行，则重置行号并更新扫描计数器
	if (row == 16)
	{
		
		row = 0;    // 行号清零
		cnt++;      // 更新扫描计数器
		if(cnt == 8)
		{
			if(matrix->mode == Picture)   
		      Loading_Animation_Handle(matrix);
		  cnt = 0;
		}
	}
}



/**
  * @brief 执行渐变暗效果
  * @param time_ms 渐变效果的效果执行周期 [当A图像切换到B图像之前，这个渐变暗的效果会持续time_ms个毫妙]
  * @retval 无
  */
void FadeOut_Effect(LED_Matrix_Type* matrix,uint32_t time_ms)
{
  uint8_t i = 8;

  uint8_t row = 0;        // 当前扫描的行号
  uint8_t cnt = 0;        // 扫描计数器，用于实现灰度效果，每行扫描16次
  while(i)
  {
    // 刷新LED点阵列数据
    if(matrix->IsOn == 0) return;
    __ledmat_column_transmit(LEDMatrix_Ram2ColData(matrix,row,cnt));
    __ledmat_column_apply(); // 应用列数据到LED点阵显示

    // 选中当前行
    MBI_OE_PORT->BSRR = MBI_OE_PIN;
    Set_LED_Row(row);
    MBI_OE_PORT->BRR = MBI_OE_PIN;

    row++;  // 行号加1

    // 如果已经刷新到最后一行，则重置行号并更新扫描计数器
    if (row == 16)
    {
        row = 0;    // 行号清零
        cnt++;      // 更新扫描计数器
        cnt %= 8;   // 扫描计数器取模8，确保在0~8之间循环

       
        /*将Col_Data的数据进行更改
           一个画面需要刷新8次，每刷新一个画面后将第8-i个刷新的数据的亮度直接清除*/
        for(uint8_t n = 0; n < 16; n++)
        {
            //matrix->Col_Data[n][8-i] = 0;
        }
        i--;
    }
  }
}


/**
 * @brief  测试函数 - 每秒修改点阵所有点的灰度值，放在主循环中执行
 * @param  matrix: 点阵屏幕的结构体指针
 * @retval None
 */
void LEDMatrix_Text_Draw(LED_Matrix_Type *matrix)
{
    static uint32_t tick = 0;        // 记录上次更新时间的计数器
    static GrayscaleLevel lev = Grayscale_Off;  // 当前灰度级别

    // 检查是否到达下一次更新时间
    if (tick <= HAL_GetTick())
    {
        tick = HAL_GetTick() + 1000;  // 更新下次更新时间为当前时间加上1秒

        // 初始化左侧LED点阵和右侧LED点阵，帧率为120，灰度级别为lev
        LEDMatrix_Init(matrix, lev);

        lev++;          // 更新灰度级别
        lev %= 5;       // 灰度级别循环在0到3之间
    }

    // 更新LED点阵显示
    LEDMatrix_Update(matrix);
}



