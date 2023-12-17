#include "usart.h"



/**********************************************************
* @funcName ��USART1_Init
* @brief    ����USART1��Ӧ��GPIO�ڽ��г�ʼ������
* @param    ��uint32_t baud
* @retval   ��void
* @details  ��
*             PA9     TX     ---------���
*             PA10    RX     ---------����
* @fn       ��
************************************************************/
void USART1_Init(uint32_t baud)
{
    GPIO_InitTypeDef  GPIO_InitStruct;     /* GPIOx���ýṹ�� */
    USART_InitTypeDef USART_InitStruct;    /* USARTx���ýṹ�� */
    NVIC_InitTypeDef   NVIC_InitStruct;    /* NVIC(�ж�)���ýṹ�� */

    /* ʱ��ʹ��   GPIOA   USART1 */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_USART1, ENABLE); 

    /* GPIOx��ʼ������ */
    /* GPIOx�˿����� */
    /* PA9   USART1_TX ----- ���ô������ */
    GPIO_InitStruct.GPIO_Pin   = GPIO_Pin_9;             /* PA9 �˿����� */
    GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_AF_PP;        /* ���������� */
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;       /* IO���ٶ�Ϊ50MHz */
    GPIO_Init(GPIOA, &GPIO_InitStruct);                  /* �����趨������ʼ��PA9 */
    /* PA10  USART1_RX ----- ���ô������� */
    GPIO_InitStruct.GPIO_Pin   = GPIO_Pin_10;            /* PA10 �˿����� */
    GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_IN_FLOATING;  /* �������� */
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;       /* IO���ٶ�Ϊ50MHz */
    GPIO_Init(GPIOA, &GPIO_InitStruct);                  /* �����趨������ʼ��PA10 */

    /* USART ��ʼ������ */
    /* USART1���� */
    USART_InitStruct.USART_BaudRate      = baud;                 /* ����������(USART->BRR�Ĵ���) */
    USART_InitStruct.USART_WordLength    = USART_WordLength_8b;  /* �ֳ�Ϊ8λ���ݸ�ʽ:һ����ʼλ�� 8������λ�� n��ֹͣλ��(USART->CR1�Ĵ����ĵ�12λ) */
    USART_InitStruct.USART_StopBits      = USART_StopBits_1;     /* һ��ֹͣλ(USART->CR2�Ĵ����ĵ�12��13λ) */
    USART_InitStruct.USART_Parity        = USART_Parity_No;      /* ����żУ��(USART->CR1�Ĵ����ĵ�10λ) */
    USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;/* ��Ӳ������������(USART->CR3�Ĵ����ĵ�9λ) */
    USART_InitStruct.USART_Mode = USART_Mode_Rx | USART_Mode_Tx; /* �շ�ģʽ(USART->CR1�Ĵ����ĵ�2��3λ) */
    USART_Init(USART1,&USART_InitStruct);                        /* ��ʼ��USART1 */

    /* NVIC���� */
    /* ѡ���жϷ�ʽ��ʹ�ܸ÷�ʽ�ж� */
    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);     /* ��ȡ���ݼĴ�����Ϊ��(�������)�ж� (USART->CR1�ĵ�5λ) */
    USART_ITConfig(USART1, USART_IT_IDLE, ENABLE);     /* ��⵽������·(����)�ж� (USART->CR1�ĵ�4λ) */

    /* �����ж����� */
    NVIC_InitStruct.NVIC_IRQChannel = USART1_IRQn;           /* ѡ�񴮿�1�ж� */
    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1;   /* ��ռ���ȼ�1 */
    NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1;          /* �����ȼ�1 */
    NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;             /* IRQͨ��ʹ�� */
    NVIC_Init(&NVIC_InitStruct);                             /* ����1�жϳ�ʼ�� */

    /* ʹ�ܴ���1 */
    USART_Cmd(USART1, ENABLE);
}



/* ���´���Ļ�����USART_RX_BUF[] */
uint8_t USART_RX_BUF[USART_REC_LEN] __attribute__ ((at(0X20001000)));/* ���ջ���,���USART_REC_LEN���ֽ�,��ʼ��ַΪ0X20001000. */
uint16_t USART_RX_STA = 0;        /* ����״̬��� 0-δ������� 1-�ѽ������ */
uint16_t USART_RX_CNT = 0;        /* ���յ��ֽ��� */

/**********************************************************
* @funcName ��USART1_IRQHandler
* @brief    ������1�ж�
* @param    ��void
* @retval   ��void
* @details  ��
* @fn       ��
************************************************************/
void USART1_IRQHandler(void)
{
    uint8_t data=0;

    /* �ж��жϴ�������ʽ */
    /* ��������ж� */
    if(USART1->SR & (1<<5))
    {
        /* �ж�Ҫִ�е����� */
        data = USART1->DR;

        /* ���³��������USART_RX_BUF[]������ */
        if(USART_RX_CNT<USART_REC_LEN)
        {
            USART_RX_BUF[USART_RX_CNT]=data;
            USART_RX_CNT++;
        }

        /* �ȶ�USART1->SR���ٸ�USART1->DR����������жϱ�־ */
        /* ����ֱ���޸�USART1->SR���Ӷ�����жϱ�־ */
        /* ���������ַ�ʽ���� */
        USART1->SR &= ~(1<<5);
    }
    if(USART1->SR & (1<<4))
    {
        USART_RX_STA = 1;   /* ������� */

        /* �ȶ�USART1->SR���ٸ�USART1->DR����������жϱ�־ */
        /* ����ֱ���޸�USART1->SR���Ӷ�����жϱ�־ */
        /* ���������ַ�ʽ���� */
        USART1->SR &= ~(1<<4);
        USART1->DR;
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
void _sys_exit(int x)
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


