#include "sys.h" 
#include "usart.h" 
#include "delay.h" 
#include "led.h"
#include "key.h"
#include "timer.h" 

/************************************************************************************/
//PWM���ʵ�� 


//STM32H7����ģ��-HAL�⺯���汾
//DevEBox  ��Խ����
//�Ա����̣�mcudev.taobao.com
//�Ա����̣�shop389957290.taobao.com	

/************************************************************************************/


	u8 dir=1;
	u16 led0pwmval=0; 
	
	
int main(void)
{

	Cache_Enable();											//��L1-Cache
	HAL_Init();													//��ʼ��HAL��
	Stm32_Clock_Init(160,5,2,4);				//����ʱ��,400Mhz 
	delay_init(400);										//��ʱ��ʼ��
	uart_init(115200);									//���ڳ�ʼ��
	LED_Init();													//��ʼ��LEDʱ��  
	KEY_Init();
	TIM3_PWM_Init(500-1,200-1);					//200M/200=1M�ļ���Ƶ�ʣ��Զ���װ��Ϊ500����ôPWMƵ��Ϊ1M/500=2kHZ
	
	
	while(1)
	{
		delay_ms(10);	
		
		if(dir)led0pwmval++;							//dir==1 led0pwmval����
		else led0pwmval--;				 		    //dir==0 led0pwmval�ݼ� 

		if(led0pwmval>300)dir=0;			  	//led0pwmval����300�󣬷���Ϊ�ݼ�
		if(led0pwmval==0)dir=1;			      //led0pwmval�ݼ���0�󣬷����Ϊ����
		
		TIM_SetTIM3Compare4(led0pwmval);	//�޸ıȽ�ֵ���޸�ռ�ձ�
	}
	
	
}





























/************************************************************************************/

//STM32H7����ģ��-HAL�⺯���汾
//DevEBox  ��Խ����
//�Ա����̣�mcudev.taobao.com
//�Ա����̣�shop389957290.taobao.com	

/************************************************************************************/







