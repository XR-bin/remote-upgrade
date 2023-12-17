#ifndef __UPDATE_H
#define __UPDATE_H

    /****************   �ⲿͷ�ļ�����   ****************/
    #include "sys.h"
    #include "delay.h"
    #include "usart.h"



    /*****************   �������Ͷ���   *****************/
    typedef void(*ptr_code)(void);          /* ����һ������������������ ptr_code */



    /********************   �궨��   ********************/
    /* user������flash��ʼ��ַ */
    #define   USER_CODE_ADDR   0x08000000

    /* Bootloader������flash��ʼ��ַ */
    #define   BOOT_CODE_ADDR   0x08010000



    /****************    �����ⲿ����   *****************/
    void Updata_Code(void);       /* ���뵽Bootloader������и��´��� */

#endif






