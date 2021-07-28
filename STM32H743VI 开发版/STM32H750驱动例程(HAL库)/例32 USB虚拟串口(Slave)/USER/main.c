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

//USB虚拟串口测试

//STM32H7工程模板-HAL库函数版本
//DevEBox  大越创新
//淘宝店铺：mcudev.taobao.com
//淘宝店铺：shop389957290.taobao.com	



USBD_HandleTypeDef USBD_Device;
extern PCD_HandleTypeDef hpcd;
extern vu8 bDeviceState;			//USB连接 情况

int main(void)
{
	u16 len;	
	u16 times=0;    
	u8 usbstatus=0;
	Cache_Enable();                			  //打开L1-Cache
	MPU_Memory_Protection();        		  //保护相关存储区域
	HAL_Init();				        		        //初始化HAL库
	Stm32_Clock_Init(160,5,2,4);  		    //设置时钟,400Mhz 
	delay_init(400);						          //延时初始化
	uart_init(115200);						        //串口初始化
	
	LED_Init();								//初始化LED
	KEY_Init();								//初始化按键
	
	LCD_Init();            //初始化2.0寸 240x320 高清屏  LCD显示
	GBK_Lib_Init();        //硬件GBK字库初始化--(如果使用不带字库的液晶屏版本，此处可以屏蔽，不做字库初始化）
	LCD_Clear(WHITE);      //清屏  
	
	
	
 	my_mem_init(SRAMIN);		    		//初始化内部内存池
	//my_mem_init(SRAMEX);		    		//初始化外部内存池
	my_mem_init(SRAMDTCM);		    		//初始化CCM内存池 

	

	
	Draw_Font16B(16,16,RED,"  STM32H7 USB-USART ");
	Draw_Font16B(16,32,BLUE,"  嵌入式开发网   ");	 
	Draw_Font16B(16,48,BLUE,"mcudev.taobao.com"); 
	 
 	Draw_Font24B(16,70,BLUE,"USB Connecting...");//提示USB开始连接	
	
	USBD_Init(&USBD_Device,&VCP_Desc,0);
	
	USBD_RegisterClass(&USBD_Device,USBD_CDC_CLASS);
	
	USBD_CDC_RegisterInterface(&USBD_Device,&USBD_CDC_fops);
	
	USBD_Start(&USBD_Device);
	
	HAL_PWREx_EnableUSBVoltageDetector();
		
    
 	while(1)
	{
		if(usbstatus!=bDeviceState)//USB连接状态发生了改变.
		{
			usbstatus=bDeviceState;//记录新的状态
			if(usbstatus==1)
			{
				
				POINT_COLOR=BLUE;
				Draw_Font24B(16,70,BLUE,"USB Connected    ");//提示USB连接成功
				LED2(0);//D2亮
			}
			else
			{
				
				POINT_COLOR=RED;
				Draw_Font24B(16,70,BLUE,"USB disConnected ");//提示USB断开
				LED2(1);//D2灭
			}
		}
		if(USB_USART_RX_STA&0x8000)
		{					   
			len=USB_USART_RX_STA&0x3FFF;//得到此次接收到的数据长度
			usb_printf("\r\n您发送的消息长度为:%d\r\n\r\n",len);
            VCP_DataTx(USB_USART_RX_BUF,len);;
			usb_printf("\r\n\r\n");//插入换行
			USB_USART_RX_STA=0;
		}
		else
		{
			times++;
			if(times%5000==0)
			{
				usb_printf("\r\n  STM32F4/F7/H7开发板USB虚拟串口实验\r\n");
				usb_printf("大越创新-mcudev.taobao.com \r\n\r\n");
			}
			if(times%200==0)usb_printf("请输入数据,以回车键结束\r\n");  
			if(times%30==0)LED2_Toggle;//闪烁LED,提示系统正在运行.
			delay_ms(10);    
		}
		
		
	}   	
}





























//STM32H7工程模板-HAL库函数版本
//DevEBox  大越创新
//淘宝店铺：mcudev.taobao.com
//淘宝店铺：shop389957290.taobao.com	




