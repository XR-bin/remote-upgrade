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
	
//	/*将向量表重定向到当前代码段(boot代码)的向量表*/
	SCB->VTOR = FLASH_BASE | 0x14000; 
	
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
				printf("请按下KEY_UP,将新代码写入User区\r\n");
			}else oldcount=USART_RX_CNT;
		}
		delay_ms(10);
		
		key = KEY_Scan();
		
		if(key)
		{
			//KEY_UP被按下
			//更新user区的代码
			if(key == 3)
			{
				if(applenth)
				{
					printf("开始更新固件...\r\n");	
					if(((*(vu32*)(0X20001000+4))&0xFF000000)==0x08000000)//判断是否为0X08XXXXXX.
					{	 
						iap_write_appbin(FLASH_APP1_ADDR,USART_RX_BUF,applenth);//更新FLASH代码   
						printf("固件更新完成!\r\n");	
						printf("请按下KEY0或KEY1按键退出Bootloader，进入user\r\n");
					}
				}
				else 
				{
					printf("没有可以更新的固件!\r\n");
				}
			}
			
			//KEY1或KEY0被按下
			//退出Bootloader，进入新代码
			if((key == 1) || (key == 2))
			{
				printf("准备退出Bootloader\r\n");
				delay1_ms(10);//给打印留点时间，避免没打印完句子就跳转
				/*升级完成，系统复位*/
				__set_FAULTMASK(1);
				NVIC_SystemReset();
			}
			
		}
	}
}




