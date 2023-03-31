#include "stm32f10x.h"
#include "usart.h"
#include "delay.h"
#include "key.h"
#include "led.h"
#include "stdio.h"
#include "iap.h"

int main(void)
{
	u8 key=0;
	u16 oldcount=0;				//老的串口接收数据值
	u16 applenth=0;				//接收到的app代码长度
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	USART1_Init(115200);
	SysTick_Init();
	KEY_Init();
	LED_Init();
	LED0_ON;
	LED1_ON;
	printf("进入Bootloader程序\r\n");
	while(1)
	{
		if(USART_RX_CNT)
		{
			if(oldcount==USART_RX_CNT)//新周期内,没有收到任何数据,认为本次数据接收完成.
			{
				applenth=USART_RX_CNT;
				oldcount=0;
				USART_RX_CNT=0;
				printf("用户程序接收完成!\r\n");
				printf("代码长度:%dBytes\r\n",applenth);
			}else oldcount=USART_RX_CNT;
		}
		delay_ms(10);
		
		key = KEY_Scan();
		
		if(key)
		{
			//KEY_UP被按下
			if(key == 3)
			{
				if(applenth)
				{
					printf("开始更新固件...\r\n");	
					if(((*(vu32*)(0X20001000+4))&0xFF000000)==0x08000000)//判断是否为0X08XXXXXX.
					{	 
						iap_write_appbin(FLASH_APP1_ADDR,USART_RX_BUF,applenth);//更新FLASH代码   
						printf("固件更新完成!\r\n");	
					}
				}
				else 
				{
					printf("没有可以更新的固件!\r\n");
				}
			}
			
			//KEY1被按下
			if(key == 2)
			{
				printf("开始执行FLASH用户代码!!\r\n");
				if(((*(vu32*)(FLASH_APP1_ADDR+4))&0xFF000000)==0x08000000)//判断是否为0X08XXXXXX.
				{	 
					iap_load_app(FLASH_APP1_ADDR);//执行FLASH APP代码
				}else 
				{
					printf("非FLASH应用程序,无法执行!\r\n");   
				}
			}
			
			//KEY0被按下
			if(key == 1)
			{
				printf("开始执行SRAM用户代码!!\r\n");
				if(((*(vu32*)(0X20001000+4))&0xFF000000)==0x20000000)//判断是否为0X20XXXXXX.
				{	 
					iap_load_app(0X20001000);//SRAM地址
				}else 
				{
					printf("非SRAM应用程序,无法执行!\r\n");
				}	
			}	
		}
	}
}


