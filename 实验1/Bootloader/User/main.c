#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "key.h"
#include "iap.h"

int main(void)
{
    uint8_t key=0;
    uint16_t appLenth=0;

    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); /* 2号分组方案 2 位抢占优先级， 2 位响应优先级 */
    SysTick_Init();               /* 延时初始化 */
    USART1_Init(115200);          /* 串口1初始化   115200 */
    LED_Init();                   /* LED初始化 */
    KEY_Init();                   /* KEY初始化 */

    LED0_ON;
    LED1_ON;
    printf("进入Bootloader程序\r\n");

    while(1)
    {
        if(USART_RX_STA)
        {
            appLenth = USART_RX_CNT;
            USART_RX_CNT = 0;
            USART_RX_STA = 0;
            printf("用户程序接收完成!\r\n");
            printf("代码长度:%dBytes\r\n",appLenth);
            printf("按下KEY_UP执行FLASH更新固件\r\n");
            printf("按下KEY1执行FLASH里的新程序\r\n");
            printf("按下KEY2执行SRAM里的新程序\r\n");
        }

        delay_ms(10);

        key = KEY_Scan();

        /* KEY_UP被按下 */
        if(key == 3)
        {
            if(appLenth)
            {
                /* 判断USART_RX_BUF内是否有FLASH程序包 */
                if(((*(volatile uint32_t*)(USART_RX_BUF +4))&0xFF000000)==0x08000000)
                {
                    printf("开始更新固件...\r\n");
                    /* 更新FLASH代码 */
                    IAP_Write_AppBin(FLASH_APP_ADDR, USART_RX_BUF, appLenth);
                    printf("固件更新完成!\r\n");	
                }
            }
            else 
            {
                printf("没有可以更新的固件!\r\n");
            }
        }

        /* KEY1被按下 */
        if(key == 2)
        {
            /* 判断FLASH_APP_ADDR是否有程序包，并且程序包是否是FLASH程序包 */
            if(((*(volatile uint32_t*)(FLASH_APP_ADDR+4))&0xFF000000)==0x08000000)
            {
                printf("开始执行FLASH用户代码!!\r\n");
                IAP_Load_App(FLASH_APP_ADDR);/* 跳转到FLASH地址运行程序 */
            }
            else
            {
                /* 没跳转成功就会执行下面的程序 */
                printf("非FLASH应用程序,无法执行!\r\n");
            }
        }

        /* KEY0被按下 */
        if(key == 1)
        {
            /* 判断SRAM_APP_ADDR是否有程序包，并且程序包是否是SRAM程序包 */
            if(((*(volatile uint32_t*)(SRAM_APP_ADDR+4))&0xFF000000)==0x20000000)
            {
                printf("开始执行SRAM用户代码!!\r\n");
                IAP_Load_App(SRAM_APP_ADDR);/* 跳转到SRAM地址运行程序 */
            }
            else
            {
                printf("非SRAM应用程序,无法执行!\r\n");
            }
        }
    }
}


