#ifndef MISC_TYPEDEF
#define MISC_TYPEDEF

#include "stm32f10x.h"
#include "stdio.h"
#include "stdlib.h"

/*关于延时函数*/
namespace delay
{
	void Init();
	void delay_ms(u16 nms);
	void delay_us(u32 nus);
}

/*初始化STM32的时钟*/
namespace stm32
{
	void MY_NVIC_SetVectorTable(u32 NVIC_VectTab, u32 Offset);
	void MYRCC_DeInit(void);
	void Stm32_Clock_Init(u8 PLL);
}

/*重载new和delete运算符*/
void *operator new(size_t size);
void *operator new[](size_t size);
void operator delete(void *p);
void operator delete[](void *p);
 

	
#endif
