#include "sys.h" 
#include "usart.h" 
#include "delay.h" 
#include "led.h"
#include "key.h"
#include "timer.h" 

/************************************************************************************/
//PWM输出实验 


//STM32H7工程模板-HAL库函数版本
//DevEBox  大越创新
//淘宝店铺：mcudev.taobao.com
//淘宝店铺：shop389957290.taobao.com	

/************************************************************************************/


	u8 dir=1;
	u16 led0pwmval=0; 
	
	
int main(void)
{

	Cache_Enable();											//打开L1-Cache
	HAL_Init();													//初始化HAL库
	Stm32_Clock_Init(160,5,2,4);				//设置时钟,400Mhz 
	delay_init(400);										//延时初始化
	uart_init(115200);									//串口初始化
	LED_Init();													//初始化LED时钟  
	KEY_Init();
	TIM3_PWM_Init(500-1,200-1);					//200M/200=1M的计数频率，自动重装载为500，那么PWM频率为1M/500=2kHZ
	
	
	while(1)
	{
		delay_ms(10);	
		
		if(dir)led0pwmval++;							//dir==1 led0pwmval递增
		else led0pwmval--;				 		    //dir==0 led0pwmval递减 

		if(led0pwmval>300)dir=0;			  	//led0pwmval到达300后，方向为递减
		if(led0pwmval==0)dir=1;			      //led0pwmval递减到0后，方向改为递增
		
		TIM_SetTIM3Compare4(led0pwmval);	//修改比较值，修改占空比
	}
	
	
}





























/************************************************************************************/

//STM32H7工程模板-HAL库函数版本
//DevEBox  大越创新
//淘宝店铺：mcudev.taobao.com
//淘宝店铺：shop389957290.taobao.com	

/************************************************************************************/







