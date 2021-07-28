#include "sys.h" 
#include "usart.h" 
#include "delay.h" 
#include "led.h"
#include "key.h"

#include "LCD.h"
#include "Dis_Picture.h" 
#include "Text.h"	
#include "GBK_LibDrive.h"	

#include "rng.h"

/**************************************************************************************/
//Ӳ�������(RNG) 

//STM32H7����ģ��-HAL�⺯���汾
//DevEBox  ��Խ����
//Ƕ��ʽ������
//�Ա����̣�mcudev.taobao.com
//�Ա����̣�shop389957290.taobao.com	

/**************************************************************************************/

	u32 Random1;
	u16 Random2;
	u8 t=0,key;
	u8 tbuf[32];
	
int main(void)
{

	Cache_Enable();								//��L1-Cache
	HAL_Init();										//��ʼ��HAL��
	Stm32_Clock_Init(160,5,2,4);	//����ʱ��,400Mhz
	delay_init(400);			     		//��ʱ��ʼ��
	uart_init(115200);						//���ڳ�ʼ��
	LED_Init();										//��ʼ��LEDʱ��
	KEY_Init();

	LCD_Init();            //��ʼ��2.0�� 240x320 ������  LCD��ʾ
	GBK_Lib_Init();        //Ӳ��GBK�ֿ��ʼ��--(���ʹ�ò����ֿ��Һ�����汾���˴��������Σ������ֿ��ʼ����
	LCD_Clear(WHITE);      //����      								 
	
	
	Draw_Font16B(16,16,RED, "  STM32H7 RNG    ");
  Draw_Font16B(16,32,BLUE,"  Ƕ��ʽ������   ");	 
	Draw_Font16B(16,48,BLUE,"mcudev.taobao.com"); 
	
	
	while(RNG_Init())	 		//��ʼ�������������
		{
			Draw_Font16B(16,64,BLUE,"  RNG Error! ");	 
			delay_ms(200);
			Draw_Font16B(16,80,BLUE,"RNG Trying...");	 
		} 
		
	Draw_Font16B(16,64,BLUE,"RNG Ready!   ");	 
	Draw_Font16B(16,80,BLUE,"KEY2:Get Random");//��K2��������ȡ32λ�����	 
//	Draw_Font16B(0,96,BLUE,"Random Num:");	 
 	Draw_Font16B(16,128,BLUE,"Random Num[0-9]:");
 		
		
	while(1) 
	{		
		key=KEY_Scan(0);
		
		if(key==KEY2_PRES)
		{
			key=0;//�����ֵ
			
			Random1=RNG_Get_RandomNum(); //�õ�32λ�������
			
			sprintf((char*)tbuf,"Random-32bit: %11u",Random1); //��ʾ�޷���ʮ��������
			
			Draw_Font16B(16,96,RED,tbuf); 
			
		} 
		if((t%20)==0)
		{
			LED2_Toggle;						//ÿ200ms,��תһ��LED2
			
			Random2=RNG_Get_RandomRange(0,9);		//��ȡ[0,9]����������
			sprintf((char*)tbuf,"Random-8bit: %u",Random2); //��ʾ�޷���ʮ��������
			Draw_Font24B(16,148,RED,tbuf); 	//��ʾ�����
			
		}
		delay_ms(10);
		t++;
	}
}








/**************************************************************************************/

//STM32H7����ģ��-HAL�⺯���汾
//DevEBox  ��Խ����
//Ƕ��ʽ������
//�Ա����̣�mcudev.taobao.com
//�Ա����̣�shop389957290.taobao.com	

/**************************************************************************************/

