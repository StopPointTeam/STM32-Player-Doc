#ifndef __RTC_H
#define __RTC_H
#include "sys.h"
//////////////////////////////////////////////////////////////////////////////////	 

/**************************************************************************************

//RTC��������	

//DevEBox  ��Խ���ӣ�Ƕ��ʽ��������
//�Ա����̣�mcudev.taobao.com
//�Ա����̣�shop389957290.taobao.com	

**************************************************************************************/

////////////////////////////////////////////////////////////////////////////////// 	

extern RTC_HandleTypeDef RTC_Handler;  //RTC���
    
u8 RTC_Init(void);              //RTC��ʼ��
u8 RTC_Wait_Synchro(void);								//�ȴ�ͬ��
HAL_StatusTypeDef RTC_Set_Time(u8 hour,u8 min,u8 sec,u8 ampm);      //RTCʱ������
HAL_StatusTypeDef RTC_Set_Date(u8 year,u8 month,u8 date,u8 week);	//RTC��������
void RTC_Set_AlarmA(u8 week,u8 hour,u8 min,u8 sec); //��������ʱ��(����������,24Сʱ��)
void RTC_Set_WakeUp(u32 wksel,u16 cnt);             //�����Ի��Ѷ�ʱ������
u8 RTC_DEC2BCD(u8 val);									//ʮ����ת��ΪBCD��
u8 RTC_BCD2DEC(u8 val);									//BCD��ת��Ϊʮ��������
void RTC_Get_Time(u8 *hour,u8 *min,u8 *sec,u8 *ampm);
void RTC_Get_Date(u8 *year,u8 *month,u8 *date,u8 *week);

#endif























/**************************************************************************************

//RTC��������	

//DevEBox  ��Խ���ӣ�Ƕ��ʽ��������
//�Ա����̣�mcudev.taobao.com
//�Ա����̣�shop389957290.taobao.com	

**************************************************************************************/





