#ifndef __STMFLASH_H
#define __STMFLASH_H

    /****************   �ⲿͷ�ļ�����   ****************/
    #include "sys.h"



    /********************   �궨��   ********************/
    /* FLASH��ʼ��ַ */
    #define STM32_FLASH_SIZE        0x80000         /* STM32 FLASH �ܴ�С */
    #define STM32_FLASH_BASE        0x08000000      /* STM32 FLASH ��ʼ��ַ */

    /* STM32F103 ������С */
    #if STM32_FLASH_SIZE < 256 * 1024
        #define STM32_SECTOR_SIZE   1024           /* ����С��256K�� F103, ������СΪ1K�ֽ� */
    #else
        #define STM32_SECTOR_SIZE   2048           /* �������ڵ�����256K�� F103, ������СΪ2K�ֽ� */
    #endif



    /****************    �����ⲿ����   *****************/
    uint16_t STMFLASH_Read_HalfWord(uint32_t faddr);                               /* ���ڲ�flash��ȡһ��uint16_t���� */
    void STMFLASH_Read(uint32_t rAddr, uint16_t *pBuf, uint16_t length);           /* ���ڲ�flash��ȡ���uint16_t���� */
    void STMFLASH_Write_NoCheck(uint32_t wAddr, uint16_t *pBuf, uint16_t length);  /* ���ڲ�flashд����uint16_t����(�������) */
    void STMFLASH_Write(uint32_t wAddr, uint16_t *pBuf, uint16_t length);          /* ���ڲ�flashд����uint16_t����(�д����) */

#endif





