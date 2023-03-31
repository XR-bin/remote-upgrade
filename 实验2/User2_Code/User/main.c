#include "stm32f10x.h"
#include "usart.h"
#include "delay.h"
#include "key.h"
#include "led.h"
#include "stdio.h"

void LED_Test(void);     //LED灯闪烁函数
void Updata_Code(void);  //跳转到Bootloader函数

int main(void)
{
	u8 key=0;
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	USART1_Init(115200);
	SysTick_Init();
	KEY_Init();
	LED_Init();
	LED0_OFF;
	LED1_OFF;
	printf("进入新的用户程序\r\n");
	while(1)
	{
		key = KEY_Scan();
		
		if(key == 3)
		{
			Updata_Code();
		}
		
		LED_Test();
		
		delay1_ms(10);
	}
}

//简单的LED灯闪烁
void LED_Test(void)
{
	static u16 i=0;
	
	i++;
	if(i==80)
	{
		i=0;
		GPIOE->ODR ^= (1<<5);
	}
}


/*user代码区flash起始地址*/
#define address_user_code_area		(0x08000000)
/*update代码区flash起始地址*/
#define address_update_code_area	(0x0800a000)
/*boot代码区flash起始地址*/
#define address_boot_code_area		(0x08014000)

/*定义函数指针用于实现代码的切换*/
typedef void(*ptr_code)(void);
ptr_code ptr_boot=NULL;

//设置栈顶地址
//addr:栈顶地址
__asm void MSR_MSP(u32 addr) 
{
    MSR MSP, r0 			//set Main Stack value
    BX r14
}

void Updata_Code(void)
{
	printf("程序准备跳转到Bootloader\r\n");
	delay1_ms(10);//这里延时是为了保证上面的打印能够完成再跳转
	/*函数指针指向boot代码的Reset_Handler*/
	ptr_boot=(ptr_code)(*(u32*)(address_boot_code_area+4));
	/*手动加载boot代码的栈顶位置__initial_sp到SP寄存器中*/
	MSR_MSP(*(u32*)address_boot_code_area);
	/*通过函数指针调用切换到boot代码*/
	ptr_boot();
}


