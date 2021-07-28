#include "sys.h" 
#include "usart.h" 
#include "delay.h" 
#include "led.h"
#include "key.h"
#include "exti.h" 

//�ⲿ�ж�ʵ��  

//STM32H7����ģ��-HAL�⺯���汾
//DevEBox  ��Խ����
//�Ա����̣�mcudev.taobao.com
//�Ա����̣�shop389957290.taobao.com	

int main(void)
{
	Cache_Enable();								 	//��L1-Cache
	HAL_Init();						  		    //��ʼ��HAL��
	Stm32_Clock_Init(160,5,2,4); 		//����ʱ��,400Mhz 
	delay_init(400);								//��ʱ��ʼ��
	uart_init(115200);							//���ڳ�ʼ��
	LED_Init();											//��ʼ��LEDʱ��  
	EXTI_Init();										//��ʼ���ⲿ�ж�����
	LED2(0);									      //�ȵ���LED2
	while(1)
	{
		printf("\r\n mcudev.taobao.com \r\n");	
		delay_ms(1000);	  
	}
}




















//STM32H7��������-HAL�⺯���汾
//DevEBox  ��Խ����
//�Ա����̣�mcudev.taobao.com
//�Ա����̣�shop389957290.taobao.com	

