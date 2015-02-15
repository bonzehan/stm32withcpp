#include "MISC_def.h"
#include "USART_typedef.h"
#include "RCC_typedef.h"
#include "GPIO_typedef.h"

using namespace stm32;
using namespace delay;
using namespace usartio;
using namespace rcc_reg;
using namespace gpio;

int main(void)
{
	Stm32_Clock_Init(9);
	delay::Init();
	usartio::Init();
//	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	//设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	rcc_reg::Enable(GPIOAER);
	gpio_conf PA1(GPIOA,OUT_OP,P1);
	gpio_conf PA2(GPIOA,OUT_OP,P2|P3);
//	gpio_conf PA14(GPIOA,OUT_OP,P1|P4);
	PA1.Init();
	PA2.Init();
//	PA14.Init();
	PA1.port(P1,1);
	delay_ms(100);
	printf("start\n\r");
	int count=0;
	while(1)
	{
		PA1=1;
		printf("PA1.BITS= %d\n\r",PA1.BITS);
		delay_ms(500);
		PA2=1;
		printf("PA2.BITS= %d\n\r",PA2.BITS);
		delay_ms(500);

		PA2=0;
		delay_ms(500);
		PA1=0;
		printf("\n循环 %d 完成\n\r",++count);
		delay_ms(500);
		
	}
}


