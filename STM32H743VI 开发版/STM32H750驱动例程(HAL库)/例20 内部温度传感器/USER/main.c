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
//�ڲ��¶ȴ����� ʵ��  


//STM32H7����ģ��-HAL�⺯���汾
//DevEBox  ��Խ����
//�Ա����̣�mcudev.taobao.com
//�Ա����̣�shop389957290.taobao.com			

/********************************************************************************/

float temp; 

u8 tbuf[32];

int main(void)
{
	
	Cache_Enable();					//��L1-Cache
	HAL_Init();						//��ʼ��HAL��
	Stm32_Clock_Init(160,5,2,4);	//����ʱ��,400Mhz
	delay_init(400);				//��ʱ��ʼ��
	uart_init(115200);				//���ڳ�ʼ��
	LED_Init();						//��ʼ��LEDʱ��
	KEY_Init();
	
	
	LCD_Init();            //��ʼ��2.0�� 240x320 ������  LCD��ʾ
	GBK_Lib_Init();        //Ӳ��GBK�ֿ��ʼ��--(���ʹ�ò����ֿ��Һ�����汾���˴��������Σ������ֿ��ʼ����
	LCD_Clear(WHITE);      //����   
	
	MY_ADC3_Init();					//��ʼ��ADC3
	
	
	POINT_COLOR=RED;
	
	Draw_Font16B(16,16,RED, "  STM32H7 ADC    ");
  Draw_Font16B(16,32,BLUE,"  Ƕ��ʽ������   ");	 
	Draw_Font16B(16,48,BLUE,"mcudev.taobao.com"); 
		
	Draw_Font24B(16,80,RED,"Temp: 00.00C");	 


	while(1)
	{
		temp=Get_Temprate();		//�õ��¶�ֵ 
		
		sprintf((char*)tbuf,"Temp: %5.2f",temp); //��ʾ�޷���ʮ��������
		
		Draw_Font24B(16,80,RED,tbuf);	 
	
		LED2_Toggle;
		delay_ms(250);	
		
	}
	
}



























/********************************************************************************/
//�ڲ��¶ȴ����� ʵ��  


//STM32H7����ģ��-HAL�⺯���汾
//DevEBox  ��Խ����
//�Ա����̣�mcudev.taobao.com
//�Ա����̣�shop389957290.taobao.com			

/********************************************************************************/
















