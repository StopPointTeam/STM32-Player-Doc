#include "sys.h"
#include "delay.h"
#include "usart.h" 
#include "led.h"
#include "key.h"

#include "LCD.h"
#include "Dis_Picture.h" 
#include "Text.h"	
#include "GBK_LibDrive.h"	

#include "mpu.h"
#include "malloc.h"
#include "w25qxx.h"
#include "sdmmc_sdcard.h" 
 
 
#include "ff.h"  
#include "exfuns.h" 

/****************************************************************/
//FATFS ʵ�� 


//STM32H7����ģ��-HAL�⺯���汾
//DevEBox  ��Խ����
//�Ա����̣�mcudev.taobao.com
//�Ա����̣�shop389957290.taobao.com			
/****************************************************************/


u8 tbuf[32];

	
int main(void)
{

	u32 total,free;
	u8 t=0;	
	u8 res=0;
	
	Cache_Enable();                		  //��L1-Cache
	HAL_Init();				        		      //��ʼ��HAL��
	Stm32_Clock_Init(160,5,2,4);  		  //����ʱ��,400Mhz 
	delay_init(400);										//��ʱ��ʼ��
	uart_init(115200);									//���ڳ�ʼ��
	
	LED_Init();								//��ʼ��LED
	KEY_Init();								//��ʼ������
	
	LCD_Init();            //��ʼ��2.0�� 240x320 ������  LCD��ʾ
	GBK_Lib_Init();        //Ӳ��GBK�ֿ��ʼ��--(���ʹ�ò����ֿ��Һ�����汾���˴��������Σ������ֿ��ʼ����
	LCD_Clear(WHITE);      //����  
	
//	W25QXX_Init();					//��ʼ��W25Q256
	my_mem_init(SRAMIN);			//��ʼ���ڲ��ڴ��(AXI)
	//my_mem_init(SRAMEX);			//��ʼ���ⲿ�ڴ��(SDRAM)
//	my_mem_init(SRAM12);			//��ʼ��SRAM12�ڴ��(SRAM1+SRAM2)
//	my_mem_init(SRAM4);				//��ʼ��SRAM4�ڴ��(SRAM4)
//	my_mem_init(SRAMDTCM);			//��ʼ��DTCM�ڴ��(DTCM)
//	my_mem_init(SRAMITCM);			//��ʼ��ITCM�ڴ��(ITCM)
	
	Draw_Font16B(16,16,RED,"  STM32H7 FATFS   ");
	Draw_Font16B(16,32,BLUE,"  Ƕ��ʽ������   ");	 
	Draw_Font16B(16,48,BLUE,"mcudev.taobao.com"); 
	
	
  
	
    while(SD_Init())//��ⲻ��SD��
    {
        Draw_Font16B(16,90,RED,"SD Card Error!");
        delay_ms(500);
        Draw_Font16B(16,90,RED,"Please Check! ");
        delay_ms(500);
        LED2_Toggle;//D2��˸
    }
	
	
	//FTL_Init(); //NAND FLASH FTL���㷨����	
	
  //fatfs�ļ�ϵͳ���ã�ȥ���˶�����·����֧�֣����ڶ�·��ʶ��Ĺؼ��ַ�ռ��̫��ռ䣬��ʱ���Σ�ֻ֧��Ӣ��Ŀ¼·��			
		
	exfuns_init();				//Ϊfatfs��ر��������ڴ�		
		
	f_mount(fs[0],"0:",1);		//����SD�� 
		
	
	while(exf_getfree("0",&total,&free))	//�õ�SD������������ʣ������
	{
		Draw_Font16B(16,90,BLUE,"SD Card Fatfs Error!");
		delay_ms(200);
		LCD_Fill(30,150,240,150+16,WHITE);	//�����ʾ			  
		delay_ms(200);
		LED2_Toggle;//DS0��˸
	}					

	
 	
	Draw_Font16B(16,110,BLUE,"FATFS OK!");	 

  sprintf((char*)tbuf,"SD Total Size: %u MB",total>>10); //��ʾ�޷���ʮ��������		
   
	Draw_Font16B(16,110,BLUE,tbuf);  //��ʾSD�������� MB
	
	sprintf((char*)tbuf,"SD Free Size: %u MB",free>>10); //��ʾ�޷���ʮ��������		
   
	Draw_Font16B(16,130,BLUE,tbuf);  //��ʾSD��ʣ������ MB			  
  

  
	while(1)
	{
		t++; 
		delay_ms(200);		
		LED2_Toggle;//DS0��˸
	}
}

