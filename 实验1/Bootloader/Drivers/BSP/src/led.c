#include "led.h"



/**
******************************************************************************
* @file      ��.\Drivers\BSP\src\led.c
*              .\Drivers\BSP\inc\led.h
* @author    ��XRbin
* @version   ��V1.0
* @date      ��2023-06-16
* @brief     ��LED���������ô���
******************************************************************************
* @attention
*   �ҵ�GitHub   ��https://github.com/XR-bin
*   �ҵ�gitee    ��https://gitee.com/xrbin
*   �ҵ�leetcode ��https://leetcode.cn/u/xrbin/
******************************************************************************
*/



/**********************************************************
* @funcName ��LED_Init
* @brief    ����LED��Ӧ��GPIO�ڽ��г�ʼ������
* @param    ��void
* @retval   ��void
* @details  ��
*            LED0     PB5
*            LED1     PE5
*            �ߵ�ƽ�𣬵͵�ƽ��-----���ģʽ
* @fn       ��
************************************************************/
void LED_Init(void)
{
    GPIO_InitTypeDef  GPIO_InitStructure;                   /* GPIOx���ýṹ�� */

    /* ʱ��ʹ��   GPIOB   GPIOC */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);   /* ʹ��PB�˿�ʱ�� */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);   /* ʹ��PE�˿�ʱ�� */

    /* PB5 */
    GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_5;             /* PB5 �˿����� */
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;       /* ������� */
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;       /* IO���ٶ�Ϊ50MHz */
    GPIO_Init(GPIOB, &GPIO_InitStructure);                  /* �����趨������ʼ��PB5 */

    /* PE5 */
    /* Ӧ�䲿��������PB5һ�£����Խṹ��һЩ������������ */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;               /* PE5 �˿�����, ������� */
    GPIO_Init(GPIOE, &GPIO_InitStructure);                  /* �����趨������ʼ��PE5 */

    /* �˿�������ݼĴ�������   LED�Ƶĳ�ʼ״̬ */
    GPIO_SetBits(GPIOB,GPIO_Pin_5);                         /* PB5 ����� */
    GPIO_SetBits(GPIOE,GPIO_Pin_5);                         /* PE5 ����� */
}




