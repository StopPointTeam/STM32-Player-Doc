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

#include "NORFLASH.h"

/**********************************************************************/

//W25Q64(QSPI����) ��дʵ��  

//STM32H7����ģ��-HAL�⺯���汾
//DevEBox  ��Խ����
//�Ա����̣�mcudev.taobao.com
//�Ա����̣�shop389957290.taobao.com	
  
/**********************************************************************/


//Ҫд�뵽W25Q64���ַ�������
const u8 TEXT_Buffer[24]={"W25Q64 Check: OK OK OK"};
	u8 SIZE=24;
	u32 FlashAddr=0;  //���Ե�ַ��0
	u8 datatemp[32];


	u8 key;
	u16 i=0;


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

	
	Draw_Font16B(16,16,RED, " STM32H7 W25Q64(QSPI)  ");
  Draw_Font16B(16,32,BLUE,"  Ƕ��ʽ������   ");	 
	Draw_Font16B(16,48,BLUE," mcudev.taobao.com"); 
	Draw_Font16B(16,64,RED, " K1:Write  K2:Read"); 
	
	NORFLASH_Init();				//NORFLASH(W25Q64)��ʼ��
	
	
	while(NORFLASH_ReadID()!=W25Q64)							//��ⲻ��W25Q64
	{
		Draw_Font16B(16,96,BLUE,"W25Q64 Check Failed!");
		delay_ms(500);
		Draw_Font16B(16,96,BLUE,"Please Check!        ");
		delay_ms(500);
		LED2_Toggle;		//LED2 ��˸
	}
	
	
	Draw_Font16B(16,96,BLUE,"W25Q64 Ready!"); 
		
	
	while(1)
	{
		key=KEY_Scan(0);
		if(key==KEY1_PRES)//KEY1����,д��W25Q64
		{
			LCD_Fill(0,112,239,319,WHITE);//�������    
			
 			Draw_Font16B(16,112,BLUE,"Start Write W25Q64....");
			
			NORFLASH_Write((u8*)TEXT_Buffer,FlashAddr,SIZE);		//��0����ַ����ʼ,д��SIZE���ȵ�����
			
			Draw_Font16B(16,112,BLUE,"W25Q64 Write Finished!");	//��ʾ�������
		}
		if(key==KEY2_PRES)//KEY0����,��ȡ�ַ�������ʾ
		{
 			Draw_Font16B(16,112,BLUE,"Start Read W25Q64.... ");
			
			NORFLASH_Read(datatemp,FlashAddr,SIZE);					//��0����ַ����ʼ,����SIZE���ֽ�
			
			Draw_Font16B(16,112,BLUE,"The Data Readed Is:   ");	//��ʾ�������
			
			Draw_Font16B(16,128,RED,datatemp);					//��ʾ�������ַ���
		} 
		
		i++;
		
		delay_ms(10);
		
		if(i==20)
		{
			LED2_Toggle;	//LED2 ��˸
			i=0;
		}		   
	}
}



















































/**********************************************************************/

//QSPI ʵ��  

//STM32H7����ģ��-HAL�⺯���汾
//DevEBox  ��Խ����
//�Ա����̣�mcudev.taobao.com
//�Ա����̣�shop389957290.taobao.com	
  
/**********************************************************************/






