#include "sys.h"
#include "usart.h"
#include "delay.h"
#include "led.h"
#include "key.h"

#include "lcd.h"
#include "Dis_Picture.h" 
#include "Text.h"	
#include "GBK_LibDrive.h"	



/************************************************************************************************/

//2.8寸  LCD显示实验-库函数版本

//STM32H7工程模板-HAL库函数版本
//DevEBox  大越创新
//淘宝店铺：mcudev.taobao.com
//淘宝店铺：shop389957290.taobao.com	

/************************************************************************************************/

int main(void)
{
    Cache_Enable();									//打开L1-Cache
    HAL_Init();										  //初始化HAL库
    Stm32_Clock_Init(160,5,2,4);		//设置时钟,400Mhz
    delay_init(400);								//延时初始化
    uart_init(115200);							//串口初始化
    LED_Init();										  //初始化LED
	
		LCD_Init();            //初始化LCD2.8寸 SPI 接口
		
		GBK_Lib_Init();        //硬件GBK字库初始化--(如果使用不带字库的液晶屏版本，此处可以屏蔽，不做字库初始化）
		
		POINT_COLOR=RED;       //画笔颜色：红色

    while(1)
    {
			
				Demo_Menu();  //演示程序	//液晶屏测试DEMO	
        LED2_Toggle;	//LED0闪烁
        delay_ms(1000);
			
    }
}




























































/************************************************************************************************/

//STM32H7工程模板-HAL库函数版本
//DevEBox  大越创新
//淘宝店铺：mcudev.taobao.com
//淘宝店铺：shop389957290.taobao.com	

/************************************************************************************************/


