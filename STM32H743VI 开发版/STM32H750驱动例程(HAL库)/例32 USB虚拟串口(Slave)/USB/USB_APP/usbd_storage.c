/**
  ******************************************************************************
  * @file    USB_Device/MSC_Standalone/Src/usbd_storage.c
  * @author  MCD Application Team
  * @version V1.2.0
  * @date    29-December-2017
  * @brief   Memory management layer
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2017 STMicroelectronics International N.V.
  * All rights reserved.</center></h2>
  *
  * Redistribution and use in source and binary forms, with or without
  * modification, are permitted, provided that the following conditions are met:
  *
  * 1. Redistribution of source code must retain the above copyright notice,
  *    this list of conditions and the following disclaimer.
  * 2. Redistributions in binary form must reproduce the above copyright notice,
  *    this list of conditions and the following disclaimer in the documentation
  *    and/or other materials provided with the distribution.
  * 3. Neither the name of STMicroelectronics nor the names of other
  *    contributors to this software may be used to endorse or promote products
  *    derived from this software without specific written permission.
  * 4. This software, including modifications and/or derivative works of this
  *    software, must execute solely and exclusively on microcontroller or
  *    microprocessor devices manufactured by or for STMicroelectronics.
  * 5. Redistribution and use of this software other than as permitted under
  *    this license is void and will automatically terminate your rights under
  *    this license.
  *
  * THIS SOFTWARE IS PROVIDED BY STMICROELECTRONICS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS, IMPLIED OR STATUTORY WARRANTIES, INCLUDING, BUT NOT
  * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
  * PARTICULAR PURPOSE AND NON-INFRINGEMENT OF THIRD PARTY INTELLECTUAL PROPERTY
  * RIGHTS ARE DISCLAIMED TO THE FULLEST EXTENT PERMITTED BY LAW. IN NO EVENT
  * SHALL STMICROELECTRONICS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
  * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
  * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
  * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
  * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
  * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
  * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------ */
#include "usbd_storage.h"
#include "sdmmc_sdcard.h"
#include "w25qxx.h"
#include "nand.h"    
#include "ftl.h"  

/* Private typedef ----------------------------------------------------------- */
/* Private define ------------------------------------------------------------ */
#define STORAGE_LUN_NBR                  2
#define STORAGE_BLK_NBR                  0x10000
#define STORAGE_BLK_SIZ                  0x200

////////////////////////////自己定义的一个标记USB状态的寄存器///////////////////
//bit0:表示电脑正在向SD卡写入数据
//bit1:表示电脑正从SD卡读出数据
//bit2:SD卡写数据错误标志位
//bit3:SD卡读数据错误标志位
//bit4:1,表示电脑有轮询操作(表明连接还保持着)
vu8 USB_STATUS_REG=0;
////////////////////////////////////////////////////////////////////////////////

/* Private macro ------------------------------------------------------------- */
/* Private variables --------------------------------------------------------- */
/* USB Mass storage Standard Inquiry Data */
int8_t STORAGE_Inquirydata[] = {  /* 36 */
    	/* LUN 0 */ 
	0x00,		
	0x80,		
	0x02,		
	0x02,
	(STANDARD_INQUIRY_DATA_LEN - 5),
	0x00,
	0x00,	
	0x00,
    /* Vendor Identification */
    'A', 'L', 'I', 'E', 'N', 'T', 'E', 'K', ' ',//9字节
    /* Product Identification */
    'S', 'P', 'I', ' ', 'F', 'l', 'a', 's', 'h',//15字节
    ' ','D', 'i', 's', 'k', ' ',
    /* Product Revision Level */	
    '1', '.', '0', ' ',							//4字节		
	
//	/* LUN 1 */
//	0x00,
//	0x80,		
//	0x02,		
//	0x02,
//	(STANDARD_INQUIRY_DATA_LEN - 5),
//	0x00,
//	0x00,	
//	0x00,
//	/* Vendor Identification */
//	'A', 'L', 'I', 'E', 'N', 'T', 'E', 'K',' ',	//9字节
//	/* Product Identification */				
//    'N', 'A', 'N', 'D', ' ', 'F', 'l', 'a', 's', 'h',//15字节
//	' ','D', 'i', 's', 'k', 
//    /* Product Revision Level */
//	'1', '.', '0' ,' ',                      	//4字节
	
	/* LUN 2 */
	0x00,
	0x80,		
	0x02,		
	0x02,
	(STANDARD_INQUIRY_DATA_LEN - 5),
	0x00,
	0x00,	
	0x00,
	/* Vendor Identification */
	'A', 'L', 'I', 'E', 'N', 'T', 'E', 'K',' ',	//9字节
	/* Product Identification */				
	'S', 'D', ' ', 'F', 'l', 'a', 's', 'h', ' ',//15字节
	'D', 'i', 's', 'k', ' ', ' ',  
    /* Product Revision Level */
	'1', '.', '0' ,' ',                      	//4字节
};

/* Private function prototypes ----------------------------------------------- */
int8_t STORAGE_Init(uint8_t lun);
int8_t STORAGE_GetCapacity(uint8_t lun, uint32_t * block_num,
                           uint16_t * block_size);
int8_t STORAGE_IsReady(uint8_t lun);
int8_t STORAGE_IsWriteProtected(uint8_t lun);
int8_t STORAGE_Read(uint8_t lun, uint8_t * buf, uint32_t blk_addr,
                    uint16_t blk_len);
int8_t STORAGE_Write(uint8_t lun, uint8_t * buf, uint32_t blk_addr,
                     uint16_t blk_len);
int8_t STORAGE_GetMaxLun(void);

USBD_StorageTypeDef USBD_DISK_fops = {
  STORAGE_Init,
  STORAGE_GetCapacity,
  STORAGE_IsReady,
  STORAGE_IsWriteProtected,
  STORAGE_Read,
  STORAGE_Write,
  STORAGE_GetMaxLun,
  STORAGE_Inquirydata,
};

/* Private functions --------------------------------------------------------- */

/**
  * @brief  Initializes the storage unit (medium)       
  * @param  lun: Logical unit number
  * @retval Status (0 : OK / -1 : Error)
  */
int8_t STORAGE_Init(uint8_t lun)
{
	u8 res=0;
	switch(lun)
	{
		case 0://SPI FLASH
			W25QXX_Init();
			break;
//		case 1://NAND FLASH
//			res=FTL_Init();
//			break;
		case 1://SD卡
			res=SD_Init();
			break; 
	} 
	return res; 
}

/**
  * @brief  Returns the medium capacity.      
  * @param  lun: Logical unit number
  * @param  block_num: Number of total block number
  * @param  block_size: Block size
  * @retval Status (0: OK / -1: Error)
  */
int8_t STORAGE_GetCapacity(uint8_t lun, uint32_t * block_num,
                           uint16_t * block_size)
{
    HAL_SD_CardInfoTypeDef info;
    int8_t ret = -1;

    switch(lun)
	{
		case 0://SPI FLASH
			*block_size=512;  
			*block_num=1024*1024*25/512;	//SPI FLASH的前面25M字节,文件系统用
			break;
//		case 1://NAND FLASH
//			*block_size=512;  
//			*block_num=nand_dev.valid_blocknum*nand_dev.block_pagenum*nand_dev.page_mainsize/512;
//  			break;
		case 1://SD卡
            HAL_SD_GetCardInfo(&SDCARD_Handler,&info);
            *block_num = info.LogBlockNbr - 1;
            *block_size = info.LogBlockSize;
			break; 
	}  	
	return 0; 
}

/**
  * @brief  Checks whether the medium is ready.  
  * @param  lun: Logical unit number
  * @retval Status (0: OK / -1: Error)
  */
int8_t STORAGE_IsReady(uint8_t lun)
{

    int8_t ret = 0;   
    USB_STATUS_REG|=0X10;//标记轮询
    return ret;
}

/**
  * @brief  Checks whether the medium is write protected.
  * @param  lun: Logical unit number
  * @retval Status (0: write enabled / -1: otherwise)
  */
int8_t STORAGE_IsWriteProtected(uint8_t lun)
{
    return 0;
}

/**
  * @brief  Reads data from the medium.
  * @param  lun: Logical unit number
  * @param  blk_addr: Logical block address
  * @param  blk_len: Blocks number
  * @retval Status (0: OK / -1: Error)
  */
int8_t STORAGE_Read(uint8_t lun, uint8_t * buf, uint32_t blk_addr,
                    uint16_t blk_len)
{
    int8_t res=0;
	USB_STATUS_REG|=0X02;//标记正在读数据
	switch(lun)
	{
		case 0://SPI FLASH
			W25QXX_Read(buf,blk_addr*512,blk_len*512);
			break;
//		case 1://NAND FLASH
//			res=FTL_ReadSectors(buf,blk_addr,512,blk_len);
//			break;
		case 1://SD卡
			res=SD_ReadDisk(buf,blk_addr,blk_len);
			break; 
	} 
	if(res)
	{
		USB_STATUS_REG|=0X08;//读错误! 
	} 
	return res;
}

/**
  * @brief  Writes data into the medium.
  * @param  lun: Logical unit number
  * @param  blk_addr: Logical block address
  * @param  blk_len: Blocks number
  * @retval Status (0 : OK / -1 : Error)
  */
int8_t STORAGE_Write(uint8_t lun, uint8_t * buf, uint32_t blk_addr,
                     uint16_t blk_len)
{
    int8_t res=0;
	USB_STATUS_REG|=0X01;//标记正在写数据
	switch(lun)
	{
		case 0://SPI FLASH
			W25QXX_Write(buf,blk_addr*512,blk_len*512);
			break;
//		case 1://NAND FLASH
//			res=FTL_WriteSectors(buf,blk_addr,512,blk_len);
//			break;
		case 1://SD卡
			res=SD_WriteDisk(buf,blk_addr,blk_len);
			break; 
	}  
	if(res)
	{
		USB_STATUS_REG|=0X04;//写错误!	 
	}
	return res;
}

/**
  * @brief  Returns the Max Supported LUNs.   
  * @param  None
  * @retval Lun(s) number
  */
int8_t STORAGE_GetMaxLun(void)
{
    HAL_SD_CardInfoTypeDef info;
    HAL_SD_GetCardInfo(&SDCARD_Handler,&info);
    
    if(info.LogBlockNbr)return STORAGE_LUN_NBR-1;
	else return STORAGE_LUN_NBR-2;

}


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
