#include"stm32f10x.h"

#ifndef MISC_TYPEDEF
#define MISC_TYPEDEF

namespace delay
{
	void Init();
	void delay_ms(u16 nms);
	void delay_us(u32 nus);
}

#endif
