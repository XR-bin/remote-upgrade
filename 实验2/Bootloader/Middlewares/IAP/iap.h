#ifndef __IAP_H
#define __IAP_H

    /****************   外部头文件声明   ****************/
    #include "sys.h"



    /*****************   数据类型定义   *****************/
    typedef  void(*iapfun)(void);          /* 定义一个函数变量数据类型 iapfun */



    /********************   宏定义   ********************/
    /* user代码区flash起始地址 */
    #define   USER_CODE_ADDR   0x08000000

    /* Bootloader代码区flash起始地址 */
    #define   BOOT_CODE_ADDR   0x08010000



    /****************    函数外部声明   *****************/
    void IAP_Write_AppBin(uint32_t appAddr, uint8_t *appBuf, uint32_t appSize);  /* 将程序包写入指定flash */
    void IAP_Load_App(uint32_t appAddr);                                         /* 跳转执行目标flash的程序 */

#endif






