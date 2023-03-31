#include "stm32f10x.h"
#include "delay.h"
#include "key.h"

/*****************************************************
*��������  ����KEY��Ӧ��GPIO�ڽ��г�ʼ������
*������    ��KEY_Init
*��������  ��void
*��������ֵ��void
*����      ��
*            KEY0     PE4
*            KEY1     PE3
*            KEY_UP   PA0
*            KEY0��KEY1 �͵�ƽ���£��ߵ�ƽ̧��
*            KEY_UP     �ߵ�ƽ���£��͵�ƽ̧��
*                                 -------------���ģʽ
********************************************************/
void KEY_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;         //GPIOx���ýṹ��
	
	/*GPIOx����*/
  //GPIOxʱ��ʹ��  GPIOA��GPIOE
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);
  //GPIOx����
  //PE
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3|GPIO_Pin_4;	    //PE3/4�˿�����
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU ; 		        //��������
  GPIO_Init(GPIOE, &GPIO_InitStructure);					          //�����趨������ʼ��GPIE PE3/4  
  //PA
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;	                //PA0�˿�����
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD ; 		        //��������
  GPIO_Init(GPIOA, &GPIO_InitStructure);					          //�����趨������ʼ��GPIOA PA0
}

/*****************************************************
*��������  ������ɨ�躯��
*������    ��KEY_Scan
*��������  ��void
*��������ֵ��u8
*����      ��
             KEY0     PE4
             KEY1     PE3
             KEY_UP   PA0
             KEY0��KEY1 �͵�ƽ���£��ߵ�ƽ̧��
             KEY_UP     �ߵ�ƽ���£��͵�ƽ̧��
                                  -------------���ģʽ
********************************************************/
u8 KEY_Scan(void)
{
  u8 temp = 0;
  static u8 key_flay = 1;
  if(key_flay && (KEY_UP||!(KEY1)||!(KEY0)))
  {
    delay_ms(10);
    if(KEY_UP||!(KEY1)||!(KEY0))
    {
      key_flay = 0;
      if(!(KEY0))        temp = 1;
      else if(!(KEY1))   temp = 2;
      else if(KEY_UP)    temp = 3;
    }
  }
  if(!(KEY_UP) && (KEY1) && (GPIOE->IDR & (1<<4)))
  {
    key_flay = 1;
  }
  return temp;
}











