#ifndef MISC_TYPEDEF
#define MISC_TYPEDEF

#include "stm32f10x.h"
#include "stdio.h"
#include "stdlib.h"

/*������ʱ����*/
namespace delay
{
	void Init();
	void delay_ms(u16 nms);
	void delay_us(u32 nus);
}

/*��ʼ��STM32��ʱ��*/
namespace stm32
{
	void MY_NVIC_SetVectorTable(u32 NVIC_VectTab, u32 Offset);
	void MYRCC_DeInit(void);
	void Stm32_Clock_Init(u8 PLL);
}

/*����new��delete�����*/
void *operator new(size_t size);
void *operator new[](size_t size);
void operator delete(void *p);
void operator delete[](void *p);
 

	
#endif
