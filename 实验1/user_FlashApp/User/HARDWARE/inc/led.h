#ifndef __LED_H
#define __LED_H	 

	#include "stm32f10x.h"

	#define LED0_ON  GPIO_ResetBits(GPIOB,GPIO_Pin_5);    //��LED0
	#define LED1_ON  GPIO_ResetBits(GPIOE,GPIO_Pin_5);    //��LED1
	#define LED0_OFF GPIO_SetBits(GPIOB,GPIO_Pin_5);      //��LED0
	#define LED1_OFF GPIO_SetBits(GPIOE,GPIO_Pin_5);      //��LED1

	void LED_Init(void);       //LED��ʼ��
	void LED_OFF(void);
	void LED_ON(void);

		 				    
#endif


