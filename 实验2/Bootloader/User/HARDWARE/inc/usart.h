#ifndef _USART_H
#define _USART_H

  #include "stm32f10x.h"
	
	//���´��뻺������С��Ϊ10k
	#define USART_REC_LEN  			10*1024 //�����������ֽ��� 10K
	
	extern u16 USART_RX_CNT;
	extern u8  USART_RX_BUF[USART_REC_LEN]; //���ջ���,���USART_REC_LEN���ֽ�.ĩ�ֽ�Ϊ���з� 
  
  void USART1_Init(u32 baud);
	
#endif








