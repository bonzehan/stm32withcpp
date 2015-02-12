#ifndef USART_TYPEDEF_H
#define USART_TYPEDEF_H

#include "stm32f10x.h"
#include "RCC_typedef.h"
#include "stm32f10x_usart.h"

namespace usartio
{
	void Init(void);
	void MY_NVIC_Init(u8 NVIC_PreemptionPriority,u8 NVIC_SubPriority,u8 NVIC_Channel,u8 NVIC_Group);

	//int sendchar(int ch);
	void write(const char* msge);
	void msg(const char* msge);
	void msgl(const char* msge);
	
	class usart_conf_val
	{
		public:
			unsigned char PCLK2;//PCLK2��ʱ��Ƶ�ʣ�72��MHz����
			u16 baudrate;//maxu16=65535��������
			unsigned char wordlen;//����λ���ȣ�8��
			unsigned char stopbit;//ֹͣλ��1��
			unsigned char parity;//У��λ��0��
			unsigned char HFC;//HardwareFlowControl��Ӳ�������ƣ���ֹ0��
			unsigned char mode;//ģʽ������1����2˫��3��
					
		usart_conf_val(unsigned char pclk2=72,u16 baud=9600,unsigned char wl=8,unsigned char stb=1,
			unsigned char par=0,unsigned char hfc=0,unsigned char mode=3):
			PCLK2(pclk2),baudrate(baud),wordlen(wl),stopbit(stb),parity(par),HFC(hfc),mode(mode){}//Ĭ�Ϲ��캯��
		
		float getdiv()
		{
			return (PCLK2*1000000)/(baudrate*16);
		}
	};
	
	
}
#endif
