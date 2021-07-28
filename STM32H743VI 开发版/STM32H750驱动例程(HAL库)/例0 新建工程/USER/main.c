#include "sys.h"
#include "delay.h"
#include "usart.h" 

//ASTM32H750 开发板 实验0

//STM32H7工程模板-HAL库函数版本
//DevEBox  大越创新
//淘宝店铺：mcudev.taobao.com
//淘宝店铺：shop389957290.taobao.com	

/////////////////////////////////////////////////////////////////////////////////

int main(void)
{
	u8 T = 0;
	Cache_Enable();					//打开L1-Cache
	HAL_Init();						//初始化HAL库
	Stm32_Clock_Init(160,5,2,4);	//设置时钟,400Mhz
	delay_init(400);				//延时初始化
	uart_init(115200);				//串口初始化
	while(1)
	{ 
		printf("mcudev.taobao.com T=%d\r\n",T);
		delay_ms(500);
		T++;
	}
}















//STM32H7工程模板-HAL库函数版本
//DevEBox  大越创新
//淘宝店铺：mcudev.taobao.com
//淘宝店铺：shop389957290.taobao.com	









