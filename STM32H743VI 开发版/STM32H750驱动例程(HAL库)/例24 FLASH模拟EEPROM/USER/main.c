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

//FLASH模拟EEPROM 实验 

//STM32H7工程模板-HAL库函数版本
//DevEBox  大越创新
//淘宝店铺：mcudev.taobao.com
//淘宝店铺：shop389957290.taobao.com				


/**************************************************************************/


//要写入到STM32 FLASH的字符串数组
const u8 TEXT_Buffer[]={"STM32 FLASH TEST"};
#define TEXT_LENTH sizeof(TEXT_Buffer)	 		  	//数组长度	
#define SIZE TEXT_LENTH/4+((TEXT_LENTH%4)?1:0)

#define FLASH_SAVE_ADDR  0X08008000 	//设置FLASH 保存地址(必须大于32KB地址范围,且为4的倍数. 

	u8 key=0;
	u16 i=0;
	u8 datatemp[SIZE];

int main(void)
{

	Cache_Enable();					//打开L1-Cache
	HAL_Init();				        //初始化HAL库
	Stm32_Clock_Init(160,5,2,4);	//设置时钟,400Mhz 
	delay_init(400);				//延时初始化
	uart_init(115200);				//串口初始化
	LED_Init();						//初始化LED时钟
	KEY_Init();
	MPU_Memory_Protection();		//保护相关存储区域
	
	LCD_Init();            //初始化2.0寸 240x320 高清屏  LCD显示
	GBK_Lib_Init();        //硬件GBK字库初始化--(如果使用不带字库的液晶屏版本，此处可以屏蔽，不做字库初始化）
	LCD_Clear(WHITE);      //清屏 
	
	Draw_Font16B(16,16,RED ,"STM32H7 FLASH-EEPROM ");
  Draw_Font16B(16,32,BLUE,"  嵌入式开发网       ");	 
	Draw_Font16B(16,48,BLUE,"mcudev.taobao.com    "); 
	Draw_Font16B(16,70,BLUE," K1:Write  K2:Read   "); 
		
	while(1)
	{
		key=KEY_Scan(0);
		
		if(key==KEY1_PRES)	//KEY1按下,写入STM32 FLASH
		{
			LCD_Fill(0,90,239,319,WHITE);//清除半屏    
			
 			Draw_Font16B(16,90,BLUE,"Start Write FLASH....");
			
			STMFLASH_Write(FLASH_SAVE_ADDR,(u32*)TEXT_Buffer,SIZE);
			
			Draw_Font16B(16,90,BLUE,"FLASH Write Finished!");//提示传送完成
		}
		if(key==KEY2_PRES)	//KEY0按下,读取字符串并显示
		{
 			Draw_Font16B(16,90,BLUE,"Start Read FLASH.... ");
			
			STMFLASH_Read(FLASH_SAVE_ADDR,(u32*)datatemp,SIZE);
			
			Draw_Font16B(16,90,BLUE,"The Data Readed Is:  ");//提示传送完成
			
			Draw_Font16B(16,110,RED,datatemp);//显示读到的字符串
		}
		
		
		i++;
		delay_ms(10);  
		if(i==20)
		{
			LED2_Toggle;//提示系统正在运行	
			i=0;
		}		   
	} 
}



/**************************************************************************/

//FLASH模拟EEPROM 实验 

//STM32H7工程模板-HAL库函数版本
//DevEBox  大越创新
//淘宝店铺：mcudev.taobao.com
//淘宝店铺：shop389957290.taobao.com				


/**************************************************************************/
