#include "qspi.h"
#include "delay.h"
//////////////////////////////////////////////////////////////////////////////////	 
/**********************************************************************/

//QSPI��������	

//STM32H7����ģ��-HAL�⺯���汾
//DevEBox  ��Խ����
//�Ա����̣�mcudev.taobao.com
//�Ա����̣�shop389957290.taobao.com	
  
/**********************************************************************/								  
////////////////////////////////////////////////////////////////////////////////// 	

QSPI_HandleTypeDef QSPI_Handler;    //QSPI���




/**********************************************************************/

//�ȴ�״̬��־
//flag:��Ҫ�ȴ��ı�־λ
//sta:��Ҫ�ȴ���״̬
//wtime:�ȴ�ʱ��
//����ֵ:0,�ȴ��ɹ�.
//	     1,�ȴ�ʧ��.

//STM32H7����ģ��-HAL�⺯���汾
//DevEBox  ��Խ����
//�Ա����̣�mcudev.taobao.com
//�Ա����̣�shop389957290.taobao.com	
  
/**********************************************************************/	


u8 QSPI_Wait_Flag(u32 flag,u8 sta,u32 wtime)
{
	u8 flagsta=0;
	while(wtime)
	{
		flagsta=(QUADSPI->SR&flag)?1:0; 
		if(flagsta==sta)break;
		wtime--;
	}
	if(wtime)return 0;
	else return 1;
}


/**********************************************************************/

//QSPI��ʼ��	

//STM32H7����ģ��-HAL�⺯���汾
//DevEBox  ��Խ����
//�Ա����̣�mcudev.taobao.com
//�Ա����̣�shop389957290.taobao.com	
  
/**********************************************************************/	


u8 QSPI_Init(void)
{
    QSPI_Handler.Instance=QUADSPI;                          //QSPI
    QSPI_Handler.Init.ClockPrescaler=1;                     //QPSI��Ƶ�ȣ�W25Q256���Ƶ��Ϊ104M��
                                                            //���Դ˴�Ӧ��Ϊ2��QSPIƵ�ʾ�Ϊ200/(1+1)=100MHZ
    QSPI_Handler.Init.FifoThreshold=4;                      //FIFO��ֵΪ4���ֽ�
    QSPI_Handler.Init.SampleShifting=QSPI_SAMPLE_SHIFTING_HALFCYCLE;//������λ�������(DDRģʽ��,��������Ϊ0)
    QSPI_Handler.Init.FlashSize=POSITION_VAL(0X800000)-1;  //SPI FLASH��С��W25Q64��СΪ8M�ֽ�
    QSPI_Handler.Init.ChipSelectHighTime=QSPI_CS_HIGH_TIME_5_CYCLE;//Ƭѡ�ߵ�ƽʱ��Ϊ5��ʱ��(10*5=55ns),���ֲ������tSHSL����
    QSPI_Handler.Init.ClockMode=QSPI_CLOCK_MODE_0;          //ģʽ0
    QSPI_Handler.Init.FlashID=QSPI_FLASH_ID_1;              //��һƬflash
    QSPI_Handler.Init.DualFlash=QSPI_DUALFLASH_DISABLE;     //��ֹ˫����ģʽ
    if(HAL_QSPI_Init(&QSPI_Handler)==HAL_OK) return 0;      //QSPI��ʼ���ɹ�
    else return 1;
}




/**********************************************************************/

//QSPI�ײ�����,�������ã�ʱ��ʹ��
//�˺����ᱻHAL_QSPI_Init()����
//hqspi:QSPI���


//PB2,AF9     PB2-- QUADSPI_CLK
//PB6,AF10    PB6-- QSPI_BK1_NCS
	
//PD11,AF9  PD11-- QUADSPI_BK1_IO0
//PD12,AF9  PD12-- QUADSPI_BK1_IO1
//PD13,AF9  PD13-- QUADSPI_BK1_IO3

//PE2,AF9   PE2-- QUADSPI_BK1_IO2

//STM32H7����ģ��-HAL�⺯���汾
//DevEBox  ��Խ����
//�Ա����̣�mcudev.taobao.com
//�Ա����̣�shop389957290.taobao.com	
  
/**********************************************************************/	



void HAL_QSPI_MspInit(QSPI_HandleTypeDef *hqspi)
{
    GPIO_InitTypeDef GPIO_Initure;
    
    __HAL_RCC_QSPI_CLK_ENABLE();        //ʹ��QSPIʱ��
    __HAL_RCC_GPIOB_CLK_ENABLE();       //ʹ��GPIOBʱ��
	  __HAL_RCC_GPIOD_CLK_ENABLE();       //ʹ��GPIODʱ��
    __HAL_RCC_GPIOE_CLK_ENABLE();       //ʹ��GPIOEʱ��
    
    //��ʼ��PB6 Ƭѡ�ź�
    GPIO_Initure.Pin=GPIO_PIN_6;
    GPIO_Initure.Mode=GPIO_MODE_AF_PP;             //����
    GPIO_Initure.Pull=GPIO_PULLUP;              
    GPIO_Initure.Speed=GPIO_SPEED_FREQ_VERY_HIGH;  //����
    GPIO_Initure.Alternate=GPIO_AF10_QUADSPI;      //����ΪQSPI
    HAL_GPIO_Init(GPIOB,&GPIO_Initure);
	
	    //��ʼ��PB2 ʱ���ź�
    GPIO_Initure.Pin=GPIO_PIN_2;
    GPIO_Initure.Mode=GPIO_MODE_AF_PP;             //����
    GPIO_Initure.Pull=GPIO_NOPULL;              
    GPIO_Initure.Speed=GPIO_SPEED_FREQ_VERY_HIGH;  //����
    GPIO_Initure.Alternate=GPIO_AF9_QUADSPI;      //����ΪQSPI
    HAL_GPIO_Init(GPIOB,&GPIO_Initure);
		
    
    //PD11-- QUADSPI_BK1_IO0   PD12-- QUADSPI_BK1_IO1  PD13-- QUADSPI_BK1_IO3
    GPIO_Initure.Pin=GPIO_PIN_11|GPIO_PIN_12|GPIO_PIN_13;
    GPIO_Initure.Mode=GPIO_MODE_AF_PP;             //����
    GPIO_Initure.Pull=GPIO_NOPULL;              
    GPIO_Initure.Speed=GPIO_SPEED_FREQ_VERY_HIGH;  //����
    GPIO_Initure.Alternate=GPIO_AF9_QUADSPI;      //����ΪQSPI
    HAL_GPIO_Init(GPIOD,&GPIO_Initure);
    
    //PE2-- QUADSPI_BK1_IO2
    GPIO_Initure.Pin=GPIO_PIN_2;
    GPIO_Initure.Mode=GPIO_MODE_AF_PP;             //����
    GPIO_Initure.Pull=GPIO_NOPULL;              
    GPIO_Initure.Speed=GPIO_SPEED_FREQ_VERY_HIGH;  //����
    GPIO_Initure.Alternate=GPIO_AF9_QUADSPI;      //����ΪQSPI
    HAL_GPIO_Init(GPIOE,&GPIO_Initure);
		
}




/**********************************************************************/

//QSPI��������
//cmd:Ҫ���͵�ָ��
//addr:���͵���Ŀ�ĵ�ַ
//mode:ģʽ,��ϸλ��������:
//	mode[1:0]:ָ��ģʽ;00,��ָ��;01,���ߴ���ָ��;10,˫�ߴ���ָ��;11,���ߴ���ָ��.
//	mode[3:2]:��ַģʽ;00,�޵�ַ;01,���ߴ����ַ;10,˫�ߴ����ַ;11,���ߴ����ַ.
//	mode[5:4]:��ַ����;00,8λ��ַ;01,16λ��ַ;10,24λ��ַ;11,32λ��ַ.
//	mode[7:6]:����ģʽ;00,������;01,���ߴ�������;10,˫�ߴ�������;11,���ߴ�������.
//dmcycle:��ָ��������

//STM32H7����ģ��-HAL�⺯���汾
//DevEBox  ��Խ����
//�Ա����̣�mcudev.taobao.com
//�Ա����̣�shop389957290.taobao.com	
  
/**********************************************************************/	



void QSPI_Send_CMD(u8 cmd,u32 addr,u8 mode,u8 dmcycle)
{
	QSPI_CommandTypeDef Cmdhandler;
    
	Cmdhandler.Instruction=cmd;									//ָ��
	Cmdhandler.Address=addr;									//��ַ
	Cmdhandler.DummyCycles=dmcycle;								//���ÿ�ָ��������
	
	if(((mode>>0)&0x03) == 0)
	Cmdhandler.InstructionMode=QSPI_INSTRUCTION_NONE;			//ָ��ģʽ
	else if(((mode>>0)&0x03) == 1)
	Cmdhandler.InstructionMode=QSPI_INSTRUCTION_1_LINE;			//ָ��ģʽ
	else if(((mode>>0)&0x03) == 2)
	Cmdhandler.InstructionMode=QSPI_INSTRUCTION_2_LINES;			//ָ��ģʽ
	else if(((mode>>0)&0x03) == 3)
	Cmdhandler.InstructionMode=QSPI_INSTRUCTION_4_LINES;			//ָ��ģʽ
	
	if(((mode>>2)&0x03) == 0)
	Cmdhandler.AddressMode=QSPI_ADDRESS_NONE;   					//��ַģʽ
	else if(((mode>>2)&0x03) == 1)
	Cmdhandler.AddressMode=QSPI_ADDRESS_1_LINE;   					//��ַģʽ
	else if(((mode>>2)&0x03) == 2)
	Cmdhandler.AddressMode=QSPI_ADDRESS_2_LINES;   					//��ַģʽ
	else if(((mode>>2)&0x03) == 3)
	Cmdhandler.AddressMode=QSPI_ADDRESS_4_LINES;   					//��ַģʽ
	
	if(((mode>>4)&0x03) == 0)
	Cmdhandler.AddressSize=QSPI_ADDRESS_8_BITS;   					//��ַ����
	else if(((mode>>4)&0x03) == 1)
	Cmdhandler.AddressSize=QSPI_ADDRESS_16_BITS;   					//��ַ����
	else if(((mode>>4)&0x03) == 2)
	Cmdhandler.AddressSize=QSPI_ADDRESS_24_BITS;   					//��ַ����
	else if(((mode>>4)&0x03) == 3)
	Cmdhandler.AddressSize=QSPI_ADDRESS_32_BITS;   					//��ַ����
	
	if(((mode>>6)&0x03) == 0)
	Cmdhandler.DataMode=QSPI_DATA_NONE;             			//����ģʽ
	else if(((mode>>6)&0x03) == 1)
	Cmdhandler.DataMode=QSPI_DATA_1_LINE;             			//����ģʽ
	else if(((mode>>6)&0x03) == 2)
	Cmdhandler.DataMode=QSPI_DATA_2_LINES;             			//����ģʽ
	else if(((mode>>6)&0x03) == 3)
	Cmdhandler.DataMode=QSPI_DATA_4_LINES;             			//����ģʽ
	
	Cmdhandler.SIOOMode=QSPI_SIOO_INST_EVERY_CMD;				//ÿ�ζ�����ָ��
	Cmdhandler.AlternateByteMode=QSPI_ALTERNATE_BYTES_NONE;		//�޽����ֽ�
	Cmdhandler.DdrMode=QSPI_DDR_MODE_DISABLE;					//�ر�DDRģʽ
	Cmdhandler.DdrHoldHalfCycle=QSPI_DDR_HHC_ANALOG_DELAY;

	HAL_QSPI_Command(&QSPI_Handler,&Cmdhandler,5000);
}




/**********************************************************************/

//QSPI����ָ�����ȵ�����
//buf:�������ݻ������׵�ַ
//datalen:Ҫ��������ݳ���
//����ֵ:0,����
//    ����,�������

//STM32H7����ģ��-HAL�⺯���汾
//DevEBox  ��Խ����
//�Ա����̣�mcudev.taobao.com
//�Ա����̣�shop389957290.taobao.com	
  
/**********************************************************************/	


u8 QSPI_Receive(u8* buf,u32 datalen)
{
    QSPI_Handler.Instance->DLR=datalen-1;                           //�������ݳ���
    if(HAL_QSPI_Receive(&QSPI_Handler,buf,5000)==HAL_OK) return 0;  //��������
    else return 1;
}



/**********************************************************************/

//QSPI����ָ�����ȵ�����
//buf:�������ݻ������׵�ַ
//datalen:Ҫ��������ݳ���
//����ֵ:0,����
//    ����,�������

//STM32H7����ģ��-HAL�⺯���汾
//DevEBox  ��Խ����
//�Ա����̣�mcudev.taobao.com
//�Ա����̣�shop389957290.taobao.com	
  
/**********************************************************************/	


u8 QSPI_Transmit(u8* buf,u32 datalen)
{
    QSPI_Handler.Instance->DLR=datalen-1;                            //�������ݳ���
    if(HAL_QSPI_Transmit(&QSPI_Handler,buf,5000)==HAL_OK) return 0;  //��������
    else return 1;
}


































/**********************************************************************/

//QSPI��������	

//STM32H7����ģ��-HAL�⺯���汾
//DevEBox  ��Խ����
//�Ա����̣�mcudev.taobao.com
//�Ա����̣�shop389957290.taobao.com	
  
/**********************************************************************/	

