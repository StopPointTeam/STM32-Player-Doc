#ifndef _TIMER_H
#define _TIMER_H
#include "sys.h"
//////////////////////////////////////////////////////////////////////////////////	 

  
/************************************************************************************/
//定时器驱动代码	 


//STM32H7工程模板-HAL库函数版本
//DevEBox  大越创新
//淘宝店铺：mcudev.taobao.com
//淘宝店铺：shop389957290.taobao.com	

/************************************************************************************/							  
////////////////////////////////////////////////////////////////////////////////// 
extern TIM_HandleTypeDef TIM3_Handler;      //定时器3PWM句柄 
extern TIM_OC_InitTypeDef TIM3_CH4Handler; 	//定时器3通道4句柄

void TIM3_Init(u16 arr,u16 psc);    		//定时器初始化
void TIM3_PWM_Init(u16 arr,u16 psc);
void TIM_SetTIM3Compare4(u32 compare);
#endif



























/************************************************************************************/

//STM32H7工程模板-HAL库函数版本
//DevEBox  大越创新
//淘宝店铺：mcudev.taobao.com
//淘宝店铺：shop389957290.taobao.com	

/************************************************************************************/











