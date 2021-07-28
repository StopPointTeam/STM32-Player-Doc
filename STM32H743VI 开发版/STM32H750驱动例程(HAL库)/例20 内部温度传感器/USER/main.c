#include "sys.h" 
#include "usart.h" 
#include "delay.h" 
#include "led.h"
#include "key.h"

#include "LCD.h"
#include "Dis_Picture.h" 
#include "Text.h"	
#include "GBK_LibDrive.h"	

#include "adc.h"

/********************************************************************************/
//内部温度传感器 实验  


//STM32H7工程模板-HAL库函数版本
//DevEBox  大越创新
//淘宝店铺：mcudev.taobao.com
//淘宝店铺：shop389957290.taobao.com			

/********************************************************************************/

float temp; 

u8 tbuf[32];

int main(void)
{
	
	Cache_Enable();					//打开L1-Cache
	HAL_Init();						//初始化HAL库
	Stm32_Clock_Init(160,5,2,4);	//设置时钟,400Mhz
	delay_init(400);				//延时初始化
	uart_init(115200);				//串口初始化
	LED_Init();						//初始化LED时钟
	KEY_Init();
	
	
	LCD_Init();            //初始化2.0寸 240x320 高清屏  LCD显示
	GBK_Lib_Init();        //硬件GBK字库初始化--(如果使用不带字库的液晶屏版本，此处可以屏蔽，不做字库初始化）
	LCD_Clear(WHITE);      //清屏   
	
	MY_ADC3_Init();					//初始化ADC3
	
	
	POINT_COLOR=RED;
	
	Draw_Font16B(16,16,RED, "  STM32H7 ADC    ");
  Draw_Font16B(16,32,BLUE,"  嵌入式开发网   ");	 
	Draw_Font16B(16,48,BLUE,"mcudev.taobao.com"); 
		
	Draw_Font24B(16,80,RED,"Temp: 00.00C");	 


	while(1)
	{
		temp=Get_Temprate();		//得到温度值 
		
		sprintf((char*)tbuf,"Temp: %5.2f",temp); //显示无符号十进制整数
		
		Draw_Font24B(16,80,RED,tbuf);	 
	
		LED2_Toggle;
		delay_ms(250);	
		
	}
	
}



























/********************************************************************************/
//内部温度传感器 实验  


//STM32H7工程模板-HAL库函数版本
//DevEBox  大越创新
//淘宝店铺：mcudev.taobao.com
//淘宝店铺：shop389957290.taobao.com			

/********************************************************************************/
















