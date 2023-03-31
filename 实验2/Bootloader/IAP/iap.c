#include "stm32f10x.h"
#include "iap.h"
#include "stmflash.h"
#include "stdio.h"


u16 iapbuf[1024];   //������
iapfun jump2app;    //����ָ��
/******************************************************************
*��������  �������³���д��ָ����ַ��flash
*������    ��iap_write_appbin
*��������  ��u32 appxaddr(ָ����ַ),u8 *appbuf(���³����),u32 appsize(�������С)
*��������ֵ��void
*����      ��
*******************************************************************/
void iap_write_appbin(u32 appxaddr,u8 *appbuf,u32 appsize)
{
	u16 t;
	u16 i=0;
	u16 temp;
	u32 fwaddr=appxaddr;//��ǰд��ĵ�ַ
	u8 *dfu=appbuf;
	
	for(t=0;t<appsize;t+=2)
	{						    
		temp=(u16)dfu[1]<<8;
		temp+=(u16)dfu[0];	  
		dfu+=2;//ƫ��2���ֽ�
		iapbuf[i++]=temp;	    
		if(i==1024)
		{
			i=0;
			STMFLASH_Write(fwaddr,iapbuf,1024);	
			fwaddr+=2048;//ƫ��2048  16=2*8.����Ҫ����2.
		}
	}
	if(i)STMFLASH_Write(fwaddr,iapbuf,i);//������һЩ�����ֽ�д��ȥ. 
}

//����ջ����ַ
//addr:ջ����ַ
__asm void MSR_MSP(u32 addr) 
{
    MSR MSP, r0 			//set Main Stack value
    BX r14
}

/******************************************************************
*��������  ��ִ��ָ����ַ��flash�����app����
*������    ��iap_load_app
*��������  ��u32 appxaddr(ָ��flash��ַ)
*��������ֵ��void
*����      ��
*******************************************************************/
void iap_load_app(u32 appxaddr)
{
	if(((*(vu32*)appxaddr)&0x2FFE0000)==0x20000000)	//���ջ����ַ�Ƿ�Ϸ�.
	{ 
		jump2app=(iapfun)*(vu32*)(appxaddr+4);		//�û��������ڶ�����Ϊ����ʼ��ַ(��λ��ַ)		
		MSR_MSP(*(vu32*)appxaddr);					//��ʼ��APP��ջָ��(�û��������ĵ�һ�������ڴ��ջ����ַ)
		jump2app();									//��ת��APP.
	}
}



