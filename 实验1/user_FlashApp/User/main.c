#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"

int main(void)
{
    /* �޸��ж��������ַ */
    SCB->VTOR = FLASH_BASE | 0x10000;

    SysTick_Init();               /* ��ʱ��ʼ�� */
    USART1_Init(115200);          /* ����1��ʼ�� 115200 */
    LED_Init();                   /* LED��ʼ�� */

    LED0_OFF;
    LED1_OFF;
    delay_ms(100);

    printf("\r\n");
    printf("Flash������³ɹ�\r\n");

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


