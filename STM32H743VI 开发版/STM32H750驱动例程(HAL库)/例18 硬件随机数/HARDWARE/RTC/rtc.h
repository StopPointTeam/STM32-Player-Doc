#ifndef __RTC_H
#define __RTC_H
#include "sys.h"
//////////////////////////////////////////////////////////////////////////////////	 

/**************************************************************************************

//RTC驱动代码	

//DevEBox  大越电子（嵌入式开发网）
//淘宝店铺：mcudev.taobao.com
//淘宝店铺：shop389957290.taobao.com	

**************************************************************************************/

////////////////////////////////////////////////////////////////////////////////// 	

extern RTC_HandleTypeDef RTC_Handler;  //RTC句柄
    
u8 RTC_Init(void);              //RTC初始化
u8 RTC_Wait_Synchro(void);								//等待同步
HAL_StatusTypeDef RTC_Set_Time(u8 hour,u8 min,u8 sec,u8 ampm);      //RTC时间设置
HAL_StatusTypeDef RTC_Set_Date(u8 year,u8 month,u8 date,u8 week);	//RTC日期设置
void RTC_Set_AlarmA(u8 week,u8 hour,u8 min,u8 sec); //设置闹钟时间(按星期闹铃,24小时制)
void RTC_Set_WakeUp(u32 wksel,u16 cnt);             //周期性唤醒定时器设置
u8 RTC_DEC2BCD(u8 val);									//十进制转换为BCD码
u8 RTC_BCD2DEC(u8 val);									//BCD码转换为十进制数据
void RTC_Get_Time(u8 *hour,u8 *min,u8 *sec,u8 *ampm);
void RTC_Get_Date(u8 *year,u8 *month,u8 *date,u8 *week);

#endif























/**************************************************************************************

//RTC驱动代码	

//DevEBox  大越电子（嵌入式开发网）
//淘宝店铺：mcudev.taobao.com
//淘宝店铺：shop389957290.taobao.com	

**************************************************************************************/





