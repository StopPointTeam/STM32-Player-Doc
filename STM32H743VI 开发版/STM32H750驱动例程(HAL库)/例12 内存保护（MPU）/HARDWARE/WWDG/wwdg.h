#ifndef __WWDG_H
#define __WWDG_H
#include "sys.h"
//////////////////////////////////////////////////////////////////////////////////	 




/**********************************************************************************/
//窗口看门狗驱动代码	   


//STM32H7工程模板-HAL库函数版本
//DevEBox  大越创新
//淘宝店铺：mcudev.taobao.com
//淘宝店铺：shop389957290.taobao.com	

/**********************************************************************************/
////////////////////////////////////////////////////////////////////////////////// 	
extern WWDG_HandleTypeDef WWDG_Handler;     //窗口看门狗句柄

void WWDG_Init(u8 tr,u8 wr,u32 fprer);
#endif























/**********************************************************************************/

//STM32H7工程模板-HAL库函数版本
//DevEBox  大越创新
//淘宝店铺：mcudev.taobao.com
//淘宝店铺：shop389957290.taobao.com	

/**********************************************************************************/



