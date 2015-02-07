#include "stm32f10x.h"
#include "MISC_def.h"

using namespace delay;

//void Delay(u32 count)
//{
//u32 i=0;
//for(;i<count;i++);
//}
//class C_box
//{
//	double m_length;
//	bool enable;
//	
//};
int main(void)
{
	delay::Init();
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOD,ENABLE);    //ʹ�� PA,PD �˿�ʱ��
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;        //LED0-->PA.8  �˿�����
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;        //�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;      //IO ���ٶ�Ϊ 50MHz 
	GPIO_Init(GPIOA, &GPIO_InitStructure);      //�����趨������ʼ�� GPIOA.8
	GPIO_SetBits(GPIOA,GPIO_Pin_8);              //PA.8  �����
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;    //LED1-->PD.2  �˿�����,  �������
	GPIO_Init(GPIOD, &GPIO_InitStructure);        //�������  ��IO ���ٶ�Ϊ 50MHz
	GPIO_SetBits(GPIOD,GPIO_Pin_2);          //PD.2  �����   
	while(1)
	{
		GPIO_ResetBits(GPIOA,GPIO_Pin_8);
		GPIO_SetBits(GPIOD,GPIO_Pin_2);
		delay::delay_ms(100);
		GPIO_SetBits(GPIOA,GPIO_Pin_8);
		GPIO_ResetBits(GPIOD,GPIO_Pin_2);
		delay::delay_ms(100);
	}
}
