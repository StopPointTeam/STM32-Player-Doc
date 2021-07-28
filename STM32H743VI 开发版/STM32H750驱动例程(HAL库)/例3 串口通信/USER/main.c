#include "sys.h" 
#include "usart.h" 
#include "delay.h" 
#include "led.h"

//串口通信实验  

//STM32H7工程模板-HAL库函数版本
//DevEBox  大越创新
//淘宝店铺：mcudev.taobao.com
//淘宝店铺：shop389957290.taobao.com	


	u8 t;
	u8 len;	
	u16 times=0;
	
	
int main(void)
{

	Cache_Enable();					    	//打开L1-Cache
	HAL_Init();										//初始化HAL库
	Stm32_Clock_Init(160,5,2,4);	//设置时钟,400Mhz 
	delay_init(400);							//延时初始化
	uart_init(115200);						//串口初始化
	LED_Init();										//初始化LED时钟  
	
	
	while(1)
	{
		if(USART_RX_STA&0x8000)
		{					   
			len=USART_RX_STA&0x3fff;						//得到此次接收到的数据长度
			printf("\r\n你发送的消息:\r\n");
			for(t=0;t<len;t++)
			{
				USART1->TDR=USART_RX_BUF[t];
				while((USART1->ISR&0X40)==0);			//等待发送结束
			}
			printf("\r\n\r\n");									//插入换行
			USART_RX_STA=0; 
		}
		else
		{
			times++;
			if(times%1000==0)
			{
				times=0;													//计数清零
				printf("\r\n STM32H750开发板 串口实验 \r\n");
				printf("\r\n mcudev.taobao.com \r\n");
				printf("\r\n DevEBox  大越创新 \r\n");
				
			}
			if(times%200==0)printf("请输入数据,以回车键结束\r\n");  
			if(times%30==0)LED2_Toggle;					//闪烁LED,提示系统正在运行.
			delay_ms(10);   
		}
	}
}

































/******************************************************************************************/

//STM32H7工程模板-HAL库函数版本
//DevEBox  大越创新
//淘宝店铺：mcudev.taobao.com
//淘宝店铺：shop389957290.taobao.com	


/******************************************************************************************/










