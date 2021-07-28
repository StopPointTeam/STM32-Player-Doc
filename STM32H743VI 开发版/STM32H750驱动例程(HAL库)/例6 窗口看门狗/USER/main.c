#include "sys.h" 
#include "usart.h" 
#include "delay.h" 
#include "led.h"
#include "key.h"
#include "wwdg.h"

//���ڿ��Ź�ʵ�� 

//STM32H7����ģ��-HAL�⺯���汾
//DevEBox  ��Խ����
//�Ա����̣�mcudev.taobao.com
//�Ա����̣�shop389957290.taobao.com	

int main(void)
{
	Cache_Enable();					      //��L1-Cache
	HAL_Init();					        	//��ʼ��HAL��
	Stm32_Clock_Init(160,5,2,4);	//����ʱ��,400Mhz 
	delay_init(400);							//��ʱ��ʼ��
	uart_init(115200);						//���ڳ�ʼ��
	LED_Init();										//��ʼ��LEDʱ��  
	KEY_Init();
	LED2(0);											//����LED2
	delay_ms(300);								//��ʱ300ms�ٳ�ʼ�����Ź�,LED0�ı仯"�ɼ�"
	WWDG_Init(0X7F,0X5F,WWDG_PRESCALER_8);	//������ֵΪ7F�����ڼĴ���Ϊ5F����Ƶ��Ϊ16
	
	while(1)
	{
		LED2(1);					//Ϩ��LED��
	}
}























/**********************************************************************************/

//STM32H7����ģ��-HAL�⺯���汾
//DevEBox  ��Խ����
//�Ա����̣�mcudev.taobao.com
//�Ա����̣�shop389957290.taobao.com	

/**********************************************************************************/






