#include "sys.h" 
#include "usart.h" 
#include "delay.h" 
#include "led.h"
#include "key.h"
#include "mpu.h" 


/***************************************************************************************************/
//�ڴ汣����MPU��ʵ��  


//STM32H7����ģ��-HAL�⺯���汾
//DevEBox  ��Խ����
//�Ա����̣�mcudev.taobao.com
//�Ա����̣�shop389957290.taobao.com	

/***************************************************************************************************/

u8 mpudata[128] __attribute__((at(0X20002000)));								//����һ������

int main(void)
{
	u8 i=0;
	u8 key; 
	Cache_Enable();															//��L1-Cache
	HAL_Init();																	//��ʼ��HAL��
	Stm32_Clock_Init(160,5,2,4);								//����ʱ��,400Mhz
	delay_init(400);														//��ʱ��ʼ��
	uart_init(115200);													//���ڳ�ʼ��
	LED_Init();																	//��ʼ��LEDʱ��  
	KEY_Init();
	printf("\r\n\r\nMPU closed!\r\n");					//��ʾMPU�ر�
	while(1)  
	{
		key=KEY_Scan(0);
		
     if(key==KEY1_PRES)														//ʹ��MPU�������� mpudata;
        {
            MPU_Set_Protection(0X20002000,128,1,MPU_REGION_PRIV_RO_URO,0,0,1);	//ֻ��,��ֹ����,��ֹcatch,������ 
            printf("MPU open!\r\n");											//��ʾMPU��
        }
		 else if(key==KEY2_PRES)												//��������д�����ݣ����������MPU�����Ļ�������ڴ���ʴ���
        {
					printf("Start Writing data...\r\n");
					sprintf((char*)mpudata,"MPU test array %d",i);
					printf("Data Write finshed!\r\n");
					printf("Array data is:%s\r\n",mpudata);  //�������ж�ȡ���ݣ�������û�п���MPU��������������ڴ���ʴ���
        }
		 else delay_ms(10);
		
				i++;
		if((i%50)==0) LED2_Toggle;												//LED2ȡ�� 
	}
}


































/***************************************************************************************************/

//STM32H7����ģ��-HAL�⺯���汾
//DevEBox  ��Խ����
//�Ա����̣�mcudev.taobao.com
//�Ա����̣�shop389957290.taobao.com	

/***************************************************************************************************/



