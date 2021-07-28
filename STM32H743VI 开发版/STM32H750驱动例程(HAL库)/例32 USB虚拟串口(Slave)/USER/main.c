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
#include "usbd_cdc.h" 
#include "usbd_cdc_interface.h"

//USB���⴮�ڲ���

//STM32H7����ģ��-HAL�⺯���汾
//DevEBox  ��Խ����
//�Ա����̣�mcudev.taobao.com
//�Ա����̣�shop389957290.taobao.com	



USBD_HandleTypeDef USBD_Device;
extern PCD_HandleTypeDef hpcd;
extern vu8 bDeviceState;			//USB���� ���

int main(void)
{
	u16 len;	
	u16 times=0;    
	u8 usbstatus=0;
	Cache_Enable();                			  //��L1-Cache
	MPU_Memory_Protection();        		  //������ش洢����
	HAL_Init();				        		        //��ʼ��HAL��
	Stm32_Clock_Init(160,5,2,4);  		    //����ʱ��,400Mhz 
	delay_init(400);						          //��ʱ��ʼ��
	uart_init(115200);						        //���ڳ�ʼ��
	
	LED_Init();								//��ʼ��LED
	KEY_Init();								//��ʼ������
	
	LCD_Init();            //��ʼ��2.0�� 240x320 ������  LCD��ʾ
	GBK_Lib_Init();        //Ӳ��GBK�ֿ��ʼ��--(���ʹ�ò����ֿ��Һ�����汾���˴��������Σ������ֿ��ʼ����
	LCD_Clear(WHITE);      //����  
	
	
	
 	my_mem_init(SRAMIN);		    		//��ʼ���ڲ��ڴ��
	//my_mem_init(SRAMEX);		    		//��ʼ���ⲿ�ڴ��
	my_mem_init(SRAMDTCM);		    		//��ʼ��CCM�ڴ�� 

	

	
	Draw_Font16B(16,16,RED,"  STM32H7 USB-USART ");
	Draw_Font16B(16,32,BLUE,"  Ƕ��ʽ������   ");	 
	Draw_Font16B(16,48,BLUE,"mcudev.taobao.com"); 
	 
 	Draw_Font24B(16,70,BLUE,"USB Connecting...");//��ʾUSB��ʼ����	
	
	USBD_Init(&USBD_Device,&VCP_Desc,0);
	
	USBD_RegisterClass(&USBD_Device,USBD_CDC_CLASS);
	
	USBD_CDC_RegisterInterface(&USBD_Device,&USBD_CDC_fops);
	
	USBD_Start(&USBD_Device);
	
	HAL_PWREx_EnableUSBVoltageDetector();
		
    
 	while(1)
	{
		if(usbstatus!=bDeviceState)//USB����״̬�����˸ı�.
		{
			usbstatus=bDeviceState;//��¼�µ�״̬
			if(usbstatus==1)
			{
				
				POINT_COLOR=BLUE;
				Draw_Font24B(16,70,BLUE,"USB Connected    ");//��ʾUSB���ӳɹ�
				LED2(0);//D2��
			}
			else
			{
				
				POINT_COLOR=RED;
				Draw_Font24B(16,70,BLUE,"USB disConnected ");//��ʾUSB�Ͽ�
				LED2(1);//D2��
			}
		}
		if(USB_USART_RX_STA&0x8000)
		{					   
			len=USB_USART_RX_STA&0x3FFF;//�õ��˴ν��յ������ݳ���
			usb_printf("\r\n�����͵���Ϣ����Ϊ:%d\r\n\r\n",len);
            VCP_DataTx(USB_USART_RX_BUF,len);;
			usb_printf("\r\n\r\n");//���뻻��
			USB_USART_RX_STA=0;
		}
		else
		{
			times++;
			if(times%5000==0)
			{
				usb_printf("\r\n  STM32F4/F7/H7������USB���⴮��ʵ��\r\n");
				usb_printf("��Խ����-mcudev.taobao.com \r\n\r\n");
			}
			if(times%200==0)usb_printf("����������,�Իس�������\r\n");  
			if(times%30==0)LED2_Toggle;//��˸LED,��ʾϵͳ��������.
			delay_ms(10);    
		}
		
		
	}   	
}





























//STM32H7����ģ��-HAL�⺯���汾
//DevEBox  ��Խ����
//�Ա����̣�mcudev.taobao.com
//�Ա����̣�shop389957290.taobao.com	




