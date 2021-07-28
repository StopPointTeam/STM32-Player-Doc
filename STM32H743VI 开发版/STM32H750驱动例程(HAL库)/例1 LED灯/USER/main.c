#include "sys.h" 
#include "usart.h" 
#include "delay.h" 
#include "led.h" 



//LED��ʵ��  

//STM32H7����ģ��-HAL�⺯���汾
//DevEBox  ��Խ����
//�Ա����̣�mcudev.taobao.com
//�Ա����̣�shop389957290.taobao.com	

int main(void)
{
	Cache_Enable();					//��L1-Cache
	
	HAL_Init();						//��ʼ��HAL��
	
	Stm32_Clock_Init(160,5,2,4);	//����ʱ��,400Mhz
	
	delay_init(400);				//��ʱ��ʼ��
	
	uart_init(115200);				//���ڳ�ʼ��
	
	LED_Init();						//��ʼ��LEDʱ��  
	
	while(1)
	{
		
		LED2(1);					//DS1��
		delay_ms(500);
		
		LED2(0);					//DS1��
		delay_ms(500);
	}
}



















//STM32H7����ģ��-HAL�⺯���汾
//DevEBox  ��Խ����
//�Ա����̣�mcudev.taobao.com
//�Ա����̣�shop389957290.taobao.com	





