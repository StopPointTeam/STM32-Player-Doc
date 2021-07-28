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

//W25Q64(QSPI驱动) 读写实验  

//STM32H7工程模板-HAL库函数版本
//DevEBox  大越创新
//淘宝店铺：mcudev.taobao.com
//淘宝店铺：shop389957290.taobao.com	
  
/**********************************************************************/


//要写入到W25Q64的字符串数组
const u8 TEXT_Buffer[24]={"W25Q64 Check: OK OK OK"};
	u8 SIZE=24;
	u32 FlashAddr=0;  //测试地址是0
	u8 datatemp[32];


	u8 key;
	u16 i=0;


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

	
	Draw_Font16B(16,16,RED, " STM32H7 W25Q64(QSPI)  ");
  Draw_Font16B(16,32,BLUE,"  嵌入式开发网   ");	 
	Draw_Font16B(16,48,BLUE," mcudev.taobao.com"); 
	Draw_Font16B(16,64,RED, " K1:Write  K2:Read"); 
	
	NORFLASH_Init();				//NORFLASH(W25Q64)初始化
	
	
	while(NORFLASH_ReadID()!=W25Q64)							//检测不到W25Q64
	{
		Draw_Font16B(16,96,BLUE,"W25Q64 Check Failed!");
		delay_ms(500);
		Draw_Font16B(16,96,BLUE,"Please Check!        ");
		delay_ms(500);
		LED2_Toggle;		//LED2 闪烁
	}
	
	
	Draw_Font16B(16,96,BLUE,"W25Q64 Ready!"); 
		
	
	while(1)
	{
		key=KEY_Scan(0);
		if(key==KEY1_PRES)//KEY1按下,写入W25Q64
		{
			LCD_Fill(0,112,239,319,WHITE);//清除半屏    
			
 			Draw_Font16B(16,112,BLUE,"Start Write W25Q64....");
			
			NORFLASH_Write((u8*)TEXT_Buffer,FlashAddr,SIZE);		//第0个地址处开始,写入SIZE长度的数据
			
			Draw_Font16B(16,112,BLUE,"W25Q64 Write Finished!");	//提示传送完成
		}
		if(key==KEY2_PRES)//KEY0按下,读取字符串并显示
		{
 			Draw_Font16B(16,112,BLUE,"Start Read W25Q64.... ");
			
			NORFLASH_Read(datatemp,FlashAddr,SIZE);					//第0个地址处开始,读出SIZE个字节
			
			Draw_Font16B(16,112,BLUE,"The Data Readed Is:   ");	//提示传送完成
			
			Draw_Font16B(16,128,RED,datatemp);					//显示读到的字符串
		} 
		
		i++;
		
		delay_ms(10);
		
		if(i==20)
		{
			LED2_Toggle;	//LED2 闪烁
			i=0;
		}		   
	}
}



















































/**********************************************************************/

//QSPI 实验  

//STM32H7工程模板-HAL库函数版本
//DevEBox  大越创新
//淘宝店铺：mcudev.taobao.com
//淘宝店铺：shop389957290.taobao.com	
  
/**********************************************************************/






