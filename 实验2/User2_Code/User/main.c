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

    SysTick_Init();               /* 延时初始化 */
    USART1_Init(115200);          /* 串口1初始化 115200 */
    LED_Init();                   /* LED初始化 */
    KEY_Init();                   /* KEY初始化 */

    LED0_OFF;
    LED1_OFF;
    printf("进入新的用户程序\r\n");
    printf("按下KEY_UP进入Bootloader程序\r\n");

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
            GPIOE->ODR ^= (1<<5);     /* LED1翻转 */
        }

        delay_ms(10);
    }
}


