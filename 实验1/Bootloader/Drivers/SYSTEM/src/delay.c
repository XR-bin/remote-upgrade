#include "delay.h"



/**********************************************************
* @funcName ��SysTick_Init
* @brief    ���δ�ʱ����ʼ��
* @param    ��void
* @retval   ��void
* @details  ��
* @fn       ��
************************************************************/
void SysTick_Init(void)
{
    SysTick->CTRL = 0;         /* ��Systick״̬���Ա���һ�����裬������￪���жϻ�ر����ж� */
    SysTick->CTRL &= ~(1<<2);  /* ѡ��ʱ��Դ   д0���ⲿʱ��Դ   д1���ڲ�ʱ��Դ */
}



/**********************************************************
* @funcName ��delay_us
* @brief    ��ϵͳ�δ�ʱ��΢����ʱ
* @param    ��uint32_t us (΢��)
* @retval   ��void
* @details  ��
* @fn       ��
************************************************************/
void delay_us(uint32_t us)
{
    SysTick->VAL = 0xff;                 /* ����ǰֵ�Ĵ�������   ���дһ�����ݽ��� */
    SysTick->LOAD = 9*us;                /* ��Ҫ��ʱ������д�뵽��װ��ֵ�Ĵ��� */
    SysTick->CTRL |= (1<<0);             /* ��ʼ����   ��������ʹ�� */
    while(!(SysTick->CTRL & (1<<16)));   /* �ȴ��������    while(16λΪ0) */
    SysTick->CTRL &= ~(1<<0);            /* �رռ����� */
}



/**********************************************************
* @funcName ��delay1_ms
* @brief    ��ϵͳ�δ�ʱ��΢����ʱ
* @param    ��uint16_t ms (����)
* @retval   ��void
* @details  ��
* @fn       ��
************************************************************/
void delay1_ms(uint16_t ms)
{
    SysTick->VAL = 0xff;                 /* ����ǰֵ�Ĵ�������   ���дһ�����ݽ��� */
    SysTick->LOAD = 9*1000*ms;           /* ��Ҫ��ʱ������д�뵽��װ��ֵ�Ĵ��� */ 
    SysTick->CTRL |= (1<<0);             /* ��ʼ����   ��������ʹ�� */
    while(!(SysTick->CTRL & (1<<16)));   /* �ȴ��������    while(16λΪ0) */
    SysTick->CTRL &= ~(1<<0);            /* �رռ����� */
}



/**********************************************************
* @funcName ��delay_ms
* @brief    ��ϵͳ�δ�ʱ��΢����ʱ(�޸İ�)
* @param    ��uint16_t ms (����)
* @retval   ��void
* @details  ��
* @fn       ��
************************************************************/
void delay_ms(uint16_t ms)
{
    uint16_t i,n=0;

    if(ms <= 1864)
    {
        delay1_ms(ms);
    }
    else
    {
        while(ms >= 1864)
        {
            ms -= 1864;
            n++;
        }
        for(i=0;i<n;i++) delay1_ms(1864);
        delay1_ms(ms);
    }
}

