#include "stm32f10x.h"
#include "led.h"

/*****************************************************
*��������  ����LED��Ӧ��GPIO�ڽ��г�ʼ������
*������    ��LED_Init
*��������  ��void
*��������ֵ��void
*����      ��
*            LED0     PB5
*            LED1     PE5
*            �ߵ�ƽ�𣬵͵�ƽ��-----���ģʽ
********************************************************/
void LED_Init(void)
{
 
	GPIO_InitTypeDef  GPIO_InitStructure;               //GPIOx���ýṹ��

	//ʱ��ʹ��   GPIOB   GPIOC 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	 //ʹ��PB�˿�ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);	 //ʹ��PE�˿�ʱ��

	//PB5
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;				     //PB5 �˿�����
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
	GPIO_Init(GPIOB, &GPIO_InitStructure);					     //�����趨������ʼ��PB5
	
	//PE5
	//Ӧ�䲿��������PB5һ�£����Խṹ��һЩ������������
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;	    		     //PE5 �˿�����, �������
	GPIO_Init(GPIOE, &GPIO_InitStructure);	  				     //�����趨������ʼ��PE5
	
	//�˿�������ݼĴ�������   //LED�Ƶĳ�ʼ״̬
	GPIO_SetBits(GPIOB,GPIO_Pin_5);						             //PB5 �����
	GPIO_SetBits(GPIOE,GPIO_Pin_5); 						           //PE5 ����� 
}

/************************************************************
*��������  ���ص�
*������    ��LED_OFF
*��������  ��void
*��������ֵ��void
*����      ��
***************************************************************/
void LED_OFF(void)
{
  LED0_OFF;
  LED1_OFF;
}

/************************************************************
*��������  ���ص�
*������    ��LED_ON
*��������  ��void
*��������ֵ��void
*����      ��
***************************************************************/
void LED_ON(void)
{
  LED0_ON;
  LED1_ON;
}











