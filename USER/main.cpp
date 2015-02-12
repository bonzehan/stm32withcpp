#include "MISC_def.h"
#include "USART_typedef.h"
#include "RCC_typedef.h"

using namespace stm32;
using namespace delay;
using namespace usartio;
using namespace rcc_reg;
using namespace std;

int main(void)
{
	Stm32_Clock_Init(9);
	delay::Init();
	usartio::Init();
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	//设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	rcc_reg::Enable(GPIOAER);
	int* ptr=NULL;
	ptr=new int(9);
	if(ptr!=NULL)
		printf("\r\nnew successful\n\r");
	printf("%d",*ptr);
	delete ptr;
	if(ptr==NULL)
		printf("\r\ndelete successful\n\r");
	
	while(1)
	{
		msg("msg-\r\nHelloworld汉字\r\n");
		msgl("msgl-\r\nHelloworld汉字\r\n");
		write("write-\r\nHelloworld汉字\r\n");
		msg("msg-hello汉字");
		msgl("msgl-hello汉字");
		write("write-hello汉字");
		printf("%d",*ptr);
	}
}


