#ifndef __USBD_CDC_IF_H
#define __USBD_CDC_IF_H
#include "usbd_cdc.h"
//////////////////////////////////////////////////////////////////////////////////	 

//usb vcp驱动代码	  

/**************************************************************************/
//usbd_conf 驱动代码	  

//STM32H7工程模板-HAL库函数版本
//DevEBox  大越创新
//淘宝店铺：mcudev.taobao.com
//淘宝店铺：shop389957290.taobao.com		

/**************************************************************************/
							  
////////////////////////////////////////////////////////////////////////////////// 

#define USB_USART_REC_LEN	 	200     //USB串口接收缓冲区最大字节数
//轮询周期，最大65ms，最小1ms
#define CDC_POLLING_INTERVAL    1       //轮询周期，最大65ms，最小1ms

extern u8  USB_USART_RX_BUF[USB_USART_REC_LEN]; //接收缓冲,最大USB_USART_REC_LEN个字节.末字节为换行符 
extern u16 USB_USART_RX_STA;   					//接收状态标记	
extern USBD_CDC_ItfTypeDef  USBD_CDC_fops;

void VCP_DataTx(uint8_t *data,uint32_t Len);
uint16_t VCP_DataRx(uint8_t* Buf, uint32_t Len);
void usb_printf(char* fmt,...); 

#endif 

