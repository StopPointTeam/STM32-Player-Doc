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

//DAC ʵ��

//STM32H7����ģ��-HAL�⺯���汾
//DevEBox  ��Խ����
//�Ա����̣�mcudev.taobao.com
//�Ա����̣�shop389957290.taobao.com	
/*********************************************************************/
    u16 adcx;
    float temp;
    u8 t=0;
    u16 dacval=0;
    u8 key;

    u8 tbuf[32];

int main(void)
{

    Cache_Enable();					//��L1-Cache
    HAL_Init();						//��ʼ��HAL��
    Stm32_Clock_Init(160,5,2,4);	//����ʱ��,400Mhz
    delay_init(400);				//��ʱ��ʼ��
    uart_init(115200);				//���ڳ�ʼ��
    LED_Init();						//��ʼ��LEDʱ��
    KEY_Init();
    
	
		LCD_Init();            //��ʼ��2.0�� 240x320 ������  LCD��ʾ
		GBK_Lib_Init();        //Ӳ��GBK�ֿ��ʼ��--(���ʹ�ò����ֿ��Һ�����汾���˴��������Σ������ֿ��ʼ����
		LCD_Clear(WHITE);      //����      								 
		
		
		Draw_Font16B(16,16,RED, "  STM32H7 DAC    ");
		Draw_Font16B(16,32,BLUE,"  Ƕ��ʽ������   ");	 
		Draw_Font16B(16,48,BLUE,"mcudev.taobao.com"); 
	  Draw_Font16B(16,70,BLUE,"K1: DAC+  K2: DAC-");
	
    MY_ADC1_Init();				//��ʼ��ADC1
    DAC1_Init();					//��ʼ��DAC1


    Draw_Font16B(16,100,RED,  "DAC VAL(PA5):");
    Draw_Font16B(16,120,RED, "DAC VOL(PA5):0.000V");
    Draw_Font16B(16,140,RED, "ADC VOL(PC0):0.000V");

    HAL_DAC_SetValue(&DAC1_Handler,DAC_CHANNEL_2,DAC_ALIGN_12B_R,0);//��ʼֵΪ0
		
    while(1)
    {
        t++;
			
        key=KEY_Scan(0);
			
        if(key==KEY1_PRES)
        {
            if(dacval<4000)dacval+=200;
            HAL_DAC_SetValue(&DAC1_Handler,DAC_CHANNEL_2,DAC_ALIGN_12B_R,dacval);//����DACֵ
        } 
				else if(key==KEY2_PRES)
        {
            if(dacval>200)dacval-=200;
            else dacval=0;
            HAL_DAC_SetValue(&DAC1_Handler,DAC_CHANNEL_2,DAC_ALIGN_12B_R,dacval);//����DACֵ
        }
				
        if(t==10||key==KEY1_PRES||key==KEY2_PRES) 	    //KEY1/KEY2������,���߶�ʱʱ�䵽��
        {
					
            adcx=HAL_DAC_GetValue(&DAC1_Handler,DAC_CHANNEL_2);//��ȡǰ������DAC��ֵ
					  
					  sprintf((char*)tbuf,"DAC VAL(PA5): 0x%4X",adcx);  //��ʾDAC�Ĵ���ֵ
					
					  Draw_Font16B(16,100,RED,tbuf); 	 //��ʾDAC�Ĵ���ֵ
					            	   
            temp=(float)adcx*(3.3/4096);			    //�õ�DAC��ѹֵ
 
					  sprintf((char*)tbuf,"DAC VOL(PA5): %5.3f ",temp);  //��ʾ��ѹֵ
					
					  Draw_Font16B(16,120,RED,tbuf); 	 //��ʾ��ѹֵ
										

		        adcx=Get_Adc_Average(ADC1_Handler,ADC_CHANNEL_10,20);//��ȡͨ��10��ת��ֵ��20��ȡƽ��  PC0���ţ���ӦADC1��CH10ͨ��������������Ϣ����ο������ֲ�
							
            temp=(float)adcx*(3.3/65536);			    //�õ�ADC��ѹֵ
					  
					  sprintf((char*)tbuf,"ADC VOL(PC0): %5.3f ",temp);  //��ʾ��ѹֵ
					
					  Draw_Font16B(16,140,RED,tbuf); 	 //��ʾ��ѹֵ            
					
            LED2_Toggle;
            t=0;
					
        }
        delay_ms(10);
    }
}





































/**********************************************************************/

//DAC ʵ��

//STM32H7����ģ��-HAL�⺯���汾
//DevEBox  ��Խ����
//�Ա����̣�mcudev.taobao.com
//�Ա����̣�shop389957290.taobao.com	
/*********************************************************************/




