#ifndef _DELAY_H
#define _DELAY_H
#include <sys.h>	  
//////////////////////////////////////////////////////////////////////////////////  

//STM32H7开发板
//使用SysTick的普通计数模式对延迟进行管理(支持ucosii)
//包括delay_us,delay_ms

//STM32H7工程模板-HAL库函数版本
//DevEBox  大越创新
//淘宝店铺：mcudev.taobao.com
//淘宝店铺：shop389957290.taobao.com	
//********************************************************************************
////////////////////////////////////////////////////////////////////////////////// 

void delay_init(u16 SYSCLK);
void delay_ms(u16 nms);
void delay_us(u32 nus);
#endif









//STM32H7工程模板-HAL库函数版本
//DevEBox  大越创新
//淘宝店铺：mcudev.taobao.com
//淘宝店铺：shop389957290.taobao.com	

