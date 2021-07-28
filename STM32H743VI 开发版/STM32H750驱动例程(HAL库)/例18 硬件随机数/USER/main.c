#include "sys.h" 
#include "usart.h" 
#include "delay.h" 
#include "led.h"
#include "key.h"

#include "LCD.h"
#include "Dis_Picture.h" 
#include "Text.h"	
#include "GBK_LibDrive.h"	

#include "rng.h"

/**************************************************************************************/
//硬件随机数(RNG) 

//STM32H7工程模板-HAL库函数版本
//DevEBox  大越创新
//嵌入式开发网
//淘宝店铺：mcudev.taobao.com
//淘宝店铺：shop389957290.taobao.com	

/**************************************************************************************/

	u32 Random1;
	u16 Random2;
	u8 t=0,key;
	u8 tbuf[32];
	
int main(void)
{

	Cache_Enable();								//打开L1-Cache
	HAL_Init();										//初始化HAL库
	Stm32_Clock_Init(160,5,2,4);	//设置时钟,400Mhz
	delay_init(400);			     		//延时初始化
	uart_init(115200);						//串口初始化
	LED_Init();										//初始化LED时钟
	KEY_Init();

	LCD_Init();            //初始化2.0寸 240x320 高清屏  LCD显示
	GBK_Lib_Init();        //硬件GBK字库初始化--(如果使用不带字库的液晶屏版本，此处可以屏蔽，不做字库初始化）
	LCD_Clear(WHITE);      //清屏      								 
	
	
	Draw_Font16B(16,16,RED, "  STM32H7 RNG    ");
  Draw_Font16B(16,32,BLUE,"  嵌入式开发网   ");	 
	Draw_Font16B(16,48,BLUE,"mcudev.taobao.com"); 
	
	
	while(RNG_Init())	 		//初始化随机数发生器
		{
			Draw_Font16B(16,64,BLUE,"  RNG Error! ");	 
			delay_ms(200);
			Draw_Font16B(16,80,BLUE,"RNG Trying...");	 
		} 
		
	Draw_Font16B(16,64,BLUE,"RNG Ready!   ");	 
	Draw_Font16B(16,80,BLUE,"KEY2:Get Random");//按K2按键，获取32位随机数	 
//	Draw_Font16B(0,96,BLUE,"Random Num:");	 
 	Draw_Font16B(16,128,BLUE,"Random Num[0-9]:");
 		
		
	while(1) 
	{		
		key=KEY_Scan(0);
		
		if(key==KEY2_PRES)
		{
			key=0;//清除键值
			
			Random1=RNG_Get_RandomNum(); //得到32位串随机数
			
			sprintf((char*)tbuf,"Random-32bit: %11u",Random1); //显示无符号十进制整数
			
			Draw_Font16B(16,96,RED,tbuf); 
			
		} 
		if((t%20)==0)
		{
			LED2_Toggle;						//每200ms,翻转一次LED2
			
			Random2=RNG_Get_RandomRange(0,9);		//获取[0,9]区间的随机数
			sprintf((char*)tbuf,"Random-8bit: %u",Random2); //显示无符号十进制整数
			Draw_Font24B(16,148,RED,tbuf); 	//显示随机数
			
		}
		delay_ms(10);
		t++;
	}
}








/**************************************************************************************/

//STM32H7工程模板-HAL库函数版本
//DevEBox  大越创新
//嵌入式开发网
//淘宝店铺：mcudev.taobao.com
//淘宝店铺：shop389957290.taobao.com	

/**************************************************************************************/

