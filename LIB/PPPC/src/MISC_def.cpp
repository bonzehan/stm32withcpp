#include "MISC_def.h"

namespace stm32
{
	void MY_NVIC_SetVectorTable(u32 NVIC_VectTab, u32 Offset)	 
	{ 
		//检查参数合法性
		assert_param(IS_NVIC_VECTTAB(NVIC_VectTab));
		assert_param(IS_NVIC_OFFSET(Offset));  	 
		SCB->VTOR = NVIC_VectTab|(Offset & (u32)0x1FFFFF80);//设置NVIC的向量表偏移寄存器
		//用于标识向量表是在CODE区还是在RAM区
	}
	void MYRCC_DeInit(void)
	{										  					   
		RCC->APB1RSTR = 0x00000000;//复位结束			 
		RCC->APB2RSTR = 0x00000000; 

		RCC->AHBENR = 0x00000014;  //flash时钟,闪存时钟使能.DMA时钟关闭	  
		RCC->APB2ENR = 0x00000000; //外设时钟关闭.			   
		RCC->APB1ENR = 0x00000000;   
		RCC->CR |= 0x00000001;     //使能内部高速时钟HSION	 															 
		RCC->CFGR &= 0xF8FF0000;   //复位SW[1:0],HPRE[3:0],PPRE1[2:0],PPRE2[2:0],ADCPRE[1:0],MCO[2:0]					 
		RCC->CR &= 0xFEF6FFFF;     //复位HSEON,CSSON,PLLON
		RCC->CR &= 0xFFFBFFFF;     //复位HSEBYP	   	  
		RCC->CFGR &= 0xFF80FFFF;   //复位PLLSRC, PLLXTPRE, PLLMUL[3:0] and USBPRE 
		RCC->CIR = 0x00000000;     //关闭所有中断
		//配置向量表				  
		#ifdef  VECT_TAB_RAM
		MY_NVIC_SetVectorTable(NVIC_VectTab_RAM, 0x0);
		#else   
		MY_NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x0);
		#endif
	}
	void Stm32_Clock_Init(u8 PLL)
	{
		unsigned char temp=0;   
		MYRCC_DeInit();			//复位并配置向量表
		RCC->CR|=0x00010000;	//使能外部高速时钟HSEON
		while(!(RCC->CR>>17));	//等待外部时钟就绪
		RCC->CFGR=0X00000400;	//APB1/2=DIV2;AHB=DIV1;
		PLL-=2;					//抵消2个单位
		RCC->CFGR|=PLL<<18;		//设置PLL值 2~16
		RCC->CFGR|=1<<16;		//PLLSRC ON，外部时钟作为PLL时钟
		FLASH->ACR|=0x32;		//FLASH 2个延时周期

		RCC->CR|=0x01000000;	//PLLON
		while(!(RCC->CR>>25));	//等待PLL锁定（wait PLL ready)
		RCC->CFGR|=0x00000002;	//PLL作为系统时钟	 
		while(temp!=0x02)		//等待PLL作为系统时钟设置成功
		{   
			temp=RCC->CFGR>>2;
			temp&=0x03;
		}    
	}	

}

namespace delay
{

	
	static u8  fac_us=0;//us延时倍乘数
	static u16 fac_ms=0;//ms延时倍乘数
	const u32 reload_value=0;

	
	void Init(void)
	{
		SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk;//关闭SYSTICK计数器
		SysTick->CTRL&=~SysTick_CTRL_TICKINT_Msk;//失能SYSTICK中断
		SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);//选择外部时钟 HCLK/8
		
		fac_us=SystemCoreClock/8000000;//为系统时钟的 1/8 =9
		fac_ms=(u16)fac_us*1000;//非 ucos 下,每个 ms 需要的 systick 时钟数
		//SystemCoreClock=SYSCLK_FREQ_72MHz=72000000
		SysTick->LOAD=9000;///////////////////////////设定重装值,1ms进入一次中断
		
		SysTick->CTRL|=SysTick_CTRL_TICKINT_Msk;//使能SYSTICK中断
		SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk;//开启SYSTICK计数器
	}
	
	void delay_us(u32 nus)
	{		
		SysTick->CTRL&=~SysTick_CTRL_TICKINT_Msk;//失能SYSTICK中断
		u32 temp;
		SysTick->LOAD=nus*fac_us; //时间加载	  		 
		SysTick->VAL=0x00;        //清空计数器
		SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk;          //开始倒数	 
		do{
			temp=SysTick->CTRL;
		}while(temp&0x01&&!(temp&(1<<16)));//等待时间到达
		
		SysTick->LOAD=9000;///////////////////////////设定重装值,1ms进入一次中断
		
		SysTick->VAL =0X00;       //清空计数器
		
		SysTick->CTRL|=SysTick_CTRL_TICKINT_Msk;//使能SYSTICK中断
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

