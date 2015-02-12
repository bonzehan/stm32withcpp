#include "USART_typedef.h"

using namespace rcc_reg;

namespace usartio
{
	void Init(void)
	{
		float temp;
		u16 mantissa;
		u16 fraction;	   
		temp=(float)(72*1000000)/(9600*16);//得到USARTDIV
		mantissa=temp;				 //得到整数部分
		fraction=(temp-mantissa)*16; //得到小数部分	 
		mantissa<<=4;
		mantissa+=fraction; 
		RCC->APB2ENR|=1<<2;   //使能PORTA口时钟  
		RCC->APB2ENR|=1<<14;  //使能串口时钟 
		GPIOA->CRH&=0XFFFFF00F;//IO状态设置
		GPIOA->CRH|=0X000008B0;//IO状态设置
		  
		RCC->APB2RSTR|=1<<14;   //复位串口1
		RCC->APB2RSTR&=~(1<<14);//停止复位	   	   
		//波特率设置
		USART1->BRR=mantissa; // 波特率设置	 
		USART1->CR1|=0X200C;  //1位停止,无校验位.
		
		#if EN_USART1_RX		  //如果使能了接收
		//使能接收中断
		USART1->CR1|=1<<8;    //PE中断使能
		USART1->CR1|=1<<5;    //接收缓冲区非空中断使能	    	
		MY_NVIC_Init(3,3,USART1_IRQn,2);//组2，最低优先级 
		#endif
	}

	void MY_NVIC_Init(u8 NVIC_PreemptionPriority,u8 NVIC_SubPriority,u8 NVIC_Channel,u8 NVIC_Group)	 
	{ 
		u32 temp;	
		u32 temp2,temp1;	  
		temp1=(~NVIC_Group)&0x07;//取后三位
		temp1<<=8;
		temp2=SCB->AIRCR;  //读取先前的设置
		temp2&=0X0000F8FF; //清空先前分组
		temp2|=0X05FA0000; //写入钥匙
		temp2|=temp1;	   
		SCB->AIRCR=temp2;  //设置分组	 
		temp=NVIC_PreemptionPriority<<(4-NVIC_Group);	  
		temp|=NVIC_SubPriority&(0x0f>>NVIC_Group);
		temp&=0xf;//取低四位  
		NVIC->ISER[NVIC_Channel/32]|=(1<<NVIC_Channel%32);//使能中断位(要清除的话,相反操作就OK) 
		NVIC->IP[NVIC_Channel]|=temp<<4;//设置响应优先级和抢断优先级   	    	  				   
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
	
	#if EN_USART1_RX   //如果使能了接收//串口1中断服务程序//注意,读取USARTx->SR能避免莫名其妙的错误
	u8 USART_RX_BUF[USART_REC_LEN];//接收缓冲,最大USART_REC_LEN个字节.//接收状态
	//bit15,接收完成标志
	//bit14,接收到0x0d
	//bit13~0,接收到的有效字节数目
	u16 USART_RX_STA=0;//接收状态标记	  
	
	#endif


}
