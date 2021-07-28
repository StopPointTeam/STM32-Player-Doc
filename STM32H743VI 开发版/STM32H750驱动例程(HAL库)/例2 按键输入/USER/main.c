#include "sys.h" 
#include "usart.h" 
#include "delay.h" 
#include "led.h"
#include "key.h" 

//按键输入实验  

//STM32H7工程模板-HAL库函数版本
//DevEBox  大越创新
//淘宝店铺：mcudev.taobao.com
//淘宝店铺：shop389957290.taobao.com	

u8 key;
u8 LED2_sta = 0;

int main(void)
{
	
	
	Cache_Enable();								//打开L1-Cache
	HAL_Init();				        		//初始化HAL库
	Stm32_Clock_Init(160,5,2,4);	//设置时钟,400Mhz 
	delay_init(400);							//延时初始化
	uart_init(115200);						//串口初始化
	LED_Init();										//初始化LED时钟  
	KEY_Init();         		//初始化与按键连接的硬件接口
	LED2(0);					//先点亮LED2
	while(1)
	{
		key=KEY_Scan(0); 		//得到键值
		
	  if(key)
		{						   
			switch(key)
			{	
				
				case KEY1_PRES:	//控制LED2点亮
					
				  LED2_sta=0;
					break;

				case KEY2_PRES:	//控制LED2翻转	 
	 				LED2_sta=!LED2_sta;
					break;

			}
			
			LED2(LED2_sta);		//控制LED1状态
		}
		else 
			delay_ms(10); 
	}
}
