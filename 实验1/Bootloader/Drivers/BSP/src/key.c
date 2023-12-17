#include "key.h"



/**
******************************************************************************
* @file      ��.\Drivers\BSP\src\key.c
*              .\Drivers\BSP\inc\key.h
* @author    ��XRbin
* @version   ��V1.0
* @date      ��2023-06-16
* @brief     �������������ô���
******************************************************************************
* @attention
*   �ҵ�GitHub   ��https://github.com/XR-bin
*   �ҵ�gitee    ��https://gitee.com/xrbin
*   �ҵ�leetcode ��https://leetcode.cn/u/xrbin/
******************************************************************************
*/



/**********************************************************
* @funcName ��KEY_Init
* @brief    ����KEY��Ӧ��GPIO�ڽ��г�ʼ������
* @param    ��void
* @retval   ��void
* @details  ��
*            KEY0     PE4
*            KEY1     PE3
*            KEY_UP   PA0
*                                 -------------���ģʽ
* @fn       ��
************************************************************/
void KEY_Init(void)
{
    GPIO_InitTypeDef  GPIO_InitStructure;         /* GPIOx���ýṹ�� */

    /* GPIOx���� */
    /* GPIOxʱ��ʹ��  GPIOA��GPIOE */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);

    /* GPIOx���� */
    /* PE */
    GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_3|GPIO_Pin_4;  /* PE3/4�˿����� */
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;          /* �������� */
    GPIO_Init(GPIOE, &GPIO_InitStructure);                 /* �����趨������ʼ��GPIE PE3/4 */
    /* PA */
    GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0;             /* PA0�˿����� */
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;          /* �������� */
    GPIO_Init(GPIOA, &GPIO_InitStructure);                 /* �����趨������ʼ��GPIOA PA0 */
}



/**********************************************************
* @funcName ��KEY_Scan
* @brief    ������ɨ�躯��
* @param    ��void
* @retval   ��uint8_t
* @details  ��
*            KEY0��KEY1 �͵�ƽ���£��ߵ�ƽ̧��
*            KEY_UP     �ߵ�ƽ���£��͵�ƽ̧��
* @fn       ��
************************************************************/
uint8_t KEY_Scan(void)
{
    uint8_t temp = 0;
    static uint8_t key_flay = 1;

    if(key_flay && ( KEY_UP==1 || KEY0==0 || KEY1==0 ))
    {
        delay_ms(10);
        if( KEY_UP==1 || KEY0==0 || KEY1==0 )
        {
            key_flay = 0;
            if(KEY0==0)        temp = 1;
            else if(KEY1==0)   temp = 2;
            else if(KEY_UP==1) temp = 3;
        }
    }

    if(KEY_UP==0 && KEY0==1 && KEY1==1)
    {
        key_flay = 1;
    }

    return temp;
}











