#ifndef _IAP_H
#define _IAP_H

	#include "stm32f10x.h"
	
	typedef  void (*iapfun)(void);				//����һ���������͵Ĳ���.
	
	#define FLASH_APP1_ADDR		0x08000000  	//��һ��Ӧ�ó�����ʼ��ַ(�����FLASH)
											                    //����0X08000000~0X0800FFFF�Ŀռ�ΪIAPʹ��
																					
	void iap_load_app(u32 appxaddr);			                      //ִ��flash�����app����
	void iap_write_appbin(u32 appxaddr,u8 *appbuf,u32 applen);	//��ָ����ַ��ʼ,д��bin

#endif
