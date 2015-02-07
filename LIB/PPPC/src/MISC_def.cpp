#include"stm32f10x.h"
#include"MISC_def.h"

namespace delay
{
	static u8  fac_us=0;//us延时倍乘数
	static u16 fac_ms=0;//ms延时倍乘数
	
	void Init()
	{
		SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);//选择外部时钟 HCLK/8
		fac_us=SystemCoreClock/8000000;//为系统时钟的 1/8  
		
		#ifdef OS_CRITICAL_METHOD//如果使用了ucosII
		u32 reload=SystemCoreClock/8000000;//每秒钟的计数次数,单位为 K 
		reload*=1000000/OS_TICKS_PER_SEC;//根据 OS_TICKS_PER_SEC 设定溢出时间
		//reload 为 24 位寄存器,最大值:16777216,在 72M 下,约 1.86s 左右
		fac_ms=1000/OS_TICKS_PER_SEC;//代表 ucos 可以延时的最少单位 
		SysTick->CTRL|=SysTick_CTRL_TICKINT_Msk;//开启 SYSTICK 中断
		SysTick->LOAD=reload;//每 1/OS_TICKS_PER_SEC 秒中断一次
		SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk;//开启 SYSTICK
		
		#else
		fac_ms=(u16)fac_us*1000;//非 ucos 下,每个 ms 需要的 systick 时钟数 
		#endif
	}
	
	#ifdef OS_CRITICAL_METHOD//使用了ucos								   
	void delay_us(u32 nus)
	{		
		u32 ticks;
		u32 told,tnow,tcnt=0;
		u32 reload=SysTick->LOAD;	//LOAD的值	    	 
		ticks=nus*fac_us; 			//需要的节拍数	  		 
		tcnt=0;
		told=SysTick->VAL;        	//刚进入时的计数器值
		while(1)
		{
			tnow=SysTick->VAL;	
			if(tnow!=told)
			{	    
				if(tnow<told)
					tcnt+=told-tnow;//这里注意一下SYSTICK是一个递减的计数器就可以了.
				else 
					tcnt+=reload-tnow+told;	    
				told=tnow;
				if(tcnt>=ticks)
					break;//时间超过/等于要延迟的时间,则退出.
			}  
		}								    
	}
	void delay_ms(u16 nms)
	{	
		if(OSRunning==TRUE)//如果os已经在跑了	    
		{		  
			if(nms>=fac_ms)//延时的时间大于ucos的最少时间周期 
			{
				OSTimeDly(nms/fac_ms);//ucos延时
			}
			nms%=fac_ms;				//ucos已经无法提供这么小的延时了,采用普通方式延时    
		}
		delay_us((u32)(nms*1000));	//普通方式延时,此时ucos无法启动调度.
	}
	#else
	void delay_us(u32 nus)
	{		
		u32 temp;	    	 
		SysTick->LOAD=nus*fac_us; //时间加载	  		 
		SysTick->VAL=0x00;        //清空计数器
		SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk ;          //开始倒数	 
		do{
			temp=SysTick->CTRL;
		}while(temp&0x01&&!(temp&(1<<16)));//等待时间到达   
		SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk;       //关闭计数器
		SysTick->VAL =0X00;       //清空计数器	 
	}
	void delay_ms(u16 nms)
	{	 		  	  
		u32 temp;
		//if(nms*SystemCoreClock>134217720000)
			//nms=134217720000/SystemCoreClock;
		//SysTick->LOAD为24位寄存器,最大延时n<=0xffffff*8*1000/SYSCLK(Hz)对72M,n<=1864(ms)
		SysTick->LOAD=(u32)nms*fac_ms;//时间加载(SysTick->LOAD为24bit)
		SysTick->VAL =0x00;           //清空计数器
		SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk ;          //开始倒数  
		do{
			temp=SysTick->CTRL;
		}while(temp&0x01&&!(temp&(1<<16)));//等待时间到达   
		SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk;       //关闭计数器
		SysTick->VAL =0X00;       //清空计数器	  	    
	} 
	#endif
}
