#include "sys.h" 
#include "usart.h" 
#include "delay.h" 
#include "led.h"
#include "key.h"
#include "timer.h" 



//定时器中断实验 

//STM32H7工程模板-HAL库函数版本
//DevEBox  大越创新
//淘宝店铺：mcudev.taobao.com
//淘宝店铺：shop389957290.taobao.com	

int main(void)
{
	Cache_Enable();									//打开L1-Cache
	HAL_Init();											//初始化HAL库
	Stm32_Clock_Init(160,5,2,4);		//设置时钟,400Mhz 
	delay_init(400);								//延时初始化
	uart_init(115200);							//串口初始化
	LED_Init();											//初始化LED时钟  
	KEY_Init();
	TIM3_Init(5000-1,20000-1);  		//10Khz的计数频率，计数5K次为500ms     
	
	while(1)
	{
		LED2_Toggle;
		delay_ms(200);
	}
	
	
}

































/*********************************************************************************/

//STM32H7工程模板-HAL库函数版本
//DevEBox  大越创新
//淘宝店铺：mcudev.taobao.com
//淘宝店铺：shop389957290.taobao.com	

/*********************************************************************************/

