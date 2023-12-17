#include "update.h"



/**
******************************************************************************
* @file      ：.\Middlewares\Update\update.c
*              .\Middlewares\Update\update.h
* @author    ：XRbin
* @version   ：V1.0
* @date      ：2023-12-14
* @brief     ：跳转到Bootloader代码
******************************************************************************
* @attention
*   我的GitHub   ：https://github.com/XR-bin
*   我的gitee    ：https://gitee.com/xrbin
*   我的leetcode ：https://leetcode.cn/u/xrbin/
******************************************************************************
*/



/**********************************************************
* @funcName ：Updata_Code
* @brief    ：进入到Bootloader程序进行更新代码
* @param    ：void
* @retval   ：void
* @details  ：
* @fn       ：
************************************************************/
void Updata_Code(void)
{
    ptr_code ptr_boot=NULL;

    printf("程序准备跳转到Bootloader......\r\n");
    delay_ms(100);     /* 这里延时是为了保证上面的打印能够完成再跳转 */

    /* 函数指针指向boot代码的Reset_Handler */
    ptr_boot=(ptr_code)(*(uint32_t*)(BOOT_CODE_ADDR+4));

    /* 手动加载boot代码的栈顶位置__initial_sp到SP寄存器中 */
    MSR_MSP(*(uint32_t*)BOOT_CODE_ADDR);

    /* 通过函数指针调用切换到boot代码 */
    ptr_boot();
}





