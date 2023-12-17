#include "iap.h"
#include "stmflash.h"



/**
******************************************************************************
* @file      ：.\IAP\iap.c
*              .\IAP\iap.h
* @author    ：XRbin
* @version   ：V1.0
* @date      ：2023-12-14
* @brief     ：iap烧录方式(Bootloader)代码
******************************************************************************
* @attention
*   我的GitHub   ：https://github.com/XR-bin
*   我的gitee    ：https://gitee.com/xrbin
*   我的leetcode ：https://leetcode.cn/u/xrbin/
******************************************************************************
*/


/***
*  解释为什么iapBuf要设为全局变量？
*  答：因为startup_stm32f10x_hd.s文件中，我们设置的Stack_Size
*      为0x00000400(1024byte)，iapBuf需要2024个byte，栈空间不够
*      所以我们才将其变为全局变量。
*/
uint16_t iapBuf[1024]={0};         /* 缓存区 */

/**********************************************************
* @funcName ：IAP_Write_AppBin
* @brief    ：将更新程序写入指定地址的flash
* @param    ：uint32_t appAddr (写入的起始地址)
* @param    ：uint8_t *appBuf (更新程序包)
* @param    ：uint32_t appSize (程序包大小)
* @retval   ：void
* @details  ：
* @fn       ：
************************************************************/
void IAP_Write_AppBin(uint32_t appAddr, uint8_t *appBuf, uint32_t appSize)
{
    uint16_t t;
    uint16_t i = 0;
    uint16_t temp;
    uint32_t fwaddr = appAddr;         /* 当前写入的地址 */
    uint8_t *buf = appBuf;

    for(t=0;t<appSize;t+=2)
    {
        temp = (uint16_t)(buf[1]<<8);
        temp |= (uint16_t)buf[0];
        buf += 2;  /* 偏移2个字节 */
        iapBuf[i++] = temp;

        if(i == 1024)
        {
            i = 0;
            STMFLASH_Write(fwaddr, iapBuf, 1024);
            fwaddr += 2048;    /* 偏移2048  16=2*8.所以要乘以2. */
        }
    }

    if(i != 0)STMFLASH_Write(fwaddr, iapBuf, i);  /* 将最后的一些内容字节写进去. */
}



/**********************************************************
* @funcName ：IAP_Load_App
* @brief    ：执行指定地址的flash里面的app程序
* @param    ：uint32_t appAddr (指定flash地址)
* @retval   ：void
* @details  ：
* @fn       ：
************************************************************/
void IAP_Load_App(uint32_t appAddr)
{
    iapfun jumpApp;                    /* 函数指针 */

    /* 检查程序包 栈顶地址 是否合法. */
    if(((*(volatile uint32_t*)appAddr)&0x2FFE0000) == 0x20000000)
    {
        jumpApp = (iapfun)*(volatile uint32_t*)(appAddr+4);    /* 用户代码区第二个字为程序开始地址(复位地址) */
        MSR_MSP(*(volatile uint32_t*)appAddr);                 /* 初始化APP堆栈指针(用户代码区的第一个字用于存放栈顶地址) */
        jumpApp();                                             /* 跳转到APP. */
    }
}



