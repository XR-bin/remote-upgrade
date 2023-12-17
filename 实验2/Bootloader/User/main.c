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

    /*���������ض��򵽵�ǰ�����(boot����)��������*/
    SCB->VTOR = FLASH_BASE | 0x10000;

    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); /* 2�ŷ��鷽�� 2 λ��ռ���ȼ��� 2 λ��Ӧ���ȼ� */
    SysTick_Init();               /* ��ʱ��ʼ�� */
    USART1_Init(115200);          /* ����1��ʼ��   115200 */
    LED_Init();                   /* LED��ʼ�� */
    KEY_Init();                   /* KEY��ʼ�� */

    LED0_ON;
    LED1_ON;
    printf("����Bootloader����\r\n");

    while(1)
    {
        if(USART_RX_STA)
        {
            appLenth = USART_RX_CNT;
            USART_RX_CNT = 0;
            USART_RX_STA = 0;
            printf("�û�����������!\r\n");
            printf("���볤��:%dBytes\r\n",appLenth);
            printf("����KEY_UPִ��FLASH���¹̼�\r\n");
            printf("����KEY1��KEY1ִ��FLASH����³���\r\n");
        }

        delay_ms(10);

        key = KEY_Scan();

        /* KEY_UP������ */
        if(key == 3)
        {
            if(appLenth)
            {
                /* �ж�USART_RX_BUF���Ƿ���FLASH����� */
                if(((*(volatile uint32_t*)(USART_RX_BUF +4))&0xFF000000)==0x08000000)
                {
                    printf("��ʼ���¹̼�...\r\n");
                    /* ����FLASH���� */
                    IAP_Write_AppBin(USER_CODE_ADDR, USART_RX_BUF, appLenth);
                    printf("�̼��������!\r\n");	
                }
            }
            else 
            {
                printf("û�п��Ը��µĹ̼�!\r\n");
            }
        }

        /* KEY1��KEY0������ */
        /* �˳�Bootloader�������´��� */
        if((key == 1) || (key == 2))
        {
            printf("׼���˳�Bootloader......\r\n");
            delay1_ms(100);           /* ����ӡ����ʱ�䣬����û��ӡ����Ӿ���ת */
            /* ������ɣ�ϵͳ��λ */
            __set_FAULTMASK(1);
            NVIC_SystemReset();
        }
    }
}


