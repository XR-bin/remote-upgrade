#ifndef __IAP_H
#define __IAP_H

    /****************   �ⲿͷ�ļ�����   ****************/
    #include "sys.h"



    /*****************   �������Ͷ���   *****************/
    typedef  void(*iapfun)(void);          /* ����һ������������������ iapfun */



    /********************   �궨��   ********************/
    /* user������flash��ʼ��ַ */
    #define   USER_CODE_ADDR   0x08000000

    /* Bootloader������flash��ʼ��ַ */
    #define   BOOT_CODE_ADDR   0x08010000



    /****************    �����ⲿ����   *****************/
    void IAP_Write_AppBin(uint32_t appAddr, uint8_t *appBuf, uint32_t appSize);  /* �������д��ָ��flash */
    void IAP_Load_App(uint32_t appAddr);                                         /* ��תִ��Ŀ��flash�ĳ��� */

#endif






