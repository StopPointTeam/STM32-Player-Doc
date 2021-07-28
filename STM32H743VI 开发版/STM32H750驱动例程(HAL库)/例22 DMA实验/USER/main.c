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
//DMA ʵ��  

//STM32H7����ģ��-HAL�⺯���汾
//DevEBox  ��Խ����
//�Ա����̣�mcudev.taobao.com
//�Ա����̣�shop389957290.taobao.com		

/*********************************************************************/


#define SEND_BUF_SIZE 7800	//�������ݳ���,��õ���sizeof(TEXT_TO_SEND)+2��������.

u8 SendBuff[SEND_BUF_SIZE];	//�������ݻ�����
const u8 TEXT_TO_SEND[]={" mcudev.taobao.com STM32H7XXX DMA ����ʵ��  "};	

	u16 i;
	u8 t=0;
	u8 j,mask=0;
	float pro=0;

u8 tbuf[32];

int main(void)
{

	Cache_Enable();					      //��L1-Cache
	Stm32_Clock_Init(160,5,2,4);	//����ʱ��,400Mhz 
	HAL_Init();				            //��ʼ��HAL��
	delay_init(400);		      		//��ʱ��ʼ��
	uart_init(115200);			     	//���ڳ�ʼ��
	LED_Init();				         		//��ʼ��LEDʱ��
	KEY_Init();
	
	MPU_Memory_Protection();		//������ش洢����
	
	LCD_Init();            //��ʼ��2.0�� 240x320 ������  LCD��ʾ
	GBK_Lib_Init();        //Ӳ��GBK�ֿ��ʼ��--(���ʹ�ò����ֿ��Һ�����汾���˴��������Σ������ֿ��ʼ����
	LCD_Clear(WHITE);      //����  
	
	
	MYDMA_Config(DMA2_Stream7);		//��ʼ��DMA
	
	Draw_Font16B(16,16,RED,"  STM32H7 DMA    ");
  Draw_Font16B(16,32,BLUE,"  Ƕ��ʽ������   ");	 
	Draw_Font16B(16,48,BLUE,"mcudev.taobao.com"); 
	Draw_Font24B(16,64,RED, "KEY2:Start"); 

	//��ʾ��ʾ��Ϣ	
	j=sizeof(TEXT_TO_SEND);	 
  
	for(i=0;i<SEND_BUF_SIZE;i++)//���ASCII�ַ�������
	{
		if(t>=j)//���뻻�з�
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
		else//����TEXT_TO_SEND���
		{
			mask=0;
			SendBuff[i]=TEXT_TO_SEND[t];
			t++;
		}   	   
	}		 
	POINT_COLOR=BLUE;//��������Ϊ��ɫ	  
	i=0;
	while(1)
	{
		t=KEY_Scan(0);
		
		if(t==KEY2_PRES)//KEY0����
		{
			printf("\r\nDMA DATA:\r\n"); 	  
			
			Draw_Font24B(8,90,RED, "Start Transimit..  ");
			Draw_Font24B(8,120,RED,"   %               ");//��ʾ�ٷֺ�
			
			HAL_UART_Transmit_DMA(&UART1_Handler,SendBuff,SEND_BUF_SIZE);//����DMA����
			
			  //ʹ�ܴ���1��DMA���͵ȴ�DMA������ɣ���ʱ������������һЩ�£����
		    //ʵ��Ӧ���У����������ڼ䣬����ִ�����������
		  while(1)
		    {
          if(__HAL_DMA_GET_FLAG(&UART1TxDMA_Handler,DMA_FLAG_TCIF3_7))//�ȴ�DMA2_Steam7�������
            {
               __HAL_DMA_CLEAR_FLAG(&UART1TxDMA_Handler,DMA_FLAG_TCIF3_7);//���DMA2_Steam7������ɱ�־
               HAL_UART_DMAStop(&UART1_Handler);      //��������Ժ�رմ���DMA
					     break; 
            }
						
					pro=__HAL_DMA_GET_COUNTER(&UART1TxDMA_Handler);//�õ���ǰ��ʣ����ٸ�����
							
					pro=1-pro/SEND_BUF_SIZE;    //�õ��ٷֱ�	 
							
					pro*=100;      			    //����100��
					sprintf((char*)tbuf,"%5.2f % ",pro); //��ʾ�޷���ʮ��������		
					Draw_Font24B(16,120,RED, tbuf);//��ʾ�ٷֺ�//��ʾ100%	
						
		    }
				
			Draw_Font24B(8,120,RED, "100%               ");//��ʾ�ٷֺ�//��ʾ100%	  
		  Draw_Font24B(8,90, RED, "Transimit Finished!");//��ʾ�������
		}
		i++;
		delay_ms(10);
		if(i==20)
		{
			LED2_Toggle;//��ʾϵͳ��������	
			i=0;
		}		   
	}
}
























/*********************************************************************/
//DMA ʵ��  

//STM32H7����ģ��-HAL�⺯���汾
//DevEBox  ��Խ����
//�Ա����̣�mcudev.taobao.com
//�Ա����̣�shop389957290.taobao.com		

/*********************************************************************/












