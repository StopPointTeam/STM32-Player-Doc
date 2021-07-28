#ifndef _SDMMC_SDCARD_H
#define _SDMMC_SDCARD_H
#include "sys.h"
//////////////////////////////////////////////////////////////////////////////////	 
 
/**************************************************************************/
//SD卡驱动代码	

//STM32H7工程模板-HAL库函数版本
//DevEBox  大越创新
//淘宝店铺：mcudev.taobao.com
//淘宝店铺：shop389957290.taobao.com		

/**************************************************************************/
							  
//////////////////////////////////////////////////////////////////////////////////

#define SD_TIMEOUT      	((uint32_t)100000000)       //超时时间
#define SD_TRANSFER_OK     	((uint8_t)0x00)
#define SD_TRANSFER_BUSY   	((uint8_t)0x01)

#define SD_DMA_MODE     0	                        	//1：DMA模式，0：查询模式   

extern SD_HandleTypeDef        SDCARD_Handler;      	//SD卡句柄
extern HAL_SD_CardInfoTypeDef  SDCardInfo;          	//SD卡信息结构体

u8 SD_Init(void);
u8 SD_GetCardInfo(HAL_SD_CardInfoTypeDef *cardinfo);
u8 SD_GetCardState(void);
u8 SD_ReadDisk(u8* buf,u32 sector,u32 cnt);
u8 SD_WriteDisk(u8 *buf,u32 sector,u32 cnt);
u8 SD_ReadBlocks_DMA(uint32_t *buf,uint64_t sector,uint32_t blocksize,uint32_t cnt);
u8 SD_WriteBlocks_DMA(uint32_t *buf,uint64_t sector,uint32_t blocksize,uint32_t cnt);
#endif
