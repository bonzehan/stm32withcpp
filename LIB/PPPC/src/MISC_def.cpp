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
	
	void Init()
	{
		SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);//ѡ���ⲿʱ�� HCLK/8
		fac_us=SystemCoreClock/8000000;//Ϊϵͳʱ�ӵ� 1/8  
		
		#ifdef OS_CRITICAL_METHOD//���ʹ����ucosII
		u32 reload=SystemCoreClock/8000000;//ÿ���ӵļ�������,��λΪ K 
		reload*=1000000/OS_TICKS_PER_SEC;//���� OS_TICKS_PER_SEC �趨���ʱ��
		//reload Ϊ 24 λ�Ĵ���,���ֵ:16777216,�� 72M ��,Լ 1.86s ����
		fac_ms=1000/OS_TICKS_PER_SEC;//���� ucos ������ʱ�����ٵ�λ 
		SysTick->CTRL|=SysTick_CTRL_TICKINT_Msk;//���� SYSTICK �ж�
		SysTick->LOAD=reload;//ÿ 1/OS_TICKS_PER_SEC ���ж�һ��
		SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk;//���� SYSTICK
		
		#else
		fac_ms=(u16)fac_us*1000;//�� ucos ��,ÿ�� ms ��Ҫ�� systick ʱ���� 
		#endif
	}
	
	#ifdef OS_CRITICAL_METHOD//ʹ����ucos								   
	void delay_us(u32 nus)
	{		
		u32 ticks;
		u32 told,tnow,tcnt=0;
		u32 reload=SysTick->LOAD;	//LOAD��ֵ	    	 
		ticks=nus*fac_us; 			//��Ҫ�Ľ�����	  		 
		tcnt=0;
		told=SysTick->VAL;        	//�ս���ʱ�ļ�����ֵ
		while(1)
		{
			tnow=SysTick->VAL;	
			if(tnow!=told)
			{	    
				if(tnow<told)
					tcnt+=told-tnow;//����ע��һ��SYSTICK��һ���ݼ��ļ������Ϳ�����.
				else 
					tcnt+=reload-tnow+told;	    
				told=tnow;
				if(tcnt>=ticks)
					break;//ʱ�䳬��/����Ҫ�ӳٵ�ʱ��,���˳�.
			}  
		}								    
	}
	void delay_ms(u16 nms)
	{	
		if(OSRunning==TRUE)//���os�Ѿ�������	    
		{		  
			if(nms>=fac_ms)//��ʱ��ʱ�����ucos������ʱ������ 
			{
				OSTimeDly(nms/fac_ms);//ucos��ʱ
			}
			nms%=fac_ms;				//ucos�Ѿ��޷��ṩ��ôС����ʱ��,������ͨ��ʽ��ʱ    
		}
		delay_us((u32)(nms*1000));	//��ͨ��ʽ��ʱ,��ʱucos�޷���������.
	}
	#else
	void delay_us(u32 nus)
	{		
		u32 temp;	    	 
		SysTick->LOAD=nus*fac_us; //ʱ�����	  		 
		SysTick->VAL=0x00;        //��ռ�����
		SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk ;          //��ʼ����	 
		do{
			temp=SysTick->CTRL;
		}while(temp&0x01&&!(temp&(1<<16)));//�ȴ�ʱ�䵽��   
		SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk;       //�رռ�����
		SysTick->VAL =0X00;       //��ռ�����	 
	}
	void delay_ms(u16 nms)
	{	 		  	  
		u32 temp;
		//if(nms*SystemCoreClock>134217720000)
			//nms=134217720000/SystemCoreClock;
		//SysTick->LOADΪ24λ�Ĵ���,�����ʱn<=0xffffff*8*1000/SYSCLK(Hz)��72M,n<=1864(ms)
		SysTick->LOAD=(u32)nms*fac_ms;//ʱ�����(SysTick->LOADΪ24bit)
		SysTick->VAL =0x00;           //��ռ�����
		SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk ;          //��ʼ����  
		do{
			temp=SysTick->CTRL;
		}while(temp&0x01&&!(temp&(1<<16)));//�ȴ�ʱ�䵽��   
		SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk;       //�رռ�����
		SysTick->VAL =0X00;       //��ռ�����	  	    
	} 
	#endif
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

