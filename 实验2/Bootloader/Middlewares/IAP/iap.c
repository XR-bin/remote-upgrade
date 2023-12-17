#include "iap.h"
#include "stmflash.h"



/**
******************************************************************************
* @file      ��.\IAP\iap.c
*              .\IAP\iap.h
* @author    ��XRbin
* @version   ��V1.0
* @date      ��2023-12-14
* @brief     ��iap��¼��ʽ(Bootloader)����
******************************************************************************
* @attention
*   �ҵ�GitHub   ��https://github.com/XR-bin
*   �ҵ�gitee    ��https://gitee.com/xrbin
*   �ҵ�leetcode ��https://leetcode.cn/u/xrbin/
******************************************************************************
*/


/***
*  ����ΪʲôiapBufҪ��Ϊȫ�ֱ�����
*  ����Ϊstartup_stm32f10x_hd.s�ļ��У��������õ�Stack_Size
*      Ϊ0x00000400(1024byte)��iapBuf��Ҫ2024��byte��ջ�ռ䲻��
*      �������ǲŽ����Ϊȫ�ֱ�����
*/
uint16_t iapBuf[1024]={0};         /* ������ */

/**********************************************************
* @funcName ��IAP_Write_AppBin
* @brief    �������³���д��ָ����ַ��flash
* @param    ��uint32_t appAddr (д�����ʼ��ַ)
* @param    ��uint8_t *appBuf (���³����)
* @param    ��uint32_t appSize (�������С)
* @retval   ��void
* @details  ��
* @fn       ��
************************************************************/
void IAP_Write_AppBin(uint32_t appAddr, uint8_t *appBuf, uint32_t appSize)
{
    uint16_t t;
    uint16_t i = 0;
    uint16_t temp;
    uint32_t fwaddr = appAddr;         /* ��ǰд��ĵ�ַ */
    uint8_t *buf = appBuf;

    for(t=0;t<appSize;t+=2)
    {
        temp = (uint16_t)(buf[1]<<8);
        temp |= (uint16_t)buf[0];
        buf += 2;  /* ƫ��2���ֽ� */
        iapBuf[i++] = temp;

        if(i == 1024)
        {
            i = 0;
            STMFLASH_Write(fwaddr, iapBuf, 1024);
            fwaddr += 2048;    /* ƫ��2048  16=2*8.����Ҫ����2. */
        }
    }

    if(i != 0)STMFLASH_Write(fwaddr, iapBuf, i);  /* ������һЩ�����ֽ�д��ȥ. */
}



/**********************************************************
* @funcName ��IAP_Load_App
* @brief    ��ִ��ָ����ַ��flash�����app����
* @param    ��uint32_t appAddr (ָ��flash��ַ)
* @retval   ��void
* @details  ��
* @fn       ��
************************************************************/
void IAP_Load_App(uint32_t appAddr)
{
    iapfun jumpApp;                    /* ����ָ�� */

    /* ������� ջ����ַ �Ƿ�Ϸ�. */
    if(((*(volatile uint32_t*)appAddr)&0x2FFE0000) == 0x20000000)
    {
        jumpApp = (iapfun)*(volatile uint32_t*)(appAddr+4);    /* �û��������ڶ�����Ϊ����ʼ��ַ(��λ��ַ) */
        MSR_MSP(*(volatile uint32_t*)appAddr);                 /* ��ʼ��APP��ջָ��(�û��������ĵ�һ�������ڴ��ջ����ַ) */
        jumpApp();                                             /* ��ת��APP. */
    }
}



