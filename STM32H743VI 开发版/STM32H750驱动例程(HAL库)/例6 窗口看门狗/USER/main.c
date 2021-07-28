#include "sys.h" 
#include "usart.h" 
#include "delay.h" 
#include "led.h"
#include "key.h"
#include "wwdg.h"

//窗口看门狗实验 

//STM32H7工程模板-HAL库函数版本
//DevEBox  大越创新
//淘宝店铺：mcudev.taobao.com
//淘宝店铺：shop389957290.taobao.com	

int main(void)
{
	Cache_Enable();					      //打开L1-Cache
	HAL_Init();					        	//初始化HAL库
	Stm32_Clock_Init(160,5,2,4);	//设置时钟,400Mhz 
	delay_init(400);							//延时初始化
	uart_init(115200);						//串口初始化
	LED_Init();										//初始化LED时钟  
	KEY_Init();
	LED2(0);											//点亮LED2
	delay_ms(300);								//延时300ms再初始化看门狗,LED0的变化"可见"
	WWDG_Init(0X7F,0X5F,WWDG_PRESCALER_8);	//计数器值为7F，窗口寄存器为5F，分频数为16
	
	while(1)
	{
		LED2(1);					//熄灭LED灯
	}
}























/**********************************************************************************/

//STM32H7工程模板-HAL库函数版本
//DevEBox  大越创新
//淘宝店铺：mcudev.taobao.com
//淘宝店铺：shop389957290.taobao.com	

/**********************************************************************************/






