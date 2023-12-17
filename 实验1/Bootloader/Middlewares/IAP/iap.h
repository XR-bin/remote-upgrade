#ifndef __IAP_H
#define __IAP_H

    /****************   �ⲿͷ�ļ�����   ****************/
    #include "sys.h"



    /*****************   �������Ͷ���   *****************/
    typedef  void(*iapfun)(void);          /* ����һ������������������ iapfun */



    /********************   �궨��   ********************/
    #define   FLASH_APP_ADDR   0x08010000  /* Ӧ�ó�����ʼ��ַ(�����FLASH) */
                                           /* ����0X08000000~0X0800FFFF�Ŀռ�ΪIAPʹ�� */
    #define   SRAM_APP_ADDR    0X20001000  /* Ӧ�ó�����ʼ��ַ(�����SRAM) */


    /****************    �����ⲿ����   *****************/
    void IAP_Write_AppBin(uint32_t appAddr, uint8_t *appBuf, uint32_t appSize);  /* �������д��ָ��flash */
    void IAP_Load_App(uint32_t appAddr);                                         /* ��תִ��Ŀ��flash�ĳ��� */

#endif






