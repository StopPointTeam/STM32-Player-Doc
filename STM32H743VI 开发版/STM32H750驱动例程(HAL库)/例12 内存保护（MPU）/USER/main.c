#include "sys.h" 
#include "usart.h" 
#include "delay.h" 
#include "led.h"
#include "key.h"
#include "mpu.h" 


/***************************************************************************************************/
//内存保护（MPU）实验  


//STM32H7工程模板-HAL库函数版本
//DevEBox  大越创新
//淘宝店铺：mcudev.taobao.com
//淘宝店铺：shop389957290.taobao.com	

/***************************************************************************************************/

u8 mpudata[128] __attribute__((at(0X20002000)));								//定义一个数组

int main(void)
{
	u8 i=0;
	u8 key; 
	Cache_Enable();															//打开L1-Cache
	HAL_Init();																	//初始化HAL库
	Stm32_Clock_Init(160,5,2,4);								//设置时钟,400Mhz
	delay_init(400);														//延时初始化
	uart_init(115200);													//串口初始化
	LED_Init();																	//初始化LED时钟  
	KEY_Init();
	printf("\r\n\r\nMPU closed!\r\n");					//提示MPU关闭
	while(1)  
	{
		key=KEY_Scan(0);
		
     if(key==KEY1_PRES)														//使能MPU保护数组 mpudata;
        {
            MPU_Set_Protection(0X20002000,128,1,MPU_REGION_PRIV_RO_URO,0,0,1);	//只读,禁止共用,禁止catch,允许缓冲 
            printf("MPU open!\r\n");											//提示MPU打开
        }
		 else if(key==KEY2_PRES)												//向数组中写入数据，如果开启了MPU保护的话会进入内存访问错误！
        {
					printf("Start Writing data...\r\n");
					sprintf((char*)mpudata,"MPU test array %d",i);
					printf("Data Write finshed!\r\n");
					printf("Array data is:%s\r\n",mpudata);  //从数组中读取数据，不管有没有开启MPU保护都不会进入内存访问错误！
        }
		 else delay_ms(10);
		
				i++;
		if((i%50)==0) LED2_Toggle;												//LED2取反 
	}
}


































/***************************************************************************************************/

//STM32H7工程模板-HAL库函数版本
//DevEBox  大越创新
//淘宝店铺：mcudev.taobao.com
//淘宝店铺：shop389957290.taobao.com	

/***************************************************************************************************/



