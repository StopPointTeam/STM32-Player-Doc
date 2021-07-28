#include "sys.h" 
#include "usart.h" 
#include "delay.h" 
#include "led.h"
#include "key.h"
#include "iwdg.h" 

//�������Ź�ʵ��  

//STM32H7����ģ��-HAL�⺯���汾
//DevEBox  ��Խ����
//�Ա����̣�mcudev.taobao.com
//�Ա����̣�shop389957290.taobao.com	

int main(void)
{
	Cache_Enable();											//��L1-Cache
	HAL_Init();													//��ʼ��HAL��
	Stm32_Clock_Init(160,5,2,4);				//����ʱ��,400Mhz 
	delay_init(400);										//��ʱ��ʼ��
	uart_init(115200);									//���ڳ�ʼ��
	LED_Init();													//��ʼ��LEDʱ��  
	KEY_Init();
	IWDG_Init(IWDG_PRESCALER_64,500); 	//��Ƶ��Ϊ64,����ֵΪ500,���ʱ��Ϊ1s	
	LED2(0);                       		 	//�ȵ���LED2
	
	while(1)
	{
		if(KEY_Scan(0)==KEY2_PRES)  	   //���K2���£�ι��
		{
			IWDG_Feed();    		          	//ι��
		}
		delay_ms(10);      
	}
}



































/***************************************************************************/

//STM32H7����ģ��-HAL�⺯���汾
//DevEBox  ��Խ����
//�Ա����̣�mcudev.taobao.com
//�Ա����̣�shop389957290.taobao.com	

/***************************************************************************/


