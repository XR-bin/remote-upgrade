#include "update.h"



/**
******************************************************************************
* @file      ��.\Middlewares\Update\update.c
*              .\Middlewares\Update\update.h
* @author    ��XRbin
* @version   ��V1.0
* @date      ��2023-12-14
* @brief     ����ת��Bootloader����
******************************************************************************
* @attention
*   �ҵ�GitHub   ��https://github.com/XR-bin
*   �ҵ�gitee    ��https://gitee.com/xrbin
*   �ҵ�leetcode ��https://leetcode.cn/u/xrbin/
******************************************************************************
*/



/**********************************************************
* @funcName ��Updata_Code
* @brief    �����뵽Bootloader������и��´���
* @param    ��void
* @retval   ��void
* @details  ��
* @fn       ��
************************************************************/
void Updata_Code(void)
{
    ptr_code ptr_boot=NULL;

    printf("����׼����ת��Bootloader......\r\n");
    delay_ms(100);     /* ������ʱ��Ϊ�˱�֤����Ĵ�ӡ�ܹ��������ת */

    /* ����ָ��ָ��boot�����Reset_Handler */
    ptr_boot=(ptr_code)(*(uint32_t*)(BOOT_CODE_ADDR+4));

    /* �ֶ�����boot�����ջ��λ��__initial_sp��SP�Ĵ����� */
    MSR_MSP(*(uint32_t*)BOOT_CODE_ADDR);

    /* ͨ������ָ������л���boot���� */
    ptr_boot();
}





