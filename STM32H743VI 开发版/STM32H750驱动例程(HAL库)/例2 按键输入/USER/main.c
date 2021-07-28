#include "sys.h" 
#include "usart.h" 
#include "delay.h" 
#include "led.h"
#include "key.h" 

//��������ʵ��  

//STM32H7����ģ��-HAL�⺯���汾
//DevEBox  ��Խ����
//�Ա����̣�mcudev.taobao.com
//�Ա����̣�shop389957290.taobao.com	

u8 key;
u8 LED2_sta = 0;

int main(void)
{
	
	
	Cache_Enable();								//��L1-Cache
	HAL_Init();				        		//��ʼ��HAL��
	Stm32_Clock_Init(160,5,2,4);	//����ʱ��,400Mhz 
	delay_init(400);							//��ʱ��ʼ��
	uart_init(115200);						//���ڳ�ʼ��
	LED_Init();										//��ʼ��LEDʱ��  
	KEY_Init();         		//��ʼ���밴�����ӵ�Ӳ���ӿ�
	LED2(0);					//�ȵ���LED2
	while(1)
	{
		key=KEY_Scan(0); 		//�õ���ֵ
		
	  if(key)
		{						   
			switch(key)
			{	
				
				case KEY1_PRES:	//����LED2����
					
				  LED2_sta=0;
					break;

				case KEY2_PRES:	//����LED2��ת	 
	 				LED2_sta=!LED2_sta;
					break;

			}
			
			LED2(LED2_sta);		//����LED1״̬
		}
		else 
			delay_ms(10); 
	}
}
