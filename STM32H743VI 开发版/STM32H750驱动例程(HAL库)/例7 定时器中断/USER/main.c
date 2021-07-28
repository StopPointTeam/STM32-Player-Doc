#include "sys.h" 
#include "usart.h" 
#include "delay.h" 
#include "led.h"
#include "key.h"
#include "timer.h" 



//��ʱ���ж�ʵ�� 

//STM32H7����ģ��-HAL�⺯���汾
//DevEBox  ��Խ����
//�Ա����̣�mcudev.taobao.com
//�Ա����̣�shop389957290.taobao.com	

int main(void)
{
	Cache_Enable();									//��L1-Cache
	HAL_Init();											//��ʼ��HAL��
	Stm32_Clock_Init(160,5,2,4);		//����ʱ��,400Mhz 
	delay_init(400);								//��ʱ��ʼ��
	uart_init(115200);							//���ڳ�ʼ��
	LED_Init();											//��ʼ��LEDʱ��  
	KEY_Init();
	TIM3_Init(5000-1,20000-1);  		//10Khz�ļ���Ƶ�ʣ�����5K��Ϊ500ms     
	
	while(1)
	{
		LED2_Toggle;
		delay_ms(200);
	}
	
	
}

































/*********************************************************************************/

//STM32H7����ģ��-HAL�⺯���汾
//DevEBox  ��Խ����
//�Ա����̣�mcudev.taobao.com
//�Ա����̣�shop389957290.taobao.com	

/*********************************************************************************/

