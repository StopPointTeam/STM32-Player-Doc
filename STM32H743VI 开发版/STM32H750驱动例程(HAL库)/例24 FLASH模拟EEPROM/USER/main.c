#include "sys.h" 
#include "usart.h" 
#include "delay.h" 
#include "led.h"
#include "key.h"
#include "LCD.h"
#include "Dis_Picture.h" 
#include "Text.h"	
#include "GBK_LibDrive.h"	
#include "mpu.h"

#include "w25qxx.h"

#include "stmflash.h" 

/**************************************************************************/

//FLASHģ��EEPROM ʵ�� 

//STM32H7����ģ��-HAL�⺯���汾
//DevEBox  ��Խ����
//�Ա����̣�mcudev.taobao.com
//�Ա����̣�shop389957290.taobao.com				


/**************************************************************************/


//Ҫд�뵽STM32 FLASH���ַ�������
const u8 TEXT_Buffer[]={"STM32 FLASH TEST"};
#define TEXT_LENTH sizeof(TEXT_Buffer)	 		  	//���鳤��	
#define SIZE TEXT_LENTH/4+((TEXT_LENTH%4)?1:0)

#define FLASH_SAVE_ADDR  0X08008000 	//����FLASH �����ַ(�������32KB��ַ��Χ,��Ϊ4�ı���. 

	u8 key=0;
	u16 i=0;
	u8 datatemp[SIZE];

int main(void)
{

	Cache_Enable();					//��L1-Cache
	HAL_Init();				        //��ʼ��HAL��
	Stm32_Clock_Init(160,5,2,4);	//����ʱ��,400Mhz 
	delay_init(400);				//��ʱ��ʼ��
	uart_init(115200);				//���ڳ�ʼ��
	LED_Init();						//��ʼ��LEDʱ��
	KEY_Init();
	MPU_Memory_Protection();		//������ش洢����
	
	LCD_Init();            //��ʼ��2.0�� 240x320 ������  LCD��ʾ
	GBK_Lib_Init();        //Ӳ��GBK�ֿ��ʼ��--(���ʹ�ò����ֿ��Һ�����汾���˴��������Σ������ֿ��ʼ����
	LCD_Clear(WHITE);      //���� 
	
	Draw_Font16B(16,16,RED ,"STM32H7 FLASH-EEPROM ");
  Draw_Font16B(16,32,BLUE,"  Ƕ��ʽ������       ");	 
	Draw_Font16B(16,48,BLUE,"mcudev.taobao.com    "); 
	Draw_Font16B(16,70,BLUE," K1:Write  K2:Read   "); 
		
	while(1)
	{
		key=KEY_Scan(0);
		
		if(key==KEY1_PRES)	//KEY1����,д��STM32 FLASH
		{
			LCD_Fill(0,90,239,319,WHITE);//�������    
			
 			Draw_Font16B(16,90,BLUE,"Start Write FLASH....");
			
			STMFLASH_Write(FLASH_SAVE_ADDR,(u32*)TEXT_Buffer,SIZE);
			
			Draw_Font16B(16,90,BLUE,"FLASH Write Finished!");//��ʾ�������
		}
		if(key==KEY2_PRES)	//KEY0����,��ȡ�ַ�������ʾ
		{
 			Draw_Font16B(16,90,BLUE,"Start Read FLASH.... ");
			
			STMFLASH_Read(FLASH_SAVE_ADDR,(u32*)datatemp,SIZE);
			
			Draw_Font16B(16,90,BLUE,"The Data Readed Is:  ");//��ʾ�������
			
			Draw_Font16B(16,110,RED,datatemp);//��ʾ�������ַ���
		}
		
		
		i++;
		delay_ms(10);  
		if(i==20)
		{
			LED2_Toggle;//��ʾϵͳ��������	
			i=0;
		}		   
	} 
}



/**************************************************************************/

//FLASHģ��EEPROM ʵ�� 

//STM32H7����ģ��-HAL�⺯���汾
//DevEBox  ��Խ����
//�Ա����̣�mcudev.taobao.com
//�Ա����̣�shop389957290.taobao.com				


/**************************************************************************/
