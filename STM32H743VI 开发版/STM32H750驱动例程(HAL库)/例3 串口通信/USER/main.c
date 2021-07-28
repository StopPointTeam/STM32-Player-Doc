#include "sys.h" 
#include "usart.h" 
#include "delay.h" 
#include "led.h"

//����ͨ��ʵ��  

//STM32H7����ģ��-HAL�⺯���汾
//DevEBox  ��Խ����
//�Ա����̣�mcudev.taobao.com
//�Ա����̣�shop389957290.taobao.com	


	u8 t;
	u8 len;	
	u16 times=0;
	
	
int main(void)
{

	Cache_Enable();					    	//��L1-Cache
	HAL_Init();										//��ʼ��HAL��
	Stm32_Clock_Init(160,5,2,4);	//����ʱ��,400Mhz 
	delay_init(400);							//��ʱ��ʼ��
	uart_init(115200);						//���ڳ�ʼ��
	LED_Init();										//��ʼ��LEDʱ��  
	
	
	while(1)
	{
		if(USART_RX_STA&0x8000)
		{					   
			len=USART_RX_STA&0x3fff;						//�õ��˴ν��յ������ݳ���
			printf("\r\n�㷢�͵���Ϣ:\r\n");
			for(t=0;t<len;t++)
			{
				USART1->TDR=USART_RX_BUF[t];
				while((USART1->ISR&0X40)==0);			//�ȴ����ͽ���
			}
			printf("\r\n\r\n");									//���뻻��
			USART_RX_STA=0; 
		}
		else
		{
			times++;
			if(times%1000==0)
			{
				times=0;													//��������
				printf("\r\n STM32H750������ ����ʵ�� \r\n");
				printf("\r\n mcudev.taobao.com \r\n");
				printf("\r\n DevEBox  ��Խ���� \r\n");
				
			}
			if(times%200==0)printf("����������,�Իس�������\r\n");  
			if(times%30==0)LED2_Toggle;					//��˸LED,��ʾϵͳ��������.
			delay_ms(10);   
		}
	}
}

































/******************************************************************************************/

//STM32H7����ģ��-HAL�⺯���汾
//DevEBox  ��Խ����
//�Ա����̣�mcudev.taobao.com
//�Ա����̣�shop389957290.taobao.com	


/******************************************************************************************/










