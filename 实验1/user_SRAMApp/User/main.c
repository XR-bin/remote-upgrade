#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"

int main(void)
{
    /* 修改中断向量表地址 */
    SCB->VTOR = SRAM_BASE | 0x1000;

    SysTick_Init();               /* 延时初始化 */
    USART1_Init(115200);          /* 串口1初始化 115200 */
    LED_Init();                   /* LED初始化 */

    LED0_OFF;
    LED1_OFF;

    delay_ms(100);
    printf("\r\n");
    printf("\r\nSRAM程序更新成功\r\n");;

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


