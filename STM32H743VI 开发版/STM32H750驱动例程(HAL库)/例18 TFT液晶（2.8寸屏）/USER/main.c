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

//2.8��  LCD��ʾʵ��-�⺯���汾

//STM32H7����ģ��-HAL�⺯���汾
//DevEBox  ��Խ����
//�Ա����̣�mcudev.taobao.com
//�Ա����̣�shop389957290.taobao.com	

/************************************************************************************************/

int main(void)
{
    Cache_Enable();									//��L1-Cache
    HAL_Init();										  //��ʼ��HAL��
    Stm32_Clock_Init(160,5,2,4);		//����ʱ��,400Mhz
    delay_init(400);								//��ʱ��ʼ��
    uart_init(115200);							//���ڳ�ʼ��
    LED_Init();										  //��ʼ��LED
	
		LCD_Init();            //��ʼ��LCD2.8�� SPI �ӿ�
		
		GBK_Lib_Init();        //Ӳ��GBK�ֿ��ʼ��--(���ʹ�ò����ֿ��Һ�����汾���˴��������Σ������ֿ��ʼ����
		
		POINT_COLOR=RED;       //������ɫ����ɫ

    while(1)
    {
			
				Demo_Menu();  //��ʾ����	//Һ��������DEMO	
        LED2_Toggle;	//LED0��˸
        delay_ms(1000);
			
    }
}




























































/************************************************************************************************/

//STM32H7����ģ��-HAL�⺯���汾
//DevEBox  ��Խ����
//�Ա����̣�mcudev.taobao.com
//�Ա����̣�shop389957290.taobao.com	

/************************************************************************************************/


