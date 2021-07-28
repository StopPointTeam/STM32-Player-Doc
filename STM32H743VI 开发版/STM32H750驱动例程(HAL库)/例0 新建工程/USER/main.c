#include "sys.h"
#include "delay.h"
#include "usart.h" 

//ASTM32H750 ������ ʵ��0

//STM32H7����ģ��-HAL�⺯���汾
//DevEBox  ��Խ����
//�Ա����̣�mcudev.taobao.com
//�Ա����̣�shop389957290.taobao.com	

/////////////////////////////////////////////////////////////////////////////////

int main(void)
{
	u8 T = 0;
	Cache_Enable();					//��L1-Cache
	HAL_Init();						//��ʼ��HAL��
	Stm32_Clock_Init(160,5,2,4);	//����ʱ��,400Mhz
	delay_init(400);				//��ʱ��ʼ��
	uart_init(115200);				//���ڳ�ʼ��
	while(1)
	{ 
		printf("mcudev.taobao.com T=%d\r\n",T);
		delay_ms(500);
		T++;
	}
}















//STM32H7����ģ��-HAL�⺯���汾
//DevEBox  ��Խ����
//�Ա����̣�mcudev.taobao.com
//�Ա����̣�shop389957290.taobao.com	









