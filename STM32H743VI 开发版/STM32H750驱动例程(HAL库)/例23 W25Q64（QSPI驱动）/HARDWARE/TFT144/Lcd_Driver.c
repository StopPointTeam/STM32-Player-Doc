#include "sys.h"
#include "Lcd_Driver.h"
#include "delay.h"





//********************************************************************************

//DevEBox  ��Խ���ӣ�Ƕ��ʽ��������
//�Ա����̣�mcudev.taobao.com
//�Ա����̣�shop389957290.taobao.com	

//********************************************************************************


//STM32���İ�����
//�⺯���汾����

//�����Գ���ʹ�õ���ģ��SPI�ӿ�����
//�����ɸ��Ľӿ�IO���ã�ʹ����������4 IO������ɱ���Һ��������ʾ

/******************************************************************************
�ӿڶ�����Lcd_Driver.h�ڶ��壬����ݽ����޸Ĳ��޸���ӦIO��ʼ��LCD_GPIO_Init()

//  ----------------------------------------------------------------
// VCC  ��5V��3.3v��Դ
// GND  ��Դ��
// D1   ��PB15��SDI��
// D0   ��PB13��SCL��
// CS   ��PB12 Ƭѡ    
// RST  ��PB14 ϵͳ��λ
// DC   ��PB1  ����/����  
// BLK  ��PB0 �������    
// ----------------------------------------------------------------

//	#define LCD_SDI        	//PB15
//	#define LCD_SCL        	//PB13
//	#define LCD_CS        	//PB12
//	#define LCD_SDO     		//PB14 
//	#define LCD_RS         	//PB1
//	#define LCD_BLK         //PB0    	
*******************************************************************************/

/**************************************************************************************

��������: void LCD_GPIO_Init(void)

��������: Һ��IO��ʼ������
��    ��: 
��    ��: 

//DevEBox  ��Խ���ӣ�Ƕ��ʽ��������
//�Ա����̣�mcudev.taobao.com
//�Ա����̣�shop389957290.taobao.com	

**************************************************************************************/

void LCD_GPIO_Init(void)
{

    GPIO_InitTypeDef GPIO_Initure;
    __HAL_RCC_GPIOB_CLK_ENABLE();					          //����PBʱ��
	

    GPIO_Initure.Pin=GPIO_PIN_0 |GPIO_PIN_1 | GPIO_PIN_12| GPIO_PIN_13| GPIO_PIN_14| GPIO_PIN_15;	//PB
    GPIO_Initure.Mode=GPIO_MODE_OUTPUT_PP;  		    //�������
    GPIO_Initure.Pull=GPIO_PULLUP;         			    //����
    GPIO_Initure.Speed=GPIO_SPEED_FREQ_VERY_HIGH;  	//����
    HAL_GPIO_Init(GPIOB,&GPIO_Initure);     	     	//��ʼ��
	  
    HAL_GPIO_WritePin(GPIOB,GPIO_PIN_0,GPIO_PIN_SET);	  //PB0��1 	
	  HAL_GPIO_WritePin(GPIOB,GPIO_PIN_1,GPIO_PIN_SET);	  //PB1��1 
	  HAL_GPIO_WritePin(GPIOB,GPIO_PIN_12,GPIO_PIN_SET);	//PB12��1 
 	  HAL_GPIO_WritePin(GPIOB,GPIO_PIN_13,GPIO_PIN_SET);	//PB13��1 
    HAL_GPIO_WritePin(GPIOB,GPIO_PIN_14,GPIO_PIN_SET);	//PB14��1 
	  HAL_GPIO_WritePin(GPIOB,GPIO_PIN_15,GPIO_PIN_SET);	//PB15��1 
			
		LCD_BLK_SET;//��������
		LCD_BLK_CLR;//�رձ���
		LCD_BLK_SET;//��������
      
}

/**************************************************************************************

��������: void  SPI_WriteData(uint8_t Data)

��������: ��SPI���ߴ���һ��8λ����
��    ��: 
��    ��: 

//DevEBox  ��Խ���ӣ�Ƕ��ʽ��������
//�Ա����̣�mcudev.taobao.com
//�Ա����̣�shop389957290.taobao.com	

**************************************************************************************/

void  SPI_WriteData(uint8_t Data)
{
  	unsigned char i=0;
		for(i=8;i>0;i--)
		{
			if(Data&0x80)	
			LCD_SDA_SET; //�������
				else LCD_SDA_CLR;
			 
				LCD_SCL_CLR;       
				LCD_SCL_SET;
				Data<<=1; 
		}
}





/**************************************************************************************

��������: void  SPI_WriteData(uint8_t Data)

��������: ��Һ����дһ��8λָ��
��    ��: 
��    ��: 

//DevEBox  ��Խ���ӣ�Ƕ��ʽ��������
//�Ա����̣�mcudev.taobao.com
//�Ա����̣�shop389957290.taobao.com	

**************************************************************************************/

void Lcd_WriteIndex(uint8_t Index)
{
   //SPI д����ʱ��ʼ
   LCD_CS_CLR;
   LCD_RS_CLR;
	 SPI_WriteData(Index);
   LCD_CS_SET;
}


/**************************************************************************************

��������: void Lcd_WriteData(uint8_t Data)

��������: ��Һ����дһ��8λ����
��    ��: 
��    ��: 

//DevEBox  ��Խ���ӣ�Ƕ��ʽ��������
//�Ա����̣�mcudev.taobao.com
//�Ա����̣�shop389957290.taobao.com	

**************************************************************************************/

void Lcd_WriteData(uint8_t Data)
{
   LCD_CS_CLR;
   LCD_RS_SET;
   SPI_WriteData(Data);
   LCD_CS_SET; 
}



/**************************************************************************************

��������: void LCD_WriteData_16Bit(uint16_t Data)

��������: ��Һ����дһ��16λ����
��    ��: 
��    ��: 

//DevEBox  ��Խ���ӣ�Ƕ��ʽ��������
//�Ա����̣�mcudev.taobao.com
//�Ա����̣�shop389957290.taobao.com	

**************************************************************************************/

void LCD_WriteData_16Bit(uint16_t Data)
{
   LCD_CS_CLR;
   LCD_RS_SET;
	 SPI_WriteData(Data>>8); 	//д���8λ����
	 SPI_WriteData(Data); 			//д���8λ����
   LCD_CS_SET; 
}


/**************************************************************************************

��������: void Lcd_WriteReg(uint8_t Index,uint8_t Data)

��������: дҺ�����Ĵ���
��    ��: 
��    ��: 

//DevEBox  ��Խ���ӣ�Ƕ��ʽ��������
//�Ա����̣�mcudev.taobao.com
//�Ա����̣�shop389957290.taobao.com	

**************************************************************************************/


void Lcd_WriteReg(uint8_t Index,uint8_t Data)
{
	Lcd_WriteIndex(Index);
  Lcd_WriteData(Data);
}


/**************************************************************************************

��������: void Lcd_Reset(void)

��������: Ӳ��IO����Һ������λ�����ʹ�õ������ֿ�汾����Ļ���˺�����Ч
��    ��: 
��    ��: 

//DevEBox  ��Խ���ӣ�Ƕ��ʽ��������
//�Ա����̣�mcudev.taobao.com
//�Ա����̣�shop389957290.taobao.com	

**************************************************************************************/

void Lcd_Reset(void)
{
  LCD_RST_Clr();//RST�������Ϊ��
	delay_ms(300);
  LCD_RST_Set();//RST�������Ϊ��
	delay_ms(100);
}



/**************************************************************************************

��������: void Lcd_Init(void)

��������: 1.44�� Һ������ʼ��������Һ�����������ǣ�ST7735R.
��    ��: 
��    ��: 

//DevEBox  ��Խ���ӣ�Ƕ��ʽ��������
//�Ա����̣�mcudev.taobao.com
//�Ա����̣�shop389957290.taobao.com	

**************************************************************************************/

void Lcd_Init(void)
{	
	LCD_GPIO_Init();
	Lcd_Reset(); //Reset before LCD Init.

	//LCD Init For 1.44Inch LCD Panel with ST7735R.
	Lcd_WriteIndex(0x11);//Sleep exit 
	delay_ms (120);
		
	//ST7735R Frame Rate
	Lcd_WriteIndex(0xB1); 
	Lcd_WriteData(0x01); 
	Lcd_WriteData(0x2C); 
	Lcd_WriteData(0x2D); 

	Lcd_WriteIndex(0xB2); 
	Lcd_WriteData(0x01); 
	Lcd_WriteData(0x2C); 
	Lcd_WriteData(0x2D); 

	Lcd_WriteIndex(0xB3); 
	Lcd_WriteData(0x01); 
	Lcd_WriteData(0x2C); 
	Lcd_WriteData(0x2D); 
	Lcd_WriteData(0x01); 
	Lcd_WriteData(0x2C); 
	Lcd_WriteData(0x2D); 
	
	Lcd_WriteIndex(0xB4); //Column inversion 
	Lcd_WriteData(0x07); 
	
	//ST7735R Power Sequence
	Lcd_WriteIndex(0xC0); 
	Lcd_WriteData(0xA2); 
	Lcd_WriteData(0x02); 
	Lcd_WriteData(0x84); 
	Lcd_WriteIndex(0xC1); 
	Lcd_WriteData(0xC5); 

	Lcd_WriteIndex(0xC2); 
	Lcd_WriteData(0x0A); 
	Lcd_WriteData(0x00); 

	Lcd_WriteIndex(0xC3); 
	Lcd_WriteData(0x8A); 
	Lcd_WriteData(0x2A); 
	Lcd_WriteIndex(0xC4); 
	Lcd_WriteData(0x8A); 
	Lcd_WriteData(0xEE); 
	
	Lcd_WriteIndex(0xC5); //VCOM 
	Lcd_WriteData(0x0E); 
	
	Lcd_WriteIndex(0x36); //MX, MY, RGB mode 
	Lcd_WriteData(0xC8); 
	
	//ST7735R Gamma Sequence
	Lcd_WriteIndex(0xe0); 
	Lcd_WriteData(0x0f); 
	Lcd_WriteData(0x1a); 
	Lcd_WriteData(0x0f); 
	Lcd_WriteData(0x18); 
	Lcd_WriteData(0x2f); 
	Lcd_WriteData(0x28); 
	Lcd_WriteData(0x20); 
	Lcd_WriteData(0x22); 
	Lcd_WriteData(0x1f); 
	Lcd_WriteData(0x1b); 
	Lcd_WriteData(0x23); 
	Lcd_WriteData(0x37); 
	Lcd_WriteData(0x00); 	
	Lcd_WriteData(0x07); 
	Lcd_WriteData(0x02); 
	Lcd_WriteData(0x10); 

	Lcd_WriteIndex(0xe1); 
	Lcd_WriteData(0x0f); 
	Lcd_WriteData(0x1b); 
	Lcd_WriteData(0x0f); 
	Lcd_WriteData(0x17); 
	Lcd_WriteData(0x33); 
	Lcd_WriteData(0x2c); 
	Lcd_WriteData(0x29); 
	Lcd_WriteData(0x2e); 
	Lcd_WriteData(0x30); 
	Lcd_WriteData(0x30); 
	Lcd_WriteData(0x39); 
	Lcd_WriteData(0x3f); 
	Lcd_WriteData(0x00); 
	Lcd_WriteData(0x07); 
	Lcd_WriteData(0x03); 
	Lcd_WriteData(0x10);  
	
	Lcd_WriteIndex(0x2a);
	Lcd_WriteData(0x00);
	Lcd_WriteData(0x00);
	Lcd_WriteData(0x00);
	Lcd_WriteData(0x7f);

	Lcd_WriteIndex(0x2b);
	Lcd_WriteData(0x00);
	Lcd_WriteData(0x00);
	Lcd_WriteData(0x00);
	Lcd_WriteData(0x9f);
	
	Lcd_WriteIndex(0xF0); //Enable test command  
	Lcd_WriteData(0x01); 
	Lcd_WriteIndex(0xF6); //Disable ram power save mode 
	Lcd_WriteData(0x00); 
	
	Lcd_WriteIndex(0x3A); //65k mode 
	Lcd_WriteData(0x05); 
	
	
	Lcd_WriteIndex(0x29);//Display on	 
}


/***************************************************************************************

��������LCD_Set_Region
���ܣ�����lcd��ʾ�����ڴ�����д�������Զ�����
��ڲ�����xy�����յ�
����ֵ����

//DevEBox  ��Խ���ӣ�Ƕ��ʽ��������
//�Ա����̣�mcudev.taobao.com
//�Ա����̣�shop389957290.taobao.com	

**************************************************************************************/

void Lcd_SetRegion(uint16_t x_start,uint16_t y_start,uint16_t x_end,uint16_t y_end)
{		
	Lcd_WriteIndex(0x2a);
	Lcd_WriteData(0x00);
	Lcd_WriteData(x_start+2);
	Lcd_WriteData(0x00);
	Lcd_WriteData(x_end+2);

	Lcd_WriteIndex(0x2b);
	Lcd_WriteData(0x00);
	Lcd_WriteData(y_start+3);
	Lcd_WriteData(0x00);
	Lcd_WriteData(y_end+3);
	
	Lcd_WriteIndex(0x2c);

}

/***************************************************************************************

��������LCD_Set_XY
���ܣ�����lcd��ʾ��ʼ��
��ڲ�����xy����
����ֵ����

//DevEBox  ��Խ���ӣ�Ƕ��ʽ��������
//�Ա����̣�mcudev.taobao.com
//�Ա����̣�shop389957290.taobao.com	

**************************************************************************************/
void Lcd_SetXY(uint16_t x,uint16_t y)
{
  	Lcd_SetRegion(x,y,x,y);
}

	
/***************************************************************************************

��������LCD_DrawPoint
���ܣ���һ����
��ڲ�������
����ֵ����

//DevEBox  ��Խ���ӣ�Ƕ��ʽ��������
//�Ա����̣�mcudev.taobao.com
//�Ա����̣�shop389957290.taobao.com	

**************************************************************************************/
void Gui_DrawPoint(uint16_t x,uint16_t y,uint16_t Data)
{
	Lcd_SetRegion(x,y,x+1,y+1);
	LCD_WriteData_16Bit(Data);

}    


/***************************************************************************************

��������Lcd_Clear
���ܣ�ȫ����������
��ڲ����������ɫCOLOR
����ֵ����

//DevEBox  ��Խ���ӣ�Ƕ��ʽ��������
//�Ա����̣�mcudev.taobao.com
//�Ա����̣�shop389957290.taobao.com	

**************************************************************************************/
void Lcd_Clear(uint16_t Color)               
{	
   unsigned int i,m;
   Lcd_SetRegion(0,0,X_MAX_PIXEL-1,Y_MAX_PIXEL-1);
   Lcd_WriteIndex(0x2C);
   for(i=0;i<X_MAX_PIXEL;i++)
    for(m=0;m<Y_MAX_PIXEL;m++)
    {	
	  	LCD_WriteData_16Bit(Color);
    }   
}





































/**************************************************************************************

//DevEBox  ��Խ���ӣ�Ƕ��ʽ��������
//�Ա����̣�mcudev.taobao.com
//�Ա����̣�shop389957290.taobao.com	

**************************************************************************************/

