#include "stm32f10x.h"
#include "usart.h"
#include "stdio.h"

/*****************************************************
*��������  ����USART1��Ӧ��GPIO�ڽ��г�ʼ������
*������    ��USART1_Init
*��������  ��u32 baud
*��������ֵ��void
*����      ��
*           PA9     TX     ---------���
*           PA10    RX     ---------����
********************************************************/
void USART1_Init(u32 baud)
{
  GPIO_InitTypeDef  GPIO_InitStruct;     //GPIOx���ýṹ��
  USART_InitTypeDef USART_InitStruct;    //USARTx���ýṹ��
	NVIC_InitTypeDef   NVIC_InitStruct;    //NVIC(�ж�)���ýṹ��
  
  //ʱ��ʹ��   GPIOA   USART1
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_USART1,ENABLE); 
  
  /*GPIOx��ʼ������*/
  //GPIOx�˿�����
  //PA9   USART1_TX ----- ���ô������
  GPIO_InitStruct.GPIO_Pin   = GPIO_Pin_9;				     //PA9 �˿�����
  GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_AF_PP; 	  	 //����������
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;		   //IO���ٶ�Ϊ50MHz
  GPIO_Init(GPIOA, &GPIO_InitStruct);                  //�����趨������ʼ��PA9
  //PA10  USART1_RX ----- ���ô�������
  GPIO_InitStruct.GPIO_Pin   = GPIO_Pin_10;				     //PA10 �˿�����
  GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_IN_FLOATING;  //��������
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;		   //IO���ٶ�Ϊ50MHz
  GPIO_Init(GPIOA, &GPIO_InitStruct);                  //�����趨������ʼ��PA10
  
  /*USART ��ʼ������*/
  //USART1����
  USART_InitStruct.USART_BaudRate      = baud;                 //����������(USART->BRR�Ĵ���)
  USART_InitStruct.USART_WordLength    = USART_WordLength_8b;  //�ֳ�Ϊ8λ���ݸ�ʽ:һ����ʼλ�� 8������λ�� n��ֹͣλ��(USART->CR1�Ĵ����ĵ�12λ)
  USART_InitStruct.USART_StopBits      = USART_StopBits_1;     //һ��ֹͣλ(USART->CR2�Ĵ����ĵ�12��13λ)
  USART_InitStruct.USART_Parity        = USART_Parity_No;      //����żУ��(USART->CR1�Ĵ����ĵ�10λ)
  USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������(USART->CR3�Ĵ����ĵ�9λ)
  USART_InitStruct.USART_Mode = USART_Mode_Rx | USART_Mode_Tx; //�շ�ģʽ(USART->CR1�Ĵ����ĵ�2��3λ)
  USART_Init(USART1,&USART_InitStruct);                        //��ʼ��USART1
	
	/*NVIC����*/
	//ѡ���жϷ�ʽ��ʹ�ܸ÷�ʽ�ж�
  USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);    //��ȡ���ݼĴ�����Ϊ��(�������)�ж� (USART->CR1�ĵ�5λ) 

  //�����ж�����
  NVIC_InitStruct.NVIC_IRQChannel = USART1_IRQn;           //ѡ�񴮿�1�ж�
  NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 3;   //��ռ���ȼ�3
  NVIC_InitStruct.NVIC_IRQChannelSubPriority = 3;		       //�����ȼ�3
  NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE; 		         //IRQͨ��ʹ��
  NVIC_Init(&NVIC_InitStruct); //����1�жϳ�ʼ��
  
  //ʹ�ܴ���1
  USART_Cmd(USART1, ENABLE);
}



//ע��,��ȡUSARTx->SR�ܱ���Ī������Ĵ���   
//���´���Ļ�����	USART_RX_BUF[]
u8 USART_RX_BUF[USART_REC_LEN] __attribute__ ((at(0X20001000)));//���ջ���,���USART_REC_LEN���ֽ�,��ʼ��ַΪ0X20001000.    
u16 USART_RX_STA=0;       	//����״̬���	  
u16 USART_RX_CNT=0;			    //���յ��ֽ���

/******************************************************************
*��������  ������1���жϷ�����
*������    ��USART1_IRQHandler
*��������  ��void
*��������ֵ��void
*����      ��
*******************************************************************/
void USART1_IRQHandler(void)
{
  u8 data;
  
  //�ж�����ʲô��ʽ�����ж�
	//��������ж� 
  if(USART1->SR&(1<<5))
  {
    //�ж�Ҫִ�е�����
    data = USART1->DR;
		
		//���³��������USART_RX_BUF[]������
		if(USART_RX_CNT<USART_REC_LEN)
		{
			USART_RX_BUF[USART_RX_CNT]=data;
			USART_RX_CNT++;			 									     
		}
  }
}






















/**********************************printf����*****************************************/
//�������´���,֧��printf����,������Ҫѡ��use MicroLIB	  
#if 1
#pragma import(__use_no_semihosting)             
//��׼����Ҫ��֧�ֺ���                 
struct __FILE 
{ 
	int handle; 

}; 

FILE __stdout;       
//����_sys_exit()�Ա���ʹ�ð�����ģʽ    
_sys_exit(int x) 
{ 
	x = x; 
} 
//�ض���fputc���� 
int fputc(int ch, FILE *f)
{      
	while((USART1->SR&0X40)==0);//ѭ������,ֱ���������   
    USART1->DR = (u8) ch;      
	return ch;
}
#endif 
/***********************************************************************************/








