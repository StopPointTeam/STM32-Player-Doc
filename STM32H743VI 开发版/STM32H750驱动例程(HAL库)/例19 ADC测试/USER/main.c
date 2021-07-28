#include "sys.h" 
#include "usart.h" 
#include "delay.h" 
#include "led.h"
#include "key.h"

#include "LCD.h"
#include "Dis_Picture.h" 
#include "Text.h"	
#include "GBK_LibDrive.h"	

#include "adc.h"

  
/********************************************************************************/
//ADC ʵ�� PC0���ţ���ӦADC1��CH10ͨ��������������Ϣ���ο������ֲ�

//STM32H7����ģ��-HAL�⺯���汾
//DevEBox  ��Խ����
//�Ա����̣�mcudev.taobao.com
//�Ա����̣�shop389957290.taobao.com	

/******************************************************************************/

	u16 adcx;
	float temp;
  u8 tbuf[32];

int main(void)
{

	Cache_Enable();								//��L1-Cache
	HAL_Init();										//��ʼ��HAL��
	Stm32_Clock_Init(160,5,2,4);	//����ʱ��,400Mhz
	delay_init(400);							//��ʱ��ʼ��
	uart_init(115200);						//���ڳ�ʼ��
	LED_Init();										//��ʼ��LEDʱ��
	KEY_Init();
	
	LCD_Init();            //��ʼ��2.0�� 240x320 ������  LCD��ʾ
	GBK_Lib_Init();        //Ӳ��GBK�ֿ��ʼ��--(���ʹ�ò����ֿ��Һ�����汾���˴��������Σ������ֿ��ʼ����
	LCD_Clear(WHITE);      //����  
	
	MY_ADC_Init();					//��ʼ��ADC1ͨ��--PC0���ţ���ӦADC1��CH10ͨ��������������Ϣ����ο������ֲ�
	
	Draw_Font16B(16,16,RED,"  STM32H7 ADC    ");
  Draw_Font16B(16,32,BLUE,"  Ƕ��ʽ������   ");	 
	Draw_Font16B(16,48,BLUE,"mcudev.taobao.com"); 

  
	while(1)
	{
		adcx=Get_Adc_Average(ADC_CHANNEL_10,20);//��ȡͨ��10��ת��ֵ��20��ȡƽ��  PC0���ţ���ӦADC1��CH10ͨ��������������Ϣ����ο������ֲ�
		
		sprintf((char*)tbuf,"ADC_CH10(PC0):"); //��ʾ�޷���ʮ����������
		Draw_Font24B(8,80,RED,tbuf); //��ʾADCC�������ԭʼֵ
		
		sprintf((char*)tbuf,"0x%4X",adcx); //��ʾ�޷���ʮ����������
		Draw_Font24B(120,110,RED,tbuf); //��ʾADCC�������ԭʼֵ
		
		temp=(float)adcx*(3.3/65536);         //��ȡ�����Ĵ�С����ʵ�ʵ�ѹֵ������3.1111

		sprintf((char*)tbuf,"CH10_VDD: %5.3f V",temp); //��ʾ�޷���ʮ��������
		Draw_Font24B(8,140,RED,tbuf); //��ʾ��ѹֵ
			
		LED2_Toggle;
		delay_ms(250);	
		
	}
}






































/********************************************************************************/
//ADC ʵ�� 

//STM32H7����ģ��-HAL�⺯���汾
//DevEBox  ��Խ����
//�Ա����̣�mcudev.taobao.com
//�Ա����̣�shop389957290.taobao.com	

/******************************************************************************/









































