#ifndef __UPDATE_H
#define __UPDATE_H

    /****************   外部头文件声明   ****************/
    #include "sys.h"
    #include "delay.h"
    #include "usart.h"



    /*****************   数据类型定义   *****************/
    typedef void(*ptr_code)(void);          /* 定义一个函数变量数据类型 ptr_code */



    /********************   宏定义   ********************/
    /* user代码区flash起始地址 */
    #define   USER_CODE_ADDR   0x08000000

    /* Bootloader代码区flash起始地址 */
    #define   BOOT_CODE_ADDR   0x08010000



    /****************    函数外部声明   *****************/
    void Updata_Code(void);       /* 进入到Bootloader程序进行更新代码 */

#endif






