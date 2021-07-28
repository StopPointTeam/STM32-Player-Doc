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

  
/********************************************************************************/
//ADC 实验 PC0引脚，对应ADC1的CH10通道，具体引脚信息，参考数据手册

//STM32H7工程模板-HAL库函数版本
//DevEBox  大越创新
//淘宝店铺：mcudev.taobao.com
//淘宝店铺：shop389957290.taobao.com	

/******************************************************************************/

	u16 adcx;
	float temp;
  u8 tbuf[32];

int main(void)
{

	Cache_Enable();								//打开L1-Cache
	HAL_Init();										//初始化HAL库
	Stm32_Clock_Init(160,5,2,4);	//设置时钟,400Mhz
	delay_init(400);							//延时初始化
	uart_init(115200);						//串口初始化
	LED_Init();										//初始化LED时钟
	KEY_Init();
	
	LCD_Init();            //初始化2.0寸 240x320 高清屏  LCD显示
	GBK_Lib_Init();        //硬件GBK字库初始化--(如果使用不带字库的液晶屏版本，此处可以屏蔽，不做字库初始化）
	LCD_Clear(WHITE);      //清屏  
	
	MY_ADC_Init();					//初始化ADC1通道--PC0引脚，对应ADC1的CH10通道，更多引脚信息，请参考数据手册
	
	Draw_Font16B(16,16,RED,"  STM32H7 ADC    ");
  Draw_Font16B(16,32,BLUE,"  嵌入式开发网   ");	 
	Draw_Font16B(16,48,BLUE,"mcudev.taobao.com"); 

  
	while(1)
	{
		adcx=Get_Adc_Average(ADC_CHANNEL_10,20);//获取通道10的转换值，20次取平均  PC0引脚，对应ADC1的CH10通道，更多引脚信息，请参考数据手册
		
		sprintf((char*)tbuf,"ADC_CH10(PC0):"); //显示无符号十六进制整数
		Draw_Font24B(8,80,RED,tbuf); //显示ADCC采样后的原始值
		
		sprintf((char*)tbuf,"0x%4X",adcx); //显示无符号十六进制整数
		Draw_Font24B(120,110,RED,tbuf); //显示ADCC采样后的原始值
		
		temp=(float)adcx*(3.3/65536);         //获取计算后的带小数的实际电压值，比如3.1111

		sprintf((char*)tbuf,"CH10_VDD: %5.3f V",temp); //显示无符号十进制整数
		Draw_Font24B(8,140,RED,tbuf); //显示电压值
			
		LED2_Toggle;
		delay_ms(250);	
		
	}
}






































/********************************************************************************/
//ADC 实验 

//STM32H7工程模板-HAL库函数版本
//DevEBox  大越创新
//淘宝店铺：mcudev.taobao.com
//淘宝店铺：shop389957290.taobao.com	

/******************************************************************************/









































