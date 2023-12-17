#include "stmflash.h"



/**
******************************************************************************
* @file      ��.\Drivers\BSP\src\stmflash.c
*              .\Drivers\BSP\inc\stmflash.h
* @author    ��XRbin
* @version   ��V1.0
* @date      ��2023-12-12
* @brief     ��STM32�ڲ�Flash��д����
******************************************************************************
* @attention
*   �ҵ�GitHub   ��https://github.com/XR-bin
*   �ҵ�gitee    ��https://gitee.com/xrbin
*   �ҵ�leetcode ��https://leetcode.cn/u/xrbin/
******************************************************************************
*/



/**********************************************************
* @funcName ��STMFLASH_Read_HalfWord
* @brief    ����ȡָ����ַ�İ���(16λ����)
* @param    ��uint32_t faddr(����ַ,�˵�ַ����Ϊ2�ı���!!)
* @retval   ��uint16_t --- (��ַ�е�����)
* @details  ��
* @fn       ��
************************************************************/
uint16_t STMFLASH_Read_HalfWord(uint32_t faddr)
{
    return *(volatile uint16_t*)faddr; 
}



/**********************************************************
* @funcName ��STMFLASH_Read
* @brief    ����ָ����ַ��ʼ����ָ�����ȵ�����
* @param    ��uint32_t rAddr (��ʼ��ַ���˵�ַ����Ϊ2�ı���!!,����д�����!)
* @param    ��uint16_t *pBuf (�����ݵĻ���)
* @param    ��uint16_t length (Ҫ�������ݳ���)
* @retval   ��void
* @details  ��
* @fn       ��
************************************************************/
void STMFLASH_Read(uint32_t rAddr, uint16_t *pBuf, uint16_t length)
{
    uint16_t i;

    for(i=0; i<length; i++)
    {
        pBuf[i]=STMFLASH_Read_HalfWord(rAddr);/* ��ȡ2���ֽ� */
        rAddr+=2;                            /* ƫ��2���ֽ� */
    }
}



/**********************************************************
* @funcName ��STMFLASH_Write_NoCheck
* @brief    ����ָ����ַ��ʼд��ָ�����ȵ�����(������д��)
* @param    ��uint32_t wAddr (��ʼ��ַ���˵�ַ����Ϊ2�ı���!!,����д�����!)
* @param    ��uint16_t *pBuf (�����ݵĻ���)
* @param    ��uint16_t length (Ҫд�����ݳ���)
* @retval   ��void
* @details  ��
* @fn       ��
************************************************************/
void STMFLASH_Write_NoCheck(uint32_t wAddr, uint16_t *pBuf, uint16_t length)
{
    uint16_t i;

    for(i=0; i<length; i++)
    {
        FLASH_ProgramHalfWord(wAddr, pBuf[i]);  /* д���� */
        wAddr+=2;                               /* ��ַ����2 */
    }  
}



uint16_t STMFLASH_BUF[STM32_SECTOR_SIZE/2];     /* ��ȡ���ݵĻ��棬�����2K�ֽ� */

/**********************************************************
* @funcName ��STMFLASH_Write
* @brief    ����ָ����ַ��ʼд��ָ�����ȵ�����(�м���д��)
* @param    ��uint32_t wAddr (��ʼ��ַ���˵�ַ����Ϊ2�ı���!!,����д�����!)
* @param    ��uint16_t *pBuf (�����ݵĻ���)
* @param    ��uint16_t length (Ҫд�����ݳ���)
* @retval   ��void
* @details  ��
* @fn       ��
************************************************************/
void STMFLASH_Write(uint32_t wAddr, uint16_t *pBuf, uint16_t length)
{
    uint32_t secpos;        /* ������ַ */
    uint16_t secoff;        /* ������ƫ�Ƶ�ַ(16λ�ּ���) */
    uint16_t secremain;     /* ������ʣ���ַ(16λ�ּ���) */
    uint16_t i;
    uint32_t offaddr;       /* ȥ��0X08000000��ĵ�ַ */

    if (wAddr < STM32_FLASH_BASE || (wAddr >= (STM32_FLASH_BASE + 1024 * STM32_FLASH_SIZE)))
    {
        return;      /* �Ƿ���ַ */
    }

    FLASH_Unlock();  /* ���� */

    offaddr = wAddr - STM32_FLASH_BASE;         /* ʵ��ƫ�Ƶ�ַ */
    secpos = offaddr / STM32_SECTOR_SIZE;       /* ������ַ  0~127 for STM32F103RBT6 */
    secoff = (offaddr % STM32_SECTOR_SIZE) / 2; /* �������ڵ�ƫ��(2���ֽ�Ϊ������λ.) */
    secremain = STM32_SECTOR_SIZE / 2 - secoff; /* ����ʣ��ռ��С */

    if (length <= secremain)
    {
        secremain = length; /* �����ڸ�������Χ */
    }

    while(1)
    {
        /* ������������������ */
        STMFLASH_Read(secpos*STM32_SECTOR_SIZE+STM32_FLASH_BASE, STMFLASH_BUF, STM32_SECTOR_SIZE/2);

        for(i = 0; i < secremain; i++)     /* У������ */
        {
            if(STMFLASH_BUF[secoff + i] != 0XFFFF)
            {
                break;      /* ��Ҫ���� */
            }
        }

        if(i < secremain)  /* ��Ҫ���� */
        {
            /* ����������� */
            FLASH_ErasePage(secpos * STM32_SECTOR_SIZE + STM32_FLASH_BASE);

            for(i=0;i<secremain;i++)    /* ���� */
            {
                STMFLASH_BUF[i+secoff] = pBuf[i];
            }

            /* д���������� */
            STMFLASH_Write_NoCheck(secpos*STM32_SECTOR_SIZE+STM32_FLASH_BASE, STMFLASH_BUF, STM32_SECTOR_SIZE/2);
        }
        else
        {
            /* д�Ѿ������˵�,ֱ��д������ʣ������ */
            STMFLASH_Write_NoCheck(wAddr, pBuf, secremain);
        }

        if(length == secremain)
        {
            break;//д�������
        }
        else
        {
            secpos++;               /* ������ַ��1 */
            secoff = 0;             /* ƫ��λ��Ϊ0 */
            pBuf += secremain;      /* ָ��ƫ�� */
            wAddr += secremain * 2; /* д��ַƫ��(16λ���ݵ�ַ,��Ҫ*2) */
            length -= secremain;    /* �ֽ�(16λ)���ݼ� */

            if (length > (STM32_SECTOR_SIZE / 2))
            {
                secremain = STM32_SECTOR_SIZE / 2; /* ��һ����������д���� */
            }
            else
            {
                secremain = length;                /* ��һ����������д���� */
            }
        }
    }

    FLASH_Lock();       /* ���� */
}



