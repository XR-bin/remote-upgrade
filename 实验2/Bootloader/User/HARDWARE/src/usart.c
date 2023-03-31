#include "stm32f10x.h"
#include "usart.h"
#include "stdio.h"

/*****************************************************
*函数功能  ：对USART1对应的GPIO口进行初始化设置
*函数名    ：USART1_Init
*函数参数  ：u32 baud
*函数返回值：void
*描述      ：
*           PA9     TX     ---------输出
*           PA10    RX     ---------输入
********************************************************/
void USART1_Init(u32 baud)
{
  GPIO_InitTypeDef  GPIO_InitStruct;     //GPIOx配置结构体
  USART_InitTypeDef USART_InitStruct;    //USARTx配置结构体
	NVIC_InitTypeDef   NVIC_InitStruct;    //NVIC(中断)配置结构体
  
  //时钟使能   GPIOA   USART1
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_USART1,ENABLE); 
  
  /*GPIOx初始化设置*/
  //GPIOx端口配置
  //PA9   USART1_TX ----- 复用串口输出
  GPIO_InitStruct.GPIO_Pin   = GPIO_Pin_9;				     //PA9 端口配置
  GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_AF_PP; 	  	 //复用推挽输
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;		   //IO口速度为50MHz
  GPIO_Init(GPIOA, &GPIO_InitStruct);                  //根据设定参数初始化PA9
  //PA10  USART1_RX ----- 复用串口输入
  GPIO_InitStruct.GPIO_Pin   = GPIO_Pin_10;				     //PA10 端口配置
  GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_IN_FLOATING;  //浮空输入
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;		   //IO口速度为50MHz
  GPIO_Init(GPIOA, &GPIO_InitStruct);                  //根据设定参数初始化PA10
  
  /*USART 初始化设置*/
  //USART1配置
  USART_InitStruct.USART_BaudRate      = baud;                 //波特率设置(USART->BRR寄存器)
  USART_InitStruct.USART_WordLength    = USART_WordLength_8b;  //字长为8位数据格式:一个起始位， 8个数据位， n个停止位；(USART->CR1寄存器的第12位)
  USART_InitStruct.USART_StopBits      = USART_StopBits_1;     //一个停止位(USART->CR2寄存器的第12、13位)
  USART_InitStruct.USART_Parity        = USART_Parity_No;      //无奇偶校验(USART->CR1寄存器的第10位)
  USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制(USART->CR3寄存器的第9位)
  USART_InitStruct.USART_Mode = USART_Mode_Rx | USART_Mode_Tx; //收发模式(USART->CR1寄存器的第2、3位)
  USART_Init(USART1,&USART_InitStruct);                        //初始化USART1
	
	/*NVIC配置*/
	//选择中断方式并使能该方式中断
  USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);    //读取数据寄存器不为空(接收完成)中断 (USART->CR1的第5位) 

  //串口中断配置
  NVIC_InitStruct.NVIC_IRQChannel = USART1_IRQn;           //选择串口1中断
  NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 3;   //抢占优先级3
  NVIC_InitStruct.NVIC_IRQChannelSubPriority = 3;		       //子优先级3
  NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE; 		         //IRQ通道使能
  NVIC_Init(&NVIC_InitStruct); //串口1中断初始化
  
  //使能串口1
  USART_Cmd(USART1, ENABLE);
}



//注意,读取USARTx->SR能避免莫名其妙的错误   
//更新代码的缓存区	USART_RX_BUF[]
u8 USART_RX_BUF[USART_REC_LEN] __attribute__ ((at(0X20001000)));//接收缓冲,最大USART_REC_LEN个字节,起始地址为0X20001000.    
u16 USART_RX_STA=0;       	//接收状态标记	  
u16 USART_RX_CNT=0;			    //接收的字节数

/******************************************************************
*函数功能  ：串口1的中断服务函数
*函数名    ：USART1_IRQHandler
*函数参数  ：void
*函数返回值：void
*描述      ：
*******************************************************************/
void USART1_IRQHandler(void)
{
  u8 data;
  
  //判断是由什么形式触发中断
	//接收完成中断 
  if(USART1->SR&(1<<5))
  {
    //中断要执行的任务
    data = USART1->DR;
		//将新程序包放入USART_RX_BUF[]缓存区
		if(USART_RX_CNT<USART_REC_LEN)
		{
			USART_RX_BUF[USART_RX_CNT]=data;
			USART_RX_CNT++;			 									     
		}
  }
}






















/**********************************printf函数*****************************************/
//加入以下代码,支持printf函数,而不需要选择use MicroLIB	  
#if 1
#pragma import(__use_no_semihosting)             
//标准库需要的支持函数                 
struct __FILE 
{ 
	int handle; 

}; 

FILE __stdout;       
//定义_sys_exit()以避免使用半主机模式    
_sys_exit(int x) 
{ 
	x = x; 
} 
//重定义fputc函数 
int fputc(int ch, FILE *f)
{      
	while((USART1->SR&0X40)==0);//循环发送,直到发送完毕   
    USART1->DR = (u8) ch;      
	return ch;
}
#endif 
/***********************************************************************************/








