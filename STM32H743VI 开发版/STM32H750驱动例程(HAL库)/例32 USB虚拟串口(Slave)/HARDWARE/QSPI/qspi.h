#ifndef __QSPI_H
#define __QSPI_H
#include "sys.h"
//////////////////////////////////////////////////////////////////////////////////	 
   
/**********************************************************************/

//QSPI驱动代码	

//STM32H7工程模板-HAL库函数版本
//DevEBox  大越创新
//淘宝店铺：mcudev.taobao.com
//淘宝店铺：shop389957290.taobao.com	
  
/**********************************************************************/					  
////////////////////////////////////////////////////////////////////////////////// 	
extern QSPI_HandleTypeDef QSPI_Handler;    //QSPI句柄

u8 QSPI_Init(void);												//初始化QSPI
void QSPI_Send_CMD(u8 cmd,u32 addr,u8 mode,u8 dmcycle);			//QSPI发送命令
u8 QSPI_Receive(u8* buf,u32 datalen);							//QSPI接收数据
u8 QSPI_Transmit(u8* buf,u32 datalen);							//QSPI发送数据
#endif


















/**********************************************************************/

//QSPI驱动代码	

//STM32H7工程模板-HAL库函数版本
//DevEBox  大越创新
//淘宝店铺：mcudev.taobao.com
//淘宝店铺：shop389957290.taobao.com	
  
/**********************************************************************/	


