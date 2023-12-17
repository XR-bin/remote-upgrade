#ifndef __USART_H
#define __USART_H

    /****************   外部头文件声明   ****************/
    #include "sys.h" 
    #include "stdio.h"



    /********************   宏定义   ********************/
    //更新代码缓存区大小设为55k
    #define   USART_REC_LEN   55*1024


    /****************    变量外部声明   *****************/
    extern uint8_t USART_RX_BUF[USART_REC_LEN];
    extern uint16_t USART_RX_STA;
    extern uint16_t USART_RX_CNT;



    /****************    函数外部声明   *****************/
    /*串口1*/
    void USART1_Init(uint32_t baud);          /* 串口1初始化 */
    void USART1_Send_Byte(uint8_t data);      /* 串口1发生一个字节 */
    uint8_t USART1_Receive_Byte(void);        /* 串口1接收一个字节 */
    void USART1_Send_Str(uint8_t *str);       /* 串口1发生一个字符串 */
    void USART1_Receive_Str(uint8_t *str);    /* 串口1接收一个字符串 */

#endif



