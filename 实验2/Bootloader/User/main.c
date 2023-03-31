#include "stm32f10x.h"
#include "usart.h"
#include "delay.h"
#include "key.h"
#include "led.h"
#include "stdio.h"
#include "iap.h"

int main(void)
{
	u8 key=0;
	u16 oldcount=0;				//�ϵĴ��ڽ�������ֵ
	u16 applenth=0;				//���յ���app���볤��
	
//	/*���������ض��򵽵�ǰ�����(boot����)��������*/
	SCB->VTOR = FLASH_BASE | 0x14000; 
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	USART1_Init(115200);
	SysTick_Init();
	KEY_Init();
	LED_Init();
	LED0_ON;
	LED1_ON;
	printf("����Bootloader����\r\n");
	while(1)
	{
		if(USART_RX_CNT)
		{
			if(oldcount==USART_RX_CNT)//��������,û���յ��κ�����,��Ϊ�������ݽ������.
			{
				applenth=USART_RX_CNT;
				oldcount=0;
				USART_RX_CNT=0;
				printf("�û�����������!\r\n");
				printf("���볤��:%dBytes\r\n",applenth);
				printf("�밴��KEY_UP,���´���д��User��\r\n");
			}else oldcount=USART_RX_CNT;
		}
		delay_ms(10);
		
		key = KEY_Scan();
		
		if(key)
		{
			//KEY_UP������
			//����user���Ĵ���
			if(key == 3)
			{
				if(applenth)
				{
					printf("��ʼ���¹̼�...\r\n");	
					if(((*(vu32*)(0X20001000+4))&0xFF000000)==0x08000000)//�ж��Ƿ�Ϊ0X08XXXXXX.
					{	 
						iap_write_appbin(FLASH_APP1_ADDR,USART_RX_BUF,applenth);//����FLASH����   
						printf("�̼��������!\r\n");	
						printf("�밴��KEY0��KEY1�����˳�Bootloader������user\r\n");
					}
				}
				else 
				{
					printf("û�п��Ը��µĹ̼�!\r\n");
				}
			}
			
			//KEY1��KEY0������
			//�˳�Bootloader�������´���
			if((key == 1) || (key == 2))
			{
				printf("׼���˳�Bootloader\r\n");
				delay1_ms(10);//����ӡ����ʱ�䣬����û��ӡ����Ӿ���ת
				/*������ɣ�ϵͳ��λ*/
				__set_FAULTMASK(1);
				NVIC_SystemReset();
			}
			
		}
	}
}




