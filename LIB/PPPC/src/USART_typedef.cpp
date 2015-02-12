#include "USART_typedef.h"

using namespace rcc_reg;

namespace usartio
{
	void Init(void)
	{
		float temp;
		u16 mantissa;
		u16 fraction;	   
		temp=(float)(72*1000000)/(9600*16);//�õ�USARTDIV
		mantissa=temp;				 //�õ���������
		fraction=(temp-mantissa)*16; //�õ�С������	 
		mantissa<<=4;
		mantissa+=fraction; 
		RCC->APB2ENR|=1<<2;   //ʹ��PORTA��ʱ��  
		RCC->APB2ENR|=1<<14;  //ʹ�ܴ���ʱ�� 
		GPIOA->CRH&=0XFFFFF00F;//IO״̬����
		GPIOA->CRH|=0X000008B0;//IO״̬����
		  
		RCC->APB2RSTR|=1<<14;   //��λ����1
		RCC->APB2RSTR&=~(1<<14);//ֹͣ��λ	   	   
		//����������
		USART1->BRR=mantissa; // ����������	 
		USART1->CR1|=0X200C;  //1λֹͣ,��У��λ.
		
		#if EN_USART1_RX		  //���ʹ���˽���
		//ʹ�ܽ����ж�
		USART1->CR1|=1<<8;    //PE�ж�ʹ��
		USART1->CR1|=1<<5;    //���ջ������ǿ��ж�ʹ��	    	
		MY_NVIC_Init(3,3,USART1_IRQn,2);//��2��������ȼ� 
		#endif
	}

	void MY_NVIC_Init(u8 NVIC_PreemptionPriority,u8 NVIC_SubPriority,u8 NVIC_Channel,u8 NVIC_Group)	 
	{ 
		u32 temp;	
		u32 temp2,temp1;	  
		temp1=(~NVIC_Group)&0x07;//ȡ����λ
		temp1<<=8;
		temp2=SCB->AIRCR;  //��ȡ��ǰ������
		temp2&=0X0000F8FF; //�����ǰ����
		temp2|=0X05FA0000; //д��Կ��
		temp2|=temp1;	   
		SCB->AIRCR=temp2;  //���÷���	 
		temp=NVIC_PreemptionPriority<<(4-NVIC_Group);	  
		temp|=NVIC_SubPriority&(0x0f>>NVIC_Group);
		temp&=0xf;//ȡ����λ  
		NVIC->ISER[NVIC_Channel/32]|=(1<<NVIC_Channel%32);//ʹ���ж�λ(Ҫ����Ļ�,�෴������OK) 
		NVIC->IP[NVIC_Channel]|=temp<<4;//������Ӧ���ȼ����������ȼ�   	    	  				   
	}
	
//	int sendchar(int ch)
//	{
//		while((USART1->SR&0X40)==0);
//		return (USART1->DR=(u8)ch);
//	}
	void write(const char* msge)
	{
		while(*msge!='\0')
		{
			while((USART1->SR&0X40)==0);
			USART1->DR=(u8)(*msge);
			++msge;
		}
	}
	void msg(const char* msge)
	{
		while(*msge!='\0')
		{
			switch(*msge)
			{
				case '\n':while((USART1->SR&0X40)==0);USART1->DR=0x0D;break;
				case '\r':while((USART1->SR&0X40)==0);USART1->DR=0x0A;break;
				default:while((USART1->SR&0X40)==0);USART1->DR=(u8)(*msge);break;
			}
			++msge;		
		}
	}
	void msgl(const char* msge)
	{
		while((USART1->SR&0X40)==0);
			USART1->DR=0x0A;
		while(*msge!='\0')
		{
			switch(*msge)
			{
				case '\n':while((USART1->SR&0X40)==0);USART1->DR=0x0D;break;
				case '\r':while((USART1->SR&0X40)==0);USART1->DR=0x0A;break;
				default:while((USART1->SR&0X40)==0);USART1->DR=(u8)(*msge);break;
			}
			++msge;		
		}
		while((USART1->SR&0X40)==0);
			USART1->DR=0x0A;
	}
	
	#if EN_USART1_RX   //���ʹ���˽���//����1�жϷ������//ע��,��ȡUSARTx->SR�ܱ���Ī������Ĵ���
	u8 USART_RX_BUF[USART_REC_LEN];//���ջ���,���USART_REC_LEN���ֽ�.//����״̬
	//bit15,������ɱ�־
	//bit14,���յ�0x0d
	//bit13~0,���յ�����Ч�ֽ���Ŀ
	u16 USART_RX_STA=0;//����״̬���	  
	
	#endif


}
