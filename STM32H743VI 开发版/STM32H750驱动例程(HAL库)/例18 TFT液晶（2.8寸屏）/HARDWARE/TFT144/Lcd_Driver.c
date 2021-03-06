#include "sys.h"
#include "Lcd_Driver.h"
#include "delay.h"





//********************************************************************************

//DevEBox  大越电子（嵌入式开发网）
//淘宝店铺：mcudev.taobao.com
//淘宝店铺：shop389957290.taobao.com	

//********************************************************************************


//STM32核心板例程
//库函数版本例程

//本测试程序使用的是模拟SPI接口驱动
//可自由更改接口IO配置，使用任意最少4 IO即可完成本款液晶驱动显示

/******************************************************************************
接口定义在Lcd_Driver.h内定义，请根据接线修改并修改相应IO初始化LCD_GPIO_Init()

//  ----------------------------------------------------------------
// VCC  接5V或3.3v电源
// GND  电源地
// D1   接PB15（SDI）
// D0   接PB13（SCL）
// CS   接PB12 片选    
// RST  接PB14 系统复位
// DC   接PB1  命令/数据  
// BLK  接PB0 背光控制    
// ----------------------------------------------------------------

//	#define LCD_SDI        	//PB15
//	#define LCD_SCL        	//PB13
//	#define LCD_CS        	//PB12
//	#define LCD_SDO     		//PB14 
//	#define LCD_RS         	//PB1
//	#define LCD_BLK         //PB0    	
*******************************************************************************/

/**************************************************************************************

函数名称: void LCD_GPIO_Init(void)

功能描述: 液晶IO初始化配置
输    入: 
输    出: 

//DevEBox  大越电子（嵌入式开发网）
//淘宝店铺：mcudev.taobao.com
//淘宝店铺：shop389957290.taobao.com	

**************************************************************************************/

void LCD_GPIO_Init(void)
{

    GPIO_InitTypeDef GPIO_Initure;
    __HAL_RCC_GPIOB_CLK_ENABLE();					          //开启PB时钟
	

    GPIO_Initure.Pin=GPIO_PIN_0 |GPIO_PIN_1 | GPIO_PIN_12| GPIO_PIN_13| GPIO_PIN_14| GPIO_PIN_15;	//PB
    GPIO_Initure.Mode=GPIO_MODE_OUTPUT_PP;  		    //推挽输出
    GPIO_Initure.Pull=GPIO_PULLUP;         			    //上拉
    GPIO_Initure.Speed=GPIO_SPEED_FREQ_VERY_HIGH;  	//高速
    HAL_GPIO_Init(GPIOB,&GPIO_Initure);     	     	//初始化
	  
    HAL_GPIO_WritePin(GPIOB,GPIO_PIN_0,GPIO_PIN_SET);	  //PB0置1 	
	  HAL_GPIO_WritePin(GPIOB,GPIO_PIN_1,GPIO_PIN_SET);	  //PB1置1 
	  HAL_GPIO_WritePin(GPIOB,GPIO_PIN_12,GPIO_PIN_SET);	//PB12置1 
 	  HAL_GPIO_WritePin(GPIOB,GPIO_PIN_13,GPIO_PIN_SET);	//PB13置1 
    HAL_GPIO_WritePin(GPIOB,GPIO_PIN_14,GPIO_PIN_SET);	//PB14置1 
	  HAL_GPIO_WritePin(GPIOB,GPIO_PIN_15,GPIO_PIN_SET);	//PB15置1 
			
		LCD_BLK_SET;//开启背光
		LCD_BLK_CLR;//关闭背光
		LCD_BLK_SET;//开启背光
      
}

/**************************************************************************************

函数名称: void  SPI_WriteData(uint8_t Data)

功能描述: 向SPI总线传输一个8位数据
输    入: 
输    出: 

//DevEBox  大越电子（嵌入式开发网）
//淘宝店铺：mcudev.taobao.com
//淘宝店铺：shop389957290.taobao.com	

**************************************************************************************/

void  SPI_WriteData(uint8_t Data)
{
  	unsigned char i=0;
		for(i=8;i>0;i--)
		{
			if(Data&0x80)	
			LCD_SDA_SET; //输出数据
				else LCD_SDA_CLR;
			 
				LCD_SCL_CLR;       
				LCD_SCL_SET;
				Data<<=1; 
		}
}





/**************************************************************************************

函数名称: void  SPI_WriteData(uint8_t Data)

功能描述: 向液晶屏写一个8位指令
输    入: 
输    出: 

//DevEBox  大越电子（嵌入式开发网）
//淘宝店铺：mcudev.taobao.com
//淘宝店铺：shop389957290.taobao.com	

**************************************************************************************/

void Lcd_WriteIndex(uint8_t Index)
{
   //SPI 写命令时序开始
   LCD_CS_CLR;
   LCD_RS_CLR;
	 SPI_WriteData(Index);
   LCD_CS_SET;
}


/**************************************************************************************

函数名称: void Lcd_WriteData(uint8_t Data)

功能描述: 向液晶屏写一个8位数据
输    入: 
输    出: 

//DevEBox  大越电子（嵌入式开发网）
//淘宝店铺：mcudev.taobao.com
//淘宝店铺：shop389957290.taobao.com	

**************************************************************************************/

void Lcd_WriteData(uint8_t Data)
{
   LCD_CS_CLR;
   LCD_RS_SET;
   SPI_WriteData(Data);
   LCD_CS_SET; 
}



/**************************************************************************************

函数名称: void LCD_WriteData_16Bit(uint16_t Data)

功能描述: 向液晶屏写一个16位数据
输    入: 
输    出: 

//DevEBox  大越电子（嵌入式开发网）
//淘宝店铺：mcudev.taobao.com
//淘宝店铺：shop389957290.taobao.com	

**************************************************************************************/

void LCD_WriteData_16Bit(uint16_t Data)
{
   LCD_CS_CLR;
   LCD_RS_SET;
	 SPI_WriteData(Data>>8); 	//写入高8位数据
	 SPI_WriteData(Data); 			//写入低8位数据
   LCD_CS_SET; 
}


/**************************************************************************************

函数名称: void Lcd_WriteReg(uint8_t Index,uint8_t Data)

功能描述: 写液晶屏寄存器
输    入: 
输    出: 

//DevEBox  大越电子（嵌入式开发网）
//淘宝店铺：mcudev.taobao.com
//淘宝店铺：shop389957290.taobao.com	

**************************************************************************************/


void Lcd_WriteReg(uint8_t Index,uint8_t Data)
{
	Lcd_WriteIndex(Index);
  Lcd_WriteData(Data);
}


/**************************************************************************************

函数名称: void Lcd_Reset(void)

功能描述: 硬件IO控制液晶屏复位，如果使用的是有字库版本的屏幕，此函数无效
输    入: 
输    出: 

//DevEBox  大越电子（嵌入式开发网）
//淘宝店铺：mcudev.taobao.com
//淘宝店铺：shop389957290.taobao.com	

**************************************************************************************/

void Lcd_Reset(void)
{
  LCD_RST_Clr();//RST引脚输出为高
	delay_ms(300);
  LCD_RST_Set();//RST引脚输出为低
	delay_ms(100);
}



/**************************************************************************************

函数名称: void Lcd_Init(void)

功能描述: 1.44寸 液晶屏初始化函数，液晶屏控制器是：ST7735R.
输    入: 
输    出: 

//DevEBox  大越电子（嵌入式开发网）
//淘宝店铺：mcudev.taobao.com
//淘宝店铺：shop389957290.taobao.com	

**************************************************************************************/

void Lcd_Init(void)
{	
	LCD_GPIO_Init();
	Lcd_Reset(); //Reset before LCD Init.

	//LCD Init For 1.44Inch LCD Panel with ST7735R.
	Lcd_WriteIndex(0x11);//Sleep exit 
	delay_ms (120);
		
	//ST7735R Frame Rate
	Lcd_WriteIndex(0xB1); 
	Lcd_WriteData(0x01); 
	Lcd_WriteData(0x2C); 
	Lcd_WriteData(0x2D); 

	Lcd_WriteIndex(0xB2); 
	Lcd_WriteData(0x01); 
	Lcd_WriteData(0x2C); 
	Lcd_WriteData(0x2D); 

	Lcd_WriteIndex(0xB3); 
	Lcd_WriteData(0x01); 
	Lcd_WriteData(0x2C); 
	Lcd_WriteData(0x2D); 
	Lcd_WriteData(0x01); 
	Lcd_WriteData(0x2C); 
	Lcd_WriteData(0x2D); 
	
	Lcd_WriteIndex(0xB4); //Column inversion 
	Lcd_WriteData(0x07); 
	
	//ST7735R Power Sequence
	Lcd_WriteIndex(0xC0); 
	Lcd_WriteData(0xA2); 
	Lcd_WriteData(0x02); 
	Lcd_WriteData(0x84); 
	Lcd_WriteIndex(0xC1); 
	Lcd_WriteData(0xC5); 

	Lcd_WriteIndex(0xC2); 
	Lcd_WriteData(0x0A); 
	Lcd_WriteData(0x00); 

	Lcd_WriteIndex(0xC3); 
	Lcd_WriteData(0x8A); 
	Lcd_WriteData(0x2A); 
	Lcd_WriteIndex(0xC4); 
	Lcd_WriteData(0x8A); 
	Lcd_WriteData(0xEE); 
	
	Lcd_WriteIndex(0xC5); //VCOM 
	Lcd_WriteData(0x0E); 
	
	Lcd_WriteIndex(0x36); //MX, MY, RGB mode 
	Lcd_WriteData(0xC8); 
	
	//ST7735R Gamma Sequence
	Lcd_WriteIndex(0xe0); 
	Lcd_WriteData(0x0f); 
	Lcd_WriteData(0x1a); 
	Lcd_WriteData(0x0f); 
	Lcd_WriteData(0x18); 
	Lcd_WriteData(0x2f); 
	Lcd_WriteData(0x28); 
	Lcd_WriteData(0x20); 
	Lcd_WriteData(0x22); 
	Lcd_WriteData(0x1f); 
	Lcd_WriteData(0x1b); 
	Lcd_WriteData(0x23); 
	Lcd_WriteData(0x37); 
	Lcd_WriteData(0x00); 	
	Lcd_WriteData(0x07); 
	Lcd_WriteData(0x02); 
	Lcd_WriteData(0x10); 

	Lcd_WriteIndex(0xe1); 
	Lcd_WriteData(0x0f); 
	Lcd_WriteData(0x1b); 
	Lcd_WriteData(0x0f); 
	Lcd_WriteData(0x17); 
	Lcd_WriteData(0x33); 
	Lcd_WriteData(0x2c); 
	Lcd_WriteData(0x29); 
	Lcd_WriteData(0x2e); 
	Lcd_WriteData(0x30); 
	Lcd_WriteData(0x30); 
	Lcd_WriteData(0x39); 
	Lcd_WriteData(0x3f); 
	Lcd_WriteData(0x00); 
	Lcd_WriteData(0x07); 
	Lcd_WriteData(0x03); 
	Lcd_WriteData(0x10);  
	
	Lcd_WriteIndex(0x2a);
	Lcd_WriteData(0x00);
	Lcd_WriteData(0x00);
	Lcd_WriteData(0x00);
	Lcd_WriteData(0x7f);

	Lcd_WriteIndex(0x2b);
	Lcd_WriteData(0x00);
	Lcd_WriteData(0x00);
	Lcd_WriteData(0x00);
	Lcd_WriteData(0x9f);
	
	Lcd_WriteIndex(0xF0); //Enable test command  
	Lcd_WriteData(0x01); 
	Lcd_WriteIndex(0xF6); //Disable ram power save mode 
	Lcd_WriteData(0x00); 
	
	Lcd_WriteIndex(0x3A); //65k mode 
	Lcd_WriteData(0x05); 
	
	
	Lcd_WriteIndex(0x29);//Display on	 
}


/***************************************************************************************

函数名：LCD_Set_Region
功能：设置lcd显示区域，在此区域写点数据自动换行
入口参数：xy起点和终点
返回值：无

//DevEBox  大越电子（嵌入式开发网）
//淘宝店铺：mcudev.taobao.com
//淘宝店铺：shop389957290.taobao.com	

**************************************************************************************/

void Lcd_SetRegion(uint16_t x_start,uint16_t y_start,uint16_t x_end,uint16_t y_end)
{		
	Lcd_WriteIndex(0x2a);
	Lcd_WriteData(0x00);
	Lcd_WriteData(x_start+2);
	Lcd_WriteData(0x00);
	Lcd_WriteData(x_end+2);

	Lcd_WriteIndex(0x2b);
	Lcd_WriteData(0x00);
	Lcd_WriteData(y_start+3);
	Lcd_WriteData(0x00);
	Lcd_WriteData(y_end+3);
	
	Lcd_WriteIndex(0x2c);

}

/***************************************************************************************

函数名：LCD_Set_XY
功能：设置lcd显示起始点
入口参数：xy坐标
返回值：无

//DevEBox  大越电子（嵌入式开发网）
//淘宝店铺：mcudev.taobao.com
//淘宝店铺：shop389957290.taobao.com	

**************************************************************************************/
void Lcd_SetXY(uint16_t x,uint16_t y)
{
  	Lcd_SetRegion(x,y,x,y);
}

	
/***************************************************************************************

函数名：LCD_DrawPoint
功能：画一个点
入口参数：无
返回值：无

//DevEBox  大越电子（嵌入式开发网）
//淘宝店铺：mcudev.taobao.com
//淘宝店铺：shop389957290.taobao.com	

**************************************************************************************/
void Gui_DrawPoint(uint16_t x,uint16_t y,uint16_t Data)
{
	Lcd_SetRegion(x,y,x+1,y+1);
	LCD_WriteData_16Bit(Data);

}    


/***************************************************************************************

函数名：Lcd_Clear
功能：全屏清屏函数
入口参数：填充颜色COLOR
返回值：无

//DevEBox  大越电子（嵌入式开发网）
//淘宝店铺：mcudev.taobao.com
//淘宝店铺：shop389957290.taobao.com	

**************************************************************************************/
void Lcd_Clear(uint16_t Color)               
{	
   unsigned int i,m;
   Lcd_SetRegion(0,0,X_MAX_PIXEL-1,Y_MAX_PIXEL-1);
   Lcd_WriteIndex(0x2C);
   for(i=0;i<X_MAX_PIXEL;i++)
    for(m=0;m<Y_MAX_PIXEL;m++)
    {	
	  	LCD_WriteData_16Bit(Color);
    }   
}





































/**************************************************************************************

//DevEBox  大越电子（嵌入式开发网）
//淘宝店铺：mcudev.taobao.com
//淘宝店铺：shop389957290.taobao.com	

**************************************************************************************/

