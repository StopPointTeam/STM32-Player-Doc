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

#include "dma.h" 

/*********************************************************************/
//DMA 实验  

//STM32H7工程模板-HAL库函数版本
//DevEBox  大越创新
//淘宝店铺：mcudev.taobao.com
//淘宝店铺：shop389957290.taobao.com		

/*********************************************************************/


#define SEND_BUF_SIZE 7800	//发送数据长度,最好等于sizeof(TEXT_TO_SEND)+2的整数倍.

u8 SendBuff[SEND_BUF_SIZE];	//发送数据缓冲区
const u8 TEXT_TO_SEND[]={" mcudev.taobao.com STM32H7XXX DMA 串口实验  "};	

	u16 i;
	u8 t=0;
	u8 j,mask=0;
	float pro=0;

u8 tbuf[32];

int main(void)
{

	Cache_Enable();					      //打开L1-Cache
	Stm32_Clock_Init(160,5,2,4);	//设置时钟,400Mhz 
	HAL_Init();				            //初始化HAL库
	delay_init(400);		      		//延时初始化
	uart_init(115200);			     	//串口初始化
	LED_Init();				         		//初始化LED时钟
	KEY_Init();
	
	MPU_Memory_Protection();		//保护相关存储区域
	
	LCD_Init();            //初始化2.0寸 240x320 高清屏  LCD显示
	GBK_Lib_Init();        //硬件GBK字库初始化--(如果使用不带字库的液晶屏版本，此处可以屏蔽，不做字库初始化）
	LCD_Clear(WHITE);      //清屏  
	
	
	MYDMA_Config(DMA2_Stream7);		//初始化DMA
	
	Draw_Font16B(16,16,RED,"  STM32H7 DMA    ");
  Draw_Font16B(16,32,BLUE,"  嵌入式开发网   ");	 
	Draw_Font16B(16,48,BLUE,"mcudev.taobao.com"); 
	Draw_Font24B(16,64,RED, "KEY2:Start"); 

	//显示提示信息	
	j=sizeof(TEXT_TO_SEND);	 
  
	for(i=0;i<SEND_BUF_SIZE;i++)//填充ASCII字符集数据
	{
		if(t>=j)//加入换行符
		{
			if(mask)
			{
				SendBuff[i]=0x0a;
				t=0;
			}else 
			{
				SendBuff[i]=0x0d;
				mask++;
			}	
		}
		else//复制TEXT_TO_SEND语句
		{
			mask=0;
			SendBuff[i]=TEXT_TO_SEND[t];
			t++;
		}   	   
	}		 
	POINT_COLOR=BLUE;//设置字体为蓝色	  
	i=0;
	while(1)
	{
		t=KEY_Scan(0);
		
		if(t==KEY2_PRES)//KEY0按下
		{
			printf("\r\nDMA DATA:\r\n"); 	  
			
			Draw_Font24B(8,90,RED, "Start Transimit..  ");
			Draw_Font24B(8,120,RED,"   %               ");//显示百分号
			
			HAL_UART_Transmit_DMA(&UART1_Handler,SendBuff,SEND_BUF_SIZE);//开启DMA传输
			
			  //使能串口1的DMA发送等待DMA传输完成，此时我们来做另外一些事，点灯
		    //实际应用中，传输数据期间，可以执行另外的任务
		  while(1)
		    {
          if(__HAL_DMA_GET_FLAG(&UART1TxDMA_Handler,DMA_FLAG_TCIF3_7))//等待DMA2_Steam7传输完成
            {
               __HAL_DMA_CLEAR_FLAG(&UART1TxDMA_Handler,DMA_FLAG_TCIF3_7);//清除DMA2_Steam7传输完成标志
               HAL_UART_DMAStop(&UART1_Handler);      //传输完成以后关闭串口DMA
					     break; 
            }
						
					pro=__HAL_DMA_GET_COUNTER(&UART1TxDMA_Handler);//得到当前还剩余多少个数据
							
					pro=1-pro/SEND_BUF_SIZE;    //得到百分比	 
							
					pro*=100;      			    //扩大100倍
					sprintf((char*)tbuf,"%5.2f % ",pro); //显示无符号十进制整数		
					Draw_Font24B(16,120,RED, tbuf);//显示百分号//显示100%	
						
		    }
				
			Draw_Font24B(8,120,RED, "100%               ");//显示百分号//显示100%	  
		  Draw_Font24B(8,90, RED, "Transimit Finished!");//提示传送完成
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
























/*********************************************************************/
//DMA 实验  

//STM32H7工程模板-HAL库函数版本
//DevEBox  大越创新
//淘宝店铺：mcudev.taobao.com
//淘宝店铺：shop389957290.taobao.com		

/*********************************************************************/












