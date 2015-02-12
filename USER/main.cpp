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
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	//����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
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
		msg("msg-\r\nHelloworld����\r\n");
		msgl("msgl-\r\nHelloworld����\r\n");
		write("write-\r\nHelloworld����\r\n");
		msg("msg-hello����");
		msgl("msgl-hello����");
		write("write-hello����");
		printf("%d",*ptr);
	}
}


