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
            printf("����KEY1ִ��FLASH����³���\r\n");
            printf("����KEY2ִ��SRAM����³���\r\n");
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
                    IAP_Write_AppBin(FLASH_APP_ADDR, USART_RX_BUF, appLenth);
                    printf("�̼��������!\r\n");	
                }
            }
            else 
            {
                printf("û�п��Ը��µĹ̼�!\r\n");
            }
        }

        /* KEY1������ */
        if(key == 2)
        {
            /* �ж�FLASH_APP_ADDR�Ƿ��г���������ҳ�����Ƿ���FLASH����� */
            if(((*(volatile uint32_t*)(FLASH_APP_ADDR+4))&0xFF000000)==0x08000000)
            {
                printf("��ʼִ��FLASH�û�����!!\r\n");
                IAP_Load_App(FLASH_APP_ADDR);/* ��ת��FLASH��ַ���г��� */
            }
            else
            {
                /* û��ת�ɹ��ͻ�ִ������ĳ��� */
                printf("��FLASHӦ�ó���,�޷�ִ��!\r\n");
            }
        }

        /* KEY0������ */
        if(key == 1)
        {
            /* �ж�SRAM_APP_ADDR�Ƿ��г���������ҳ�����Ƿ���SRAM����� */
            if(((*(volatile uint32_t*)(SRAM_APP_ADDR+4))&0xFF000000)==0x20000000)
            {
                printf("��ʼִ��SRAM�û�����!!\r\n");
                IAP_Load_App(SRAM_APP_ADDR);/* ��ת��SRAM��ַ���г��� */
            }
            else
            {
                printf("��SRAMӦ�ó���,�޷�ִ��!\r\n");
            }
        }
    }
}


