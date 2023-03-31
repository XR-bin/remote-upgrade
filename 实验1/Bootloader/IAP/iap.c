#include "stm32f10x.h"
#include "iap.h"
#include "stmflash.h"
#include "stdio.h"


u16 iapbuf[1024];   //缓存区
iapfun jump2app;    //函数指针
/******************************************************************
*函数功能  ：将更新程序写入指定地址的flash
*函数名    ：iap_write_appbin
*函数参数  ：u32 appxaddr(指定地址),u8 *appbuf(更新程序包),u32 appsize(程序包大小)
*函数返回值：void
*描述      ：
*******************************************************************/
void iap_write_appbin(u32 appxaddr,u8 *appbuf,u32 appsize)
{
	u16 t;
	u16 i=0;
	u16 temp;
	u32 fwaddr=appxaddr;//当前写入的地址
	u8 *dfu=appbuf;
	
	for(t=0;t<appsize;t+=2)
	{						    
		temp=(u16)dfu[1]<<8;
		temp+=(u16)dfu[0];	  
		dfu+=2;//偏移2个字节
		iapbuf[i++]=temp;	    
		if(i==1024)
		{
			i=0;
			STMFLASH_Write(fwaddr,iapbuf,1024);	
			fwaddr+=2048;//偏移2048  16=2*8.所以要乘以2.
		}
	}
	if(i)STMFLASH_Write(fwaddr,iapbuf,i);//将最后的一些内容字节写进去. 
}

//设置栈顶地址
//addr:栈顶地址
__asm void MSR_MSP(u32 addr) 
{
    MSR MSP, r0 			//set Main Stack value
    BX r14
}

/******************************************************************
*函数功能  ：执行指定地址的flash里面的app程序
*函数名    ：iap_load_app
*函数参数  ：u32 appxaddr(指定flash地址)
*函数返回值：void
*描述      ：
*******************************************************************/
void iap_load_app(u32 appxaddr)
{
	if(((*(vu32*)appxaddr)&0x2FFE0000)==0x20000000)	//检查栈顶地址是否合法.
	{ 
		jump2app=(iapfun)*(vu32*)(appxaddr+4);		//用户代码区第二个字为程序开始地址(复位地址)		
		MSR_MSP(*(vu32*)appxaddr);					//初始化APP堆栈指针(用户代码区的第一个字用于存放栈顶地址)
		jump2app();									//跳转到APP.
	}
}



