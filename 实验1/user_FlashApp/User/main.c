#include "stm32f10x.h"
#include "usart.h"
#include "delay.h"
#include "led.h"
#include "stdio.h"

int main(void)
{
	//修改中断向量表地址
	SCB->VTOR = FLASH_BASE | 0x10000;

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	SysTick_Init();
	LED_Init();
	LED0_OFF;
	LED1_OFF;
	printf("Flash程序更新成功\r\n");
	
	while(1)
	{
		LED0_ON;
		LED1_ON;
		delay_ms(800);
		LED0_OFF;
		LED1_OFF;
		delay_ms(800);
	}
}


