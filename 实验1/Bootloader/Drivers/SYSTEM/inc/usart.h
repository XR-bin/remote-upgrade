#ifndef __USART_H
#define __USART_H

    /****************   �ⲿͷ�ļ�����   ****************/
    #include "sys.h" 
    #include "stdio.h"



    /********************   �궨��   ********************/
    //���´��뻺������С��Ϊ55k
    #define   USART_REC_LEN   55*1024


    /****************    �����ⲿ����   *****************/
    extern uint8_t USART_RX_BUF[USART_REC_LEN];
    extern uint16_t USART_RX_STA;
    extern uint16_t USART_RX_CNT;



    /****************    �����ⲿ����   *****************/
    /*����1*/
    void USART1_Init(uint32_t baud);          /* ����1��ʼ�� */
    void USART1_Send_Byte(uint8_t data);      /* ����1����һ���ֽ� */
    uint8_t USART1_Receive_Byte(void);        /* ����1����һ���ֽ� */
    void USART1_Send_Str(uint8_t *str);       /* ����1����һ���ַ��� */
    void USART1_Receive_Str(uint8_t *str);    /* ����1����һ���ַ��� */

#endif



