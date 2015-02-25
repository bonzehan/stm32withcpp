#include "MISC_def.h"

namespace stm32
{
	void MY_NVIC_SetVectorTable(u32 NVIC_VectTab, u32 Offset)	 
	{ 
		//�������Ϸ���
		assert_param(IS_NVIC_VECTTAB(NVIC_VectTab));
		assert_param(IS_NVIC_OFFSET(Offset));  	 
		SCB->VTOR = NVIC_VectTab|(Offset & (u32)0x1FFFFF80);//����NVIC��������ƫ�ƼĴ���
		//���ڱ�ʶ����������CODE��������RAM��
	}
	void MYRCC_DeInit(void)
	{										  					   
		RCC->APB1RSTR = 0x00000000;//��λ����			 
		RCC->APB2RSTR = 0x00000000; 

		RCC->AHBENR = 0x00000014;  //flashʱ��,����ʱ��ʹ��.DMAʱ�ӹر�	  
		RCC->APB2ENR = 0x00000000; //����ʱ�ӹر�.			   
		RCC->APB1ENR = 0x00000000;   
		RCC->CR |= 0x00000001;     //ʹ���ڲ�����ʱ��HSION	 															 
		RCC->CFGR &= 0xF8FF0000;   //��λSW[1:0],HPRE[3:0],PPRE1[2:0],PPRE2[2:0],ADCPRE[1:0],MCO[2:0]					 
		RCC->CR &= 0xFEF6FFFF;     //��λHSEON,CSSON,PLLON
		RCC->CR &= 0xFFFBFFFF;     //��λHSEBYP	   	  
		RCC->CFGR &= 0xFF80FFFF;   //��λPLLSRC, PLLXTPRE, PLLMUL[3:0] and USBPRE 
		RCC->CIR = 0x00000000;     //�ر������ж�
		//����������				  
		#ifdef  VECT_TAB_RAM
		MY_NVIC_SetVectorTable(NVIC_VectTab_RAM, 0x0);
		#else   
		MY_NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x0);
		#endif
	}
	void Stm32_Clock_Init(u8 PLL)
	{
		unsigned char temp=0;   
		MYRCC_DeInit();			//��λ������������
		RCC->CR|=0x00010000;	//ʹ���ⲿ����ʱ��HSEON
		while(!(RCC->CR>>17));	//�ȴ��ⲿʱ�Ӿ���
		RCC->CFGR=0X00000400;	//APB1/2=DIV2;AHB=DIV1;
		PLL-=2;					//����2����λ
		RCC->CFGR|=PLL<<18;		//����PLLֵ 2~16
		RCC->CFGR|=1<<16;		//PLLSRC ON���ⲿʱ����ΪPLLʱ��
		FLASH->ACR|=0x32;		//FLASH 2����ʱ����

		RCC->CR|=0x01000000;	//PLLON
		while(!(RCC->CR>>25));	//�ȴ�PLL������wait PLL ready)
		RCC->CFGR|=0x00000002;	//PLL��Ϊϵͳʱ��	 
		while(temp!=0x02)		//�ȴ�PLL��Ϊϵͳʱ�����óɹ�
		{   
			temp=RCC->CFGR>>2;
			temp&=0x03;
		}    
	}	

}

namespace delay
{

	
	static u8  fac_us=0;//us��ʱ������
	static u16 fac_ms=0;//ms��ʱ������
	const u32 reload_value=0;

	
	void Init(void)
	{
		SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk;//�ر�SYSTICK������
		SysTick->CTRL&=~SysTick_CTRL_TICKINT_Msk;//ʧ��SYSTICK�ж�
		SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);//ѡ���ⲿʱ�� HCLK/8
		
		fac_us=SystemCoreClock/8000000;//Ϊϵͳʱ�ӵ� 1/8 =9
		fac_ms=(u16)fac_us*1000;//�� ucos ��,ÿ�� ms ��Ҫ�� systick ʱ����
		//SystemCoreClock=SYSCLK_FREQ_72MHz=72000000
		SysTick->LOAD=9000;///////////////////////////�趨��װֵ,1ms����һ���ж�
		
		SysTick->CTRL|=SysTick_CTRL_TICKINT_Msk;//ʹ��SYSTICK�ж�
		SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk;//����SYSTICK������
	}
	
	void delay_us(u32 nus)
	{		
		SysTick->CTRL&=~SysTick_CTRL_TICKINT_Msk;//ʧ��SYSTICK�ж�
		u32 temp;
		SysTick->LOAD=nus*fac_us; //ʱ�����	  		 
		SysTick->VAL=0x00;        //��ռ�����
		SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk;          //��ʼ����	 
		do{
			temp=SysTick->CTRL;
		}while(temp&0x01&&!(temp&(1<<16)));//�ȴ�ʱ�䵽��
		
		SysTick->LOAD=9000;///////////////////////////�趨��װֵ,1ms����һ���ж�
		
		SysTick->VAL =0X00;       //��ռ�����
		
		SysTick->CTRL|=SysTick_CTRL_TICKINT_Msk;//ʹ��SYSTICK�ж�
	}
	void delay_ms(u32 nms)
	{	
		u32 temp=ms_RunTime;
		u32* tmptr=NULL;
		if((nms+ms_RunTime)>0x80000000)
		{
			tmptr=new u32(nms+ms_RunTime-0x80000000);
			do{
			}while(ms_RunTime<*tmptr);
			delete tmptr;
			return;
		}
		temp+=nms;
		do{
		}while(ms_RunTime<temp);
		return; 	    
	} 
}

void *operator new(size_t size) 
{
	return malloc(size);
} 
void *operator new[](size_t size) 
{
	return malloc(size);
} 
void operator delete(void *p) 
{
	free(p);
} 
void operator delete[](void *p) 
{
	free(p);
}

