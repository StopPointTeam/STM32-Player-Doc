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
//FATFS 实验 


//STM32H7工程模板-HAL库函数版本
//DevEBox  大越创新
//淘宝店铺：mcudev.taobao.com
//淘宝店铺：shop389957290.taobao.com			
/****************************************************************/


u8 tbuf[32];

	
int main(void)
{

	u32 total,free;
	u8 t=0;	
	u8 res=0;
	
	Cache_Enable();                		  //打开L1-Cache
	HAL_Init();				        		      //初始化HAL库
	Stm32_Clock_Init(160,5,2,4);  		  //设置时钟,400Mhz 
	delay_init(400);										//延时初始化
	uart_init(115200);									//串口初始化
	
	LED_Init();								//初始化LED
	KEY_Init();								//初始化按键
	
	LCD_Init();            //初始化2.0寸 240x320 高清屏  LCD显示
	GBK_Lib_Init();        //硬件GBK字库初始化--(如果使用不带字库的液晶屏版本，此处可以屏蔽，不做字库初始化）
	LCD_Clear(WHITE);      //清屏  
	
//	W25QXX_Init();					//初始化W25Q256
	my_mem_init(SRAMIN);			//初始化内部内存池(AXI)
	//my_mem_init(SRAMEX);			//初始化外部内存池(SDRAM)
//	my_mem_init(SRAM12);			//初始化SRAM12内存池(SRAM1+SRAM2)
//	my_mem_init(SRAM4);				//初始化SRAM4内存池(SRAM4)
//	my_mem_init(SRAMDTCM);			//初始化DTCM内存池(DTCM)
//	my_mem_init(SRAMITCM);			//初始化ITCM内存池(ITCM)
	
	Draw_Font16B(16,16,RED,"  STM32H7 FATFS   ");
	Draw_Font16B(16,32,BLUE,"  嵌入式开发网   ");	 
	Draw_Font16B(16,48,BLUE,"mcudev.taobao.com"); 
	
	
  
	
    while(SD_Init())//检测不到SD卡
    {
        Draw_Font16B(16,90,RED,"SD Card Error!");
        delay_ms(500);
        Draw_Font16B(16,90,RED,"Please Check! ");
        delay_ms(500);
        LED2_Toggle;//D2闪烁
    }
	
	
	//FTL_Init(); //NAND FLASH FTL层算法代码	
	
  //fatfs文件系统配置，去掉了对中文路径的支持，由于对路径识别的关键字符占用太多空间，暂时屏蔽，只支持英文目录路径			
		
	exfuns_init();				//为fatfs相关变量申请内存		
		
	f_mount(fs[0],"0:",1);		//挂载SD卡 
		
	
	while(exf_getfree("0",&total,&free))	//得到SD卡的总容量和剩余容量
	{
		Draw_Font16B(16,90,BLUE,"SD Card Fatfs Error!");
		delay_ms(200);
		LCD_Fill(30,150,240,150+16,WHITE);	//清除显示			  
		delay_ms(200);
		LED2_Toggle;//DS0闪烁
	}					

	
 	
	Draw_Font16B(16,110,BLUE,"FATFS OK!");	 

  sprintf((char*)tbuf,"SD Total Size: %u MB",total>>10); //显示无符号十进制整数		
   
	Draw_Font16B(16,110,BLUE,tbuf);  //显示SD卡总容量 MB
	
	sprintf((char*)tbuf,"SD Free Size: %u MB",free>>10); //显示无符号十进制整数		
   
	Draw_Font16B(16,130,BLUE,tbuf);  //显示SD卡剩余容量 MB			  
  

  
	while(1)
	{
		t++; 
		delay_ms(200);		
		LED2_Toggle;//DS0闪烁
	}
}

