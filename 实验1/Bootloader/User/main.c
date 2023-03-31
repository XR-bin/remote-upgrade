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
			}else oldcount=USART_RX_CNT;
		}
		delay_ms(10);
		
		key = KEY_Scan();
		
		if(key)
		{
			//KEY_UP������
			if(key == 3)
			{
				if(applenth)
				{
					printf("��ʼ���¹̼�...\r\n");	
					if(((*(vu32*)(0X20001000+4))&0xFF000000)==0x08000000)//�ж��Ƿ�Ϊ0X08XXXXXX.
					{	 
						iap_write_appbin(FLASH_APP1_ADDR,USART_RX_BUF,applenth);//����FLASH����   
						printf("�̼��������!\r\n");	
					}
				}
				else 
				{
					printf("û�п��Ը��µĹ̼�!\r\n");
				}
			}
			
			//KEY1������
			if(key == 2)
			{
				printf("��ʼִ��FLASH�û�����!!\r\n");
				if(((*(vu32*)(FLASH_APP1_ADDR+4))&0xFF000000)==0x08000000)//�ж��Ƿ�Ϊ0X08XXXXXX.
				{	 
					iap_load_app(FLASH_APP1_ADDR);//ִ��FLASH APP����
				}else 
				{
					printf("��FLASHӦ�ó���,�޷�ִ��!\r\n");   
				}
			}
			
			//KEY0������
			if(key == 1)
			{
				printf("��ʼִ��SRAM�û�����!!\r\n");
				if(((*(vu32*)(0X20001000+4))&0xFF000000)==0x20000000)//�ж��Ƿ�Ϊ0X20XXXXXX.
				{	 
					iap_load_app(0X20001000);//SRAM��ַ
				}else 
				{
					printf("��SRAMӦ�ó���,�޷�ִ��!\r\n");
				}	
			}	
		}
	}
}


