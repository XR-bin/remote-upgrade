#include "stm32f10x.h"
#include "usart.h"
#include "delay.h"
#include "key.h"
#include "led.h"
#include "stdio.h"

void LED_Test(void);     //LED����˸����
void Updata_Code(void);  //��ת��Bootloader����

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
	printf("�����µ��û�����\r\n");
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

//�򵥵�LED����˸
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


/*user������flash��ʼ��ַ*/
#define address_user_code_area		(0x08000000)
/*update������flash��ʼ��ַ*/
#define address_update_code_area	(0x0800a000)
/*boot������flash��ʼ��ַ*/
#define address_boot_code_area		(0x08014000)

/*���庯��ָ������ʵ�ִ�����л�*/
typedef void(*ptr_code)(void);
ptr_code ptr_boot=NULL;

//����ջ����ַ
//addr:ջ����ַ
__asm void MSR_MSP(u32 addr) 
{
    MSR MSP, r0 			//set Main Stack value
    BX r14
}

void Updata_Code(void)
{
	printf("����׼����ת��Bootloader\r\n");
	delay1_ms(10);//������ʱ��Ϊ�˱�֤����Ĵ�ӡ�ܹ��������ת
	/*����ָ��ָ��boot�����Reset_Handler*/
	ptr_boot=(ptr_code)(*(u32*)(address_boot_code_area+4));
	/*�ֶ�����boot�����ջ��λ��__initial_sp��SP�Ĵ�����*/
	MSR_MSP(*(u32*)address_boot_code_area);
	/*ͨ������ָ������л���boot����*/
	ptr_boot();
}


