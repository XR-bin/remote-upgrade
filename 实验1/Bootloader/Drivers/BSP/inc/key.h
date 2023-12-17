#ifndef __KEY_H
#define __KEY_H

    /****************   �ⲿͷ�ļ�����   ****************/
    #include "sys.h"
    #include "delay.h"



    /********************   �궨��   ********************/
    #define KEY0    GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4)
    #define KEY1    GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_3)
    #define KEY_UP  GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)



    /****************    �����ⲿ����   *****************/
    void KEY_Init(void);
    uint8_t KEY_Scan(void);

#endif












