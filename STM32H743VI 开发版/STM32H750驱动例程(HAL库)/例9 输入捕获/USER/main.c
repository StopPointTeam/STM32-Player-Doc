#include "sys.h" 
#include "usart.h" 
#include "delay.h" 
#include "led.h"
#include "key.h"
#include "timer.h" 

/*****************************************************************************************************/
//输入捕获实验  


//STM32H7工程模板-HAL库函数版本
//DevEBox  大越创新
//淘宝店铺：mcudev.taobao.com
//淘宝店铺：shop389957290.taobao.com	

/*****************************************************************************************************/

extern u8  TIM5CH1_CAPTURE_STA;		//输入捕获状态		    				
extern u32	TIM5CH1_CAPTURE_VAL;	//输入捕获值 

int main(void)
{
	long long temp=0;
	Cache_Enable();										//打开L1-Cache
	HAL_Init();				        				//初始化HAL库
	Stm32_Clock_Init(160,5,2,4);			//设置时钟,400Mhz 
	delay_init(400);									//延时初始化
	uart_init(115200);								//串口初始化
	LED_Init();												//初始化LED时钟  
	KEY_Init();
	
	TIM3_PWM_Init(500-1,200-1);     				//200M/200=1M的计数频率，自动重装载为500，那么PWM频率为1M/500=2kHZ
	TIM5_CH1_Cap_Init(0XFFFFFFFF,200-1); 		//以1MHZ的频率计数
	
	LED2(0);    //点亮LED灯
	
	while(1)
	{
		delay_ms(10);
		TIM_SetTIM3Compare4(TIM_GetTIM3Capture4()+1); 
		if(TIM_GetTIM3Capture4()==300)TIM_SetTIM3Compare4(0);        
		if(TIM5CH1_CAPTURE_STA&0X80)     											   //成功捕获到了一次高电平
		{
			temp=TIM5CH1_CAPTURE_STA&0X3F; 
			temp*=0XFFFFFFFF;		 	    //溢出时间总和
			temp+=TIM5CH1_CAPTURE_VAL;      //得到总的高电平时间
			printf("HIGH:%lld us\r\n",temp);//打印总的高点平时间
			TIM5CH1_CAPTURE_STA=0;          //开启下一次捕获
		}
	} 
}


















































/*****************************************************************************************************/

//STM32H7工程模板-HAL库函数版本
//DevEBox  大越创新
//淘宝店铺：mcudev.taobao.com
//淘宝店铺：shop389957290.taobao.com	

/*****************************************************************************************************/



