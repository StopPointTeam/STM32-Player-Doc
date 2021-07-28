#ifndef __Lcd_Driver_H
#define __Lcd_Driver_H

#include "sys.h"
#include "stdint.h"


#define X_MAX_PIXEL	        128
#define Y_MAX_PIXEL	        128


//********************************************************************************

//DevEBox  ��Խ���ӣ�Ƕ��ʽ��������
//�Ա����̣�mcudev.taobao.com
//�Ա����̣�shop389957290.taobao.com	

//********************************************************************************


//STM32���İ�����

//�⺯���汾����



#define RED  	  0xf800
#define GREEN	  0x07e0
#define BLUE 	  0x001f
#define WHITE	  0xffff
#define BLACK	  0x0000
#define YELLOW  0xFFE0
#define GRAY0   0xEF7D   	//��ɫ0 
#define GRAY1   0x8410    //��ɫ1 
#define GRAY2   0x4208    //��ɫ2 




//Һ�����ƿ���1�������궨��
#define	LCD_SDA_SET  	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_15,GPIO_PIN_SET) 	   //PB15��1 

#define	LCD_SCL_SET  	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_13,GPIO_PIN_SET)	     //PB13��1 

#define	LCD_CS_SET  	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_12,GPIO_PIN_SET)	     //PB12��1  

#define LCD_RST_Set()  HAL_GPIO_WritePin(GPIOB,GPIO_PIN_14,GPIO_PIN_SET)	   //PB14��1 

#define	LCD_RS_SET  	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_1,GPIO_PIN_SET)		   //PB1��1  

#define	LCD_BLK_SET  	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_0,GPIO_PIN_SET) 	     //PB0��1 


//Һ�����ƿ���0�������궨��

#define	LCD_SDA_CLR  	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_15,GPIO_PIN_RESET)  	  //PB15��0 //DIN

#define	LCD_SCL_CLR  	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_13,GPIO_PIN_RESET)	    //PB13��0 //CLK

#define	LCD_CS_CLR  	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_12,GPIO_PIN_RESET)	   	//PB12��0/CS

#define LCD_RST_Clr()  HAL_GPIO_WritePin(GPIOB,GPIO_PIN_14,GPIO_PIN_RESET)	  //PB14��0 //RES

#define	LCD_RS_CLR  	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_1,GPIO_PIN_RESET)		 	//PB1��0 //DC

#define	LCD_BLK_CLR  	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_0,GPIO_PIN_RESET)  	  //PB0��0 //DIN






void LCD_GPIO_Init(void);
void Lcd_WriteIndex(uint8_t Index);
void Lcd_WriteData(uint8_t Data);
void Lcd_WriteReg(uint8_t Index,uint8_t Data);
uint16_t Lcd_ReadReg(uint8_t LCD_Reg);
void Lcd_Reset(void);
void Lcd_Init(void);
void Lcd_Clear(uint16_t Color);
void Lcd_SetXY(uint16_t x,uint16_t y);
void Gui_DrawPoint(uint16_t x,uint16_t y,uint16_t Data);
void Lcd_SetRegion(uint16_t x_start,uint16_t y_start,uint16_t x_end,uint16_t y_end);
void LCD_WriteData_16Bit(uint16_t Data);

#endif



//********************************************************************************

//DevEBox  ��Խ���ӣ�Ƕ��ʽ��������
//�Ա����̣�mcudev.taobao.com
//�Ա����̣�shop389957290.taobao.com	

//********************************************************************************













