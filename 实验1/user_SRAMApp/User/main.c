#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"

int main(void)
{
    /* �޸��ж��������ַ */
    SCB->VTOR = SRAM_BASE | 0x1000;

    SysTick_Init();               /* ��ʱ��ʼ�� */
    USART1_Init(115200);          /* ����1��ʼ�� 115200 */
    LED_Init();                   /* LED��ʼ�� */

    LED0_OFF;
    LED1_OFF;

    delay_ms(100);
    printf("\r\n");
    printf("\r\nSRAM������³ɹ�\r\n");;

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


