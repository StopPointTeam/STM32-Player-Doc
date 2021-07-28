#include "sys.h"
#include "usart.h"
#include "delay.h"
#include "led.h"
#include "key.h"


#include "LCD.h"
#include "Dis_Picture.h" 
#include "Text.h"	
#include "GBK_LibDrive.h"	

#include "adc.h"
#include "dac.h"

/**********************************************************************/

//DAC 实验

//STM32H7工程模板-HAL库函数版本
//DevEBox  大越创新
//淘宝店铺：mcudev.taobao.com
//淘宝店铺：shop389957290.taobao.com	
/*********************************************************************/
    u16 adcx;
    float temp;
    u8 t=0;
    u16 dacval=0;
    u8 key;

    u8 tbuf[32];

int main(void)
{

    Cache_Enable();					//打开L1-Cache
    HAL_Init();						//初始化HAL库
    Stm32_Clock_Init(160,5,2,4);	//设置时钟,400Mhz
    delay_init(400);				//延时初始化
    uart_init(115200);				//串口初始化
    LED_Init();						//初始化LED时钟
    KEY_Init();
    
	
		LCD_Init();            //初始化2.0寸 240x320 高清屏  LCD显示
		GBK_Lib_Init();        //硬件GBK字库初始化--(如果使用不带字库的液晶屏版本，此处可以屏蔽，不做字库初始化）
		LCD_Clear(WHITE);      //清屏      								 
		
		
		Draw_Font16B(16,16,RED, "  STM32H7 DAC    ");
		Draw_Font16B(16,32,BLUE,"  嵌入式开发网   ");	 
		Draw_Font16B(16,48,BLUE,"mcudev.taobao.com"); 
	  Draw_Font16B(16,70,BLUE,"K1: DAC+  K2: DAC-");
	
    MY_ADC1_Init();				//初始化ADC1
    DAC1_Init();					//初始化DAC1


    Draw_Font16B(16,100,RED,  "DAC VAL(PA5):");
    Draw_Font16B(16,120,RED, "DAC VOL(PA5):0.000V");
    Draw_Font16B(16,140,RED, "ADC VOL(PC0):0.000V");

    HAL_DAC_SetValue(&DAC1_Handler,DAC_CHANNEL_2,DAC_ALIGN_12B_R,0);//初始值为0
		
    while(1)
    {
        t++;
			
        key=KEY_Scan(0);
			
        if(key==KEY1_PRES)
        {
            if(dacval<4000)dacval+=200;
            HAL_DAC_SetValue(&DAC1_Handler,DAC_CHANNEL_2,DAC_ALIGN_12B_R,dacval);//设置DAC值
        } 
				else if(key==KEY2_PRES)
        {
            if(dacval>200)dacval-=200;
            else dacval=0;
            HAL_DAC_SetValue(&DAC1_Handler,DAC_CHANNEL_2,DAC_ALIGN_12B_R,dacval);//设置DAC值
        }
				
        if(t==10||key==KEY1_PRES||key==KEY2_PRES) 	    //KEY1/KEY2按下了,或者定时时间到了
        {
					
            adcx=HAL_DAC_GetValue(&DAC1_Handler,DAC_CHANNEL_2);//读取前面设置DAC的值
					  
					  sprintf((char*)tbuf,"DAC VAL(PA5): 0x%4X",adcx);  //显示DAC寄存器值
					
					  Draw_Font16B(16,100,RED,tbuf); 	 //显示DAC寄存器值
					            	   
            temp=(float)adcx*(3.3/4096);			    //得到DAC电压值
 
					  sprintf((char*)tbuf,"DAC VOL(PA5): %5.3f ",temp);  //显示电压值
					
					  Draw_Font16B(16,120,RED,tbuf); 	 //显示电压值
										

		        adcx=Get_Adc_Average(ADC1_Handler,ADC_CHANNEL_10,20);//获取通道10的转换值，20次取平均  PC0引脚，对应ADC1的CH10通道，更多引脚信息，请参考数据手册
							
            temp=(float)adcx*(3.3/65536);			    //得到ADC电压值
					  
					  sprintf((char*)tbuf,"ADC VOL(PC0): %5.3f ",temp);  //显示电压值
					
					  Draw_Font16B(16,140,RED,tbuf); 	 //显示电压值            
					
            LED2_Toggle;
            t=0;
					
        }
        delay_ms(10);
    }
}





































/**********************************************************************/

//DAC 实验

//STM32H7工程模板-HAL库函数版本
//DevEBox  大越创新
//淘宝店铺：mcudev.taobao.com
//淘宝店铺：shop389957290.taobao.com	
/*********************************************************************/




