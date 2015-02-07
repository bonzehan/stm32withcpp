#include"stm32f10x.h"
#include"MISC_def.h"

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
