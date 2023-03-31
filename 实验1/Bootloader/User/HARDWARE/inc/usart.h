#ifndef _USART_H
#define _USART_H

  #include "stm32f10x.h"
	
	//更新代码缓存区大小设为55k
	#define USART_REC_LEN  			55*1024 //定义最大接收字节数 55K
	
	extern u16 USART_RX_CNT;
	extern u8  USART_RX_BUF[USART_REC_LEN]; //接收缓冲,最大USART_REC_LEN个字节.末字节为换行符 
  
  void USART1_Init(u32 baud);
	
#endif








