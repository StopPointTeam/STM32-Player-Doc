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
//SD�� ʵ��

//STM32H7����ģ��-HAL�⺯���汾
//DevEBox  ��Խ����
//�Ա����̣�mcudev.taobao.com
//�Ա����̣�shop389957290.taobao.com	

/********************************************************/





//ͨ�����ڴ�ӡSD�������Ϣ
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
    printf("Card ManufacturerID:%d\r\n",SDCardInfo.SD_cid.ManufacturerID);	//������ID
    printf("Card RCA:%d\r\n",SDCardInfo.RCA);								//����Ե�ַ
    printf("Card Capacity:%d MB\r\n",(u32)(SDCardInfo.CardCapacity>>20));	//��ʾ����
    printf("Card BlockSize:%d\r\n\r\n",SDCardInfo.CardBlockSize);			//��ʾ���С
}


/********************************************************/
//����SD���Ķ�ȡ
//��secaddr��ַ��ʼ,��ȡseccnt������������
//secaddr:������ַ
//seccnt:������

//STM32H7����ģ��-HAL�⺯���汾
//DevEBox  ��Խ����
//�Ա����̣�mcudev.taobao.com
//�Ա����̣�shop389957290.taobao.com	

/********************************************************/


void sd_test_read(u32 secaddr,u32 seccnt)
{
    u32 i;
    u8 *buf;
    u8 sta=0;
    buf=mymalloc(SRAMIN,seccnt*512);	//�����ڴ�,��SDRAM�����ڴ�
    sta=SD_ReadDisk(buf,secaddr,seccnt);//��ȡsecaddr������ʼ������
    if(sta==0)
    {
        printf("SECTOR %d DATA:\r\n",secaddr);
        for(i=0; i<seccnt*512; i++)printf("%x ",buf[i]); //��ӡsecaddr��ʼ����������
        printf("\r\nDATA ENDED\r\n");
    } else printf("err:%d\r\n",sta);
    myfree(SRAMIN,buf);	//�ͷ��ڴ�
}




/********************************************************/
//����SD����д��(����,���дȫ��0XFF������,���������SD��.)
//��secaddr��ַ��ʼ,д��seccnt������������
//secaddr:������ַ
//seccnt:������

//STM32H7����ģ��-HAL�⺯���汾
//DevEBox  ��Խ����
//�Ա����̣�mcudev.taobao.com
//�Ա����̣�shop389957290.taobao.com	

/********************************************************/


void sd_test_write(u32 secaddr,u32 seccnt)
{
    u32 i;
    u8 *buf;
    u8 sta=0;
    buf=mymalloc(SRAMIN,seccnt*512);	//��SDRAM�����ڴ�
    for(i=0; i<seccnt*512; i++) 			//��ʼ��д�������,��3�ı���.
    {
        buf[i]=i*3;
    }
    sta=SD_WriteDisk(buf,secaddr,seccnt);//��secaddr������ʼд��seccnt����������
    if(sta==0)
    {
        printf("Write over!\r\n");
    } else printf("err:%d\r\n",sta);
    myfree(SRAMIN,buf);					//�ͷ��ڴ�
}



/********************************************************/
//Main ������

//STM32H7����ģ��-HAL�⺯���汾
//DevEBox  ��Խ����
//�Ա����̣�mcudev.taobao.com
//�Ա����̣�shop389957290.taobao.com	

/********************************************************/


u8 tbuf[32];

int main(void)
{
    u8 key;
    u32 sd_size;
    u8 t=0;
    u8 *buf;
	
    Cache_Enable();                  //��L1-Cache
    HAL_Init();				        		   //��ʼ��HAL��
    Stm32_Clock_Init(160,5,2,4);  	 //����ʱ��,400Mhz
    delay_init(400);						     //��ʱ��ʼ��
    uart_init(115200);						   //���ڳ�ʼ��
    
    LED_Init();							        //��ʼ��LED
    KEY_Init();					       			//��ʼ������
	
		LCD_Init();            //��ʼ��2.0�� 240x320 ������  LCD��ʾ
		GBK_Lib_Init();        //Ӳ��GBK�ֿ��ʼ��--(���ʹ�ò����ֿ��Һ�����汾���˴��������Σ������ֿ��ʼ����
		LCD_Clear(WHITE);      //����  
	
    my_mem_init(SRAMIN);			//��ʼ���ڲ��ڴ��(AXI)
//    //my_mem_init(SRAMEX);			//��ʼ���ⲿ�ڴ��(SDRAM)
//    my_mem_init(SRAM12);			//��ʼ��SRAM12�ڴ��(SRAM1+SRAM2)
//    my_mem_init(SRAM4);				//��ʼ��SRAM4�ڴ��(SRAM4)
//    my_mem_init(SRAMDTCM);			//��ʼ��DTCM�ڴ��(DTCM)
//    my_mem_init(SRAMITCM);			//��ʼ��ITCM�ڴ��(ITCM)
	
	
    Draw_Font16B(16,16,RED,"  STM32H7 SD Card ");
		Draw_Font16B(16,32,BLUE,"  Ƕ��ʽ������   ");	 
		Draw_Font16B(16,48,BLUE,"mcudev.taobao.com"); 
		Draw_Font16B(16,64,BLUE, "KEY2:Read Sector 0"); 


    while(SD_Init())//��ⲻ��SD��
    {
        Draw_Font16B(16,90,RED,"SD Card Error!");
        delay_ms(500);
        Draw_Font16B(16,90,RED,"Please Check! ");
        delay_ms(500);
        LED2_Toggle;//D2��˸
    }
		
		
    show_sdcard_info();	//��ӡSD�������Ϣ
                                        
    Draw_Font16B(16,90,BLUE,"SD Card OK    "); //���SD���ɹ�
		
		sprintf((char*)tbuf,"SD Card Size: %u MB",SDCardInfo.CardCapacity>>20); //��ʾ�޷���ʮ��������		
   
		Draw_Font16B(16,110,BLUE,tbuf);  //��ʾ�洢������
    
		
    while(1)
    {
        key=KEY_Scan(0);
			
        if(key==KEY2_PRES)//KEY2������
        {
            buf=mymalloc(SRAMIN,2048);		//�����ڴ�2K
					
            key=SD_ReadDisk(buf,0,1);
					
            if(key==0)	//��ȡ0����������
            {
                Draw_Font16B(16,130,BLUE,"USART1 Sending ...");
							
                printf("SECTOR 0 DATA:\r\n");
							
                for(sd_size=0; sd_size<512; sd_size++)printf("%x ",buf[sd_size]); //��ӡ0��������
							
                printf("\r\nDATA ENDED\r\n");
							
                Draw_Font16B(16,130,BLUE,"USART1 Send  Over!");
							
            } 
						else printf("err:%d\r\n",key);
						
            myfree(SRAMIN,buf);//�ͷ��ڴ�
        }
        t++;
        delay_ms(10);
        if(t==20)
        {
            LED2_Toggle;//D2��˸
            t=0;
        }
    }
}































/********************************************************/
//SD�� ʵ��

//STM32H7����ģ��-HAL�⺯���汾
//DevEBox  ��Խ����
//�Ա����̣�mcudev.taobao.com
//�Ա����̣�shop389957290.taobao.com	

/********************************************************/





