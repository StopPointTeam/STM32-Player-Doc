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


#include "usbd_core.h"
#include "usbd_desc.h"
#include "usbd_msc.h"
#include "usbd_storage.h" 

/*************************************************************************/

//USB������(Slave) ʵ�� 
//STM32H7����ģ��-HAL�⺯���汾
//DevEBox  ��Խ����
//�Ա����̣�mcudev.taobao.com
//�Ա����̣�shop389957290.taobao.com	


/*************************************************************************/

USBD_HandleTypeDef USBD_Device;
extern PCD_HandleTypeDef hpcd;
extern vu8 USB_STATUS_REG;			//USB״̬
extern vu8 bDeviceState;			//USB���� ���

u8 tbuf[32];


int main(void)
{
	u8 offline_cnt=0;
	u8 tct=0;
	u8 USB_STA;
	u8 Divece_STA;
	uint64_t CardCap;	//SD������
	Cache_Enable();                			//��L1-Cache
	Stm32_Clock_Init(160,5,2,4);  		    //����ʱ��,400Mhz
	HAL_Init();				        		//��ʼ��HAL��
	delay_init(400);						//��ʱ��ʼ��
	uart_init(115200);						//���ڳ�ʼ��
	
	LED_Init();								//��ʼ��LED
	KEY_Init();								//��ʼ������
	MPU_Memory_Protection();        		//������ش洢����
	

	LCD_Init();            //��ʼ��2.0�� 240x320 ������  LCD��ʾ
	GBK_Lib_Init();        //Ӳ��GBK�ֿ��ʼ��--(���ʹ�ò����ֿ��Һ�����汾���˴��������Σ������ֿ��ʼ����
	LCD_Clear(WHITE);      //����  
	
	W25QXX_Init();
 	my_mem_init(SRAMIN);		    		//��ʼ���ڲ��ڴ��
//	my_mem_init(SRAMEX);		    		//��ʼ���ⲿ�ڴ��
	my_mem_init(SRAMDTCM);		    		//��ʼ��CCM�ڴ�� 

	 Draw_Font16B(16,10,RED,"  STM32H750 USB Card ");
	 Draw_Font16B(16,30,BLUE,"     Ƕ��ʽ������   ");	 
	 Draw_Font16B(16,50,BLUE," mcudev.taobao.com  "); 
	 

	if(W25QXX_ReadID()!=W25Q64)
		Draw_Font16B(16,70,RED,"W25Q64 Error!");	//���W25Q128����
	else //SPI FLASH ����
	{   														 
		Draw_Font16B(16,70,BLUE,"SPI FLASH Size:8MB");	 
	} 
	
	
	if(SD_Init())
		Draw_Font16B(16,90,RED,"SD Card Error!");	//���SD������
	else //SD ������
	{   	
		
		CardCap=(uint64_t)(SDCardInfo.LogBlockNbr)*(uint64_t)(SDCardInfo.LogBlockSize);	//����SD������
		
		sprintf((char*)tbuf,"SD Card Size: %u MB",CardCap>>20); //��ʾ�޷���ʮ��������		
   
		Draw_Font16B(16,90,BLUE,tbuf);  //��ʾ�洢������
		
 	}
	
	

    
	USBD_Init(&USBD_Device,&MSC_Desc,0);                        //��ʼ��USB
	USBD_RegisterClass(&USBD_Device,USBD_MSC_CLASS);            //�����
	USBD_MSC_RegisterStorage(&USBD_Device,&USBD_DISK_fops);     //ΪMSC����ӻص�����
	USBD_Start(&USBD_Device);                                   //����USB
	HAL_PWREx_EnableUSBVoltageDetector();
	delay_ms(1800);
    
	while(1)
	{
		if(USB_STA!=USB_STATUS_REG)//״̬�ı��� 
		{	 						   
			  
			if(USB_STATUS_REG&0x01)//����д		  
			{
				
				Draw_Font16B(16,130,BLUE,"USB Writing...");//��ʾUSB����д������	 
			}
			if(USB_STATUS_REG&0x02)//���ڶ�
			{
				
				Draw_Font16B(16,130,BLUE,"USB Reading...");//��ʾUSB���ڶ�������  		 
			}

			
			if(USB_STATUS_REG&0x04)
				
				   Draw_Font16B(16,170,RED,"USB Write Err ");//��ʾд�����
			else 
				   Draw_Font16B(16,170,BLUE,"              ");//��ʾд�����//�����ʾ	  
			
			if(USB_STATUS_REG&0x08)
				
				   Draw_Font16B(16,190,RED,"USB Read  Err ");//��ʾ��������
			
			else  
				   Draw_Font16B(16,190,BLUE,"              ");//��ʾд�����//�����ʾ	     
			
			USB_STA=USB_STATUS_REG;//��¼����״̬
		}
		
		
		if(Divece_STA!=bDeviceState) 
		{
			if(bDeviceState==1)
				Draw_Font16B(16,150,BLUE,"USB Connected    ");//��ʾUSB�����Ѿ�����
			else 
				Draw_Font16B(16,150,BLUE,"USB DisConnected ");//��ʾUSB���γ���
			Divece_STA=bDeviceState;
		}
		
		tct++;
		if(tct==200)
		{
			tct=0;
			
			LED2_Toggle;//��ʾϵͳ������
			
			if(USB_STATUS_REG&0x10)
			{
				offline_cnt=0;//USB������,�����offline������
				bDeviceState=1;
			}
			else//û�еõ���ѯ 
			{
				offline_cnt++;  
				if(offline_cnt>10)bDeviceState=0;//2s��û�յ����߱��,����USB���γ���
			}
			USB_STATUS_REG=0;
		}
		

	} 
}



























/*************************************************************************/

//USB������(Slave) ʵ�� 
//STM32H7����ģ��-HAL�⺯���汾
//DevEBox  ��Խ����
//�Ա����̣�mcudev.taobao.com
//�Ա����̣�shop389957290.taobao.com	


/*************************************************************************/


