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

/********************************************************/
//SD卡 实验

//STM32H7工程模板-HAL库函数版本
//DevEBox  大越创新
//淘宝店铺：mcudev.taobao.com
//淘宝店铺：shop389957290.taobao.com	

/********************************************************/





//通过串口打印SD卡相关信息
void show_sdcard_info(void)
{
    switch(SDCardInfo.CardType)
    {
    case STD_CAPACITY_SD_CARD_V1_1:
        printf("Card Type:SDSC V1.1\r\n");
        break;
    case STD_CAPACITY_SD_CARD_V2_0:
        printf("Card Type:SDSC V2.0\r\n");
        break;
    case HIGH_CAPACITY_SD_CARD:
        printf("Card Type:SDHC V2.0\r\n");
        break;
    case MULTIMEDIA_CARD:
        printf("Card Type:MMC Card\r\n");
        break;
    }
    printf("Card ManufacturerID:%d\r\n",SDCardInfo.SD_cid.ManufacturerID);	//制造商ID
    printf("Card RCA:%d\r\n",SDCardInfo.RCA);								//卡相对地址
    printf("Card Capacity:%d MB\r\n",(u32)(SDCardInfo.CardCapacity>>20));	//显示容量
    printf("Card BlockSize:%d\r\n\r\n",SDCardInfo.CardBlockSize);			//显示块大小
}


/********************************************************/
//测试SD卡的读取
//从secaddr地址开始,读取seccnt个扇区的数据
//secaddr:扇区地址
//seccnt:扇区数

//STM32H7工程模板-HAL库函数版本
//DevEBox  大越创新
//淘宝店铺：mcudev.taobao.com
//淘宝店铺：shop389957290.taobao.com	

/********************************************************/


void sd_test_read(u32 secaddr,u32 seccnt)
{
    u32 i;
    u8 *buf;
    u8 sta=0;
    buf=mymalloc(SRAMIN,seccnt*512);	//申请内存,从SDRAM申请内存
    sta=SD_ReadDisk(buf,secaddr,seccnt);//读取secaddr扇区开始的内容
    if(sta==0)
    {
        printf("SECTOR %d DATA:\r\n",secaddr);
        for(i=0; i<seccnt*512; i++)printf("%x ",buf[i]); //打印secaddr开始的扇区数据
        printf("\r\nDATA ENDED\r\n");
    } else printf("err:%d\r\n",sta);
    myfree(SRAMIN,buf);	//释放内存
}




/********************************************************/
//测试SD卡的写入(慎用,最好写全是0XFF的扇区,否则可能损坏SD卡.)
//从secaddr地址开始,写入seccnt个扇区的数据
//secaddr:扇区地址
//seccnt:扇区数

//STM32H7工程模板-HAL库函数版本
//DevEBox  大越创新
//淘宝店铺：mcudev.taobao.com
//淘宝店铺：shop389957290.taobao.com	

/********************************************************/


void sd_test_write(u32 secaddr,u32 seccnt)
{
    u32 i;
    u8 *buf;
    u8 sta=0;
    buf=mymalloc(SRAMIN,seccnt*512);	//从SDRAM申请内存
    for(i=0; i<seccnt*512; i++) 			//初始化写入的数据,是3的倍数.
    {
        buf[i]=i*3;
    }
    sta=SD_WriteDisk(buf,secaddr,seccnt);//从secaddr扇区开始写入seccnt个扇区内容
    if(sta==0)
    {
        printf("Write over!\r\n");
    } else printf("err:%d\r\n",sta);
    myfree(SRAMIN,buf);					//释放内存
}



/********************************************************/
//Main 主函数

//STM32H7工程模板-HAL库函数版本
//DevEBox  大越创新
//淘宝店铺：mcudev.taobao.com
//淘宝店铺：shop389957290.taobao.com	

/********************************************************/


u8 tbuf[32];

int main(void)
{
    u8 key;
    u32 sd_size;
    u8 t=0;
    u8 *buf;
	
    Cache_Enable();                  //打开L1-Cache
    HAL_Init();				        		   //初始化HAL库
    Stm32_Clock_Init(160,5,2,4);  	 //设置时钟,400Mhz
    delay_init(400);						     //延时初始化
    uart_init(115200);						   //串口初始化
    
    LED_Init();							        //初始化LED
    KEY_Init();					       			//初始化按键
	
		LCD_Init();            //初始化2.0寸 240x320 高清屏  LCD显示
		GBK_Lib_Init();        //硬件GBK字库初始化--(如果使用不带字库的液晶屏版本，此处可以屏蔽，不做字库初始化）
		LCD_Clear(WHITE);      //清屏  
	
    my_mem_init(SRAMIN);			//初始化内部内存池(AXI)
//    //my_mem_init(SRAMEX);			//初始化外部内存池(SDRAM)
//    my_mem_init(SRAM12);			//初始化SRAM12内存池(SRAM1+SRAM2)
//    my_mem_init(SRAM4);				//初始化SRAM4内存池(SRAM4)
//    my_mem_init(SRAMDTCM);			//初始化DTCM内存池(DTCM)
//    my_mem_init(SRAMITCM);			//初始化ITCM内存池(ITCM)
	
	
    Draw_Font16B(16,16,RED,"  STM32H7 SD Card ");
		Draw_Font16B(16,32,BLUE,"  嵌入式开发网   ");	 
		Draw_Font16B(16,48,BLUE,"mcudev.taobao.com"); 
		Draw_Font16B(16,64,BLUE, "KEY2:Read Sector 0"); 


    while(SD_Init())//检测不到SD卡
    {
        Draw_Font16B(16,90,RED,"SD Card Error!");
        delay_ms(500);
        Draw_Font16B(16,90,RED,"Please Check! ");
        delay_ms(500);
        LED2_Toggle;//D2闪烁
    }
		
		
    show_sdcard_info();	//打印SD卡相关信息
                                        
    Draw_Font16B(16,90,BLUE,"SD Card OK    "); //检测SD卡成功
		
		sprintf((char*)tbuf,"SD Card Size: %u MB",SDCardInfo.CardCapacity>>20); //显示无符号十进制整数		
   
		Draw_Font16B(16,110,BLUE,tbuf);  //显示存储卡容量
    
		
    while(1)
    {
        key=KEY_Scan(0);
			
        if(key==KEY2_PRES)//KEY2按下了
        {
            buf=mymalloc(SRAMIN,2048);		//申请内存2K
					
            key=SD_ReadDisk(buf,0,1);
					
            if(key==0)	//读取0扇区的内容
            {
                Draw_Font16B(16,130,BLUE,"USART1 Sending ...");
							
                printf("SECTOR 0 DATA:\r\n");
							
                for(sd_size=0; sd_size<512; sd_size++)printf("%x ",buf[sd_size]); //打印0扇区数据
							
                printf("\r\nDATA ENDED\r\n");
							
                Draw_Font16B(16,130,BLUE,"USART1 Send  Over!");
							
            } 
						else printf("err:%d\r\n",key);
						
            myfree(SRAMIN,buf);//释放内存
        }
        t++;
        delay_ms(10);
        if(t==20)
        {
            LED2_Toggle;//D2闪烁
            t=0;
        }
    }
}































/********************************************************/
//SD卡 实验

//STM32H7工程模板-HAL库函数版本
//DevEBox  大越创新
//淘宝店铺：mcudev.taobao.com
//淘宝店铺：shop389957290.taobao.com	

/********************************************************/





