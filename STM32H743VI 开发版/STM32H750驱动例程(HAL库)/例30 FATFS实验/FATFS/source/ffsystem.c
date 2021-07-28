/*------------------------------------------------------------------------*/
/* Sample Code of OS Dependent Functions for FatFs                        */
/* (C)ChaN, 2017                                                          */
/*------------------------------------------------------------------------*/
#include "ff.h"
#include "sys.h"
#include "malloc.h"
//////////////////////////////////////////////////////////////////////////////////	 
   
/****************************************************************/
//FATFS底层(ffsystem) 驱动代码	


//STM32H7工程模板-HAL库函数版本
//DevEBox  大越创新
//淘宝店铺：mcudev.taobao.com
//淘宝店铺：shop389957290.taobao.com			
/****************************************************************/							  
////////////////////////////////////////////////////////////////////////////////// 



//获得时间
//User defined function to give a current time to fatfs module      */
//31-25: Year(0-127 org.1980), 24-21: Month(1-12), 20-16: Day(1-31) */                                                                                                                                                                                                                                          
//15-11: Hour(0-23), 10-5: Minute(0-59), 4-0: Second(0-29 *2) */                                                                                                                                                                                                                                                
DWORD get_fattime (void)
{				 
	return 0;
}

//动态分配内存
void *ff_memalloc (UINT size)			
{
	return (void*)mymalloc(SRAMIN,size);
}

//释放内存
void ff_memfree (void* mf)		 
{
	myfree(SRAMIN,mf);
}











