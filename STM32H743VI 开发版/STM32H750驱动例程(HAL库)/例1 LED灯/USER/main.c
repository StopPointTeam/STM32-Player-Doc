#include "sys.h" 
#include "usart.h" 
#include "delay.h" 
#include "led.h" 



//LED灯实验  

//STM32H7工程模板-HAL库函数版本
//DevEBox  大越创新
//淘宝店铺：mcudev.taobao.com
//淘宝店铺：shop389957290.taobao.com	

int main(void)
{
	Cache_Enable();					//打开L1-Cache
	
	HAL_Init();						//初始化HAL库
	
	Stm32_Clock_Init(160,5,2,4);	//设置时钟,400Mhz
	
	delay_init(400);				//延时初始化
	
	uart_init(115200);				//串口初始化
	
	LED_Init();						//初始化LED时钟  
	
	while(1)
	{
		
		LED2(1);					//DS1灭
		delay_ms(500);
		
		LED2(0);					//DS1亮
		delay_ms(500);
	}
}



















//STM32H7工程模板-HAL库函数版本
//DevEBox  大越创新
//淘宝店铺：mcudev.taobao.com
//淘宝店铺：shop389957290.taobao.com	





