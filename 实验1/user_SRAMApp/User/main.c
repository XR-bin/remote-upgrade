#include "stm32f10x.h"
#include "delay.h"
#include "led.h"
#include "usart.h"
#include "stdio.h"


int main(void)
{
	//修改中断向量表地址
	SCB->VTOR = SRAM_BASE | 0x1000;

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	USART1_Init(115200);
	SysTick_Init();
	LED_Init();
	LED0_OFF;
	LED1_OFF;
	printf("\r\nSRAM程序更新成功\r\n");
	
	while(1)
	{
		LED0_ON;
		LED1_OFF;
		delay_ms(800);
		LED0_OFF;
		LED1_ON;
		delay_ms(800);
	}
}


