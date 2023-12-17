#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "key.h"
#include "update.h"

int main(void)
{
    uint8_t key=0;
    uint8_t i=0;

    SysTick_Init();               /* ��ʱ��ʼ�� */
    USART1_Init(115200);          /* ����1��ʼ�� 115200 */
    LED_Init();                   /* LED��ʼ�� */
    KEY_Init();                   /* KEY��ʼ�� */

    LED0_OFF;
    LED1_OFF;
    printf("�����µ��û�����\r\n");
    printf("����KEY_UP����Bootloader����\r\n");

    while(1)
    {
        key = KEY_Scan();

        if(key == 3)
        {
            Updata_Code();
        }
    
        i++;
        if(i==80)
        {
            i=0;
            GPIOE->ODR ^= (1<<5);     /* LED1��ת */
        }

        delay_ms(10);
    }
}


