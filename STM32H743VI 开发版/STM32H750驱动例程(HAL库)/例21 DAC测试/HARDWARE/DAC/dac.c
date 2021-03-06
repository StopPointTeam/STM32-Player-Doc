#include "dac.h"
//////////////////////////////////////////////////////////////////////////////////	 
/**********************************************************************/

//DAC驱动代码	 

//STM32H7工程模板-HAL库函数版本
//DevEBox  大越创新
//淘宝店铺：mcudev.taobao.com
//淘宝店铺：shop389957290.taobao.com	
/*********************************************************************/								  
////////////////////////////////////////////////////////////////////////////////// 	

DAC_HandleTypeDef DAC1_Handler;			//DAC句柄
DAC_ChannelConfTypeDef DACCH1_Config;	//DAC1通道1
	
	

/**********************************************************************/


//初始化DAC

//STM32H7工程模板-HAL库函数版本
//DevEBox  大越创新
//淘宝店铺：mcudev.taobao.com
//淘宝店铺：shop389957290.taobao.com	
/*********************************************************************/	

void DAC1_Init(void)
{
    DAC1_Handler.Instance=DAC1;
    HAL_DAC_Init(&DAC1_Handler);               	//初始化DAC
    
    DACCH1_Config.DAC_Trigger=DAC_TRIGGER_NONE;             //不使用触发功能
    DACCH1_Config.DAC_OutputBuffer=DAC_OUTPUTBUFFER_DISABLE;//DAC1输出缓冲关闭
    HAL_DAC_ConfigChannel(&DAC1_Handler,&DACCH1_Config,DAC_CHANNEL_2);//DAC通道2配置
    
    HAL_DAC_Start(&DAC1_Handler,DAC_CHANNEL_2);  //开启DAC通道1
}


/**********************************************************************/

//DAC底层驱动，时钟配置，引脚 配置
//此函数会被HAL_DAC_Init()调用
//hdac:DAC句柄 

//STM32H7工程模板-HAL库函数版本
//DevEBox  大越创新
//淘宝店铺：mcudev.taobao.com
//淘宝店铺：shop389957290.taobao.com	
/*********************************************************************/	

void HAL_DAC_MspInit(DAC_HandleTypeDef* hdac)
{      
    GPIO_InitTypeDef GPIO_Initure;
	
    __HAL_RCC_DAC12_CLK_ENABLE();           //使能DAC时钟
    __HAL_RCC_GPIOA_CLK_ENABLE();			      //开启GPIOA时钟
	
    GPIO_Initure.Pin=GPIO_PIN_5;            //PA5
    GPIO_Initure.Mode=GPIO_MODE_ANALOG;     //模拟
    GPIO_Initure.Pull=GPIO_NOPULL;          //不带上下拉
    HAL_GPIO_Init(GPIOA,&GPIO_Initure);
}



/**********************************************************************/

//设置通道1输出电压
//vol:0~3300,代表0~3.3V

//STM32H7工程模板-HAL库函数版本
//DevEBox  大越创新
//淘宝店铺：mcudev.taobao.com
//淘宝店铺：shop389957290.taobao.com	
/*********************************************************************/	

void DAC1_Set_Vol(u16 vol)
{
	double temp=vol;
	temp/=1000;
	temp=temp*4096/3.3;
	
	HAL_DAC_SetValue(&DAC1_Handler,DAC_CHANNEL_2,DAC_ALIGN_12B_R,temp);//12位右对齐数据格式设置DAC值
}




































/**********************************************************************/

//DAC驱动代码	 

//STM32H7工程模板-HAL库函数版本
//DevEBox  大越创新
//淘宝店铺：mcudev.taobao.com
//淘宝店铺：shop389957290.taobao.com	
/*********************************************************************/	

