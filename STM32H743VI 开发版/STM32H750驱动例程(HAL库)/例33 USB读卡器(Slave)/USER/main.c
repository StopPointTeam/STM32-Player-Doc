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

//USB读卡器(Slave) 实验 
//STM32H7工程模板-HAL库函数版本
//DevEBox  大越创新
//淘宝店铺：mcudev.taobao.com
//淘宝店铺：shop389957290.taobao.com	


/*************************************************************************/

USBD_HandleTypeDef USBD_Device;
extern PCD_HandleTypeDef hpcd;
extern vu8 USB_STATUS_REG;			//USB状态
extern vu8 bDeviceState;			//USB连接 情况

u8 tbuf[32];


int main(void)
{
	u8 offline_cnt=0;
	u8 tct=0;
	u8 USB_STA;
	u8 Divece_STA;
	uint64_t CardCap;	//SD卡容量
	Cache_Enable();                			//打开L1-Cache
	Stm32_Clock_Init(160,5,2,4);  		    //设置时钟,400Mhz
	HAL_Init();				        		//初始化HAL库
	delay_init(400);						//延时初始化
	uart_init(115200);						//串口初始化
	
	LED_Init();								//初始化LED
	KEY_Init();								//初始化按键
	MPU_Memory_Protection();        		//保护相关存储区域
	

	LCD_Init();            //初始化2.0寸 240x320 高清屏  LCD显示
	GBK_Lib_Init();        //硬件GBK字库初始化--(如果使用不带字库的液晶屏版本，此处可以屏蔽，不做字库初始化）
	LCD_Clear(WHITE);      //清屏  
	
	W25QXX_Init();
 	my_mem_init(SRAMIN);		    		//初始化内部内存池
//	my_mem_init(SRAMEX);		    		//初始化外部内存池
	my_mem_init(SRAMDTCM);		    		//初始化CCM内存池 

	 Draw_Font16B(16,10,RED,"  STM32H750 USB Card ");
	 Draw_Font16B(16,30,BLUE,"     嵌入式开发网   ");	 
	 Draw_Font16B(16,50,BLUE," mcudev.taobao.com  "); 
	 

	if(W25QXX_ReadID()!=W25Q64)
		Draw_Font16B(16,70,RED,"W25Q64 Error!");	//检测W25Q128错误
	else //SPI FLASH 正常
	{   														 
		Draw_Font16B(16,70,BLUE,"SPI FLASH Size:8MB");	 
	} 
	
	
	if(SD_Init())
		Draw_Font16B(16,90,RED,"SD Card Error!");	//检测SD卡错误
	else //SD 卡正常
	{   	
		
		CardCap=(uint64_t)(SDCardInfo.LogBlockNbr)*(uint64_t)(SDCardInfo.LogBlockSize);	//计算SD卡容量
		
		sprintf((char*)tbuf,"SD Card Size: %u MB",CardCap>>20); //显示无符号十进制整数		
   
		Draw_Font16B(16,90,BLUE,tbuf);  //显示存储卡容量
		
 	}
	
	

    
	USBD_Init(&USBD_Device,&MSC_Desc,0);                        //初始化USB
	USBD_RegisterClass(&USBD_Device,USBD_MSC_CLASS);            //添加类
	USBD_MSC_RegisterStorage(&USBD_Device,&USBD_DISK_fops);     //为MSC类添加回调函数
	USBD_Start(&USBD_Device);                                   //开启USB
	HAL_PWREx_EnableUSBVoltageDetector();
	delay_ms(1800);
    
	while(1)
	{
		if(USB_STA!=USB_STATUS_REG)//状态改变了 
		{	 						   
			  
			if(USB_STATUS_REG&0x01)//正在写		  
			{
				
				Draw_Font16B(16,130,BLUE,"USB Writing...");//提示USB正在写入数据	 
			}
			if(USB_STATUS_REG&0x02)//正在读
			{
				
				Draw_Font16B(16,130,BLUE,"USB Reading...");//提示USB正在读出数据  		 
			}

			
			if(USB_STATUS_REG&0x04)
				
				   Draw_Font16B(16,170,RED,"USB Write Err ");//提示写入错误
			else 
				   Draw_Font16B(16,170,BLUE,"              ");//提示写入错误//清除显示	  
			
			if(USB_STATUS_REG&0x08)
				
				   Draw_Font16B(16,190,RED,"USB Read  Err ");//提示读出错误
			
			else  
				   Draw_Font16B(16,190,BLUE,"              ");//提示写入错误//清除显示	     
			
			USB_STA=USB_STATUS_REG;//记录最后的状态
		}
		
		
		if(Divece_STA!=bDeviceState) 
		{
			if(bDeviceState==1)
				Draw_Font16B(16,150,BLUE,"USB Connected    ");//提示USB连接已经建立
			else 
				Draw_Font16B(16,150,BLUE,"USB DisConnected ");//提示USB被拔出了
			Divece_STA=bDeviceState;
		}
		
		tct++;
		if(tct==200)
		{
			tct=0;
			
			LED2_Toggle;//提示系统在运行
			
			if(USB_STATUS_REG&0x10)
			{
				offline_cnt=0;//USB连接了,则清除offline计数器
				bDeviceState=1;
			}
			else//没有得到轮询 
			{
				offline_cnt++;  
				if(offline_cnt>10)bDeviceState=0;//2s内没收到在线标记,代表USB被拔出了
			}
			USB_STATUS_REG=0;
		}
		

	} 
}



























/*************************************************************************/

//USB读卡器(Slave) 实验 
//STM32H7工程模板-HAL库函数版本
//DevEBox  大越创新
//淘宝店铺：mcudev.taobao.com
//淘宝店铺：shop389957290.taobao.com	


/*************************************************************************/


