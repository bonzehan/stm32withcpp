#include "RCC_typedef.h"

namespace rcc_reg
{
//	enum{
//		TIM2ER=0,TIM3ER=1,TIM4ER,TIM5ER,TIM6ER,TIM7ER,
//		WWDGER=11,
//		SPI2ER=14,SPI3ER=15,
//		USART2ER=17,USART3ER,USART4ER,USART5ER,I2C1ER=21,I2C2ER=22,USBER=23,
//		CANER=25,
//		BKPER=27,PWRER=28,DACER=29,
//		AFIOER=32,
//		GPIOAER=34,GPIOBER,GPIOCER,GPIODER,GPIOEER,GPIOFER,GPIOGER,
//		ADC1ER=41,ADC2ER=42,TIM1ER=43,SPI1ER=44,TIM8ER=45,USART1ER=46,ADC3ER=47
//	};//用于APB1和APB2外设复位寄存器和外设时钟使能寄存器，对于APB1外设，相应值为位号，对于APB2外设，相应值为位号+32
//	enum{
//		DMA1E=64,DMA2E,SRAME,
//		FLITFE=68,
//		CRCE=70,
//		FSMCE=72,
//		SDIOE=74
//	};//用于AHB外设时钟使能寄存器，相应值为位号+64
	
//	u32 CR=0x00000083;
//	u32 CFRG=0x00000000;
//	u32 CIR=0x00000000;
//	u32 APB2RSTR=0x00000000;
//	u32 APB1RSTR=0x00000000;
//	u32 AHBENR=0x00000014;
//	u32 APB2ENR=0x00000000;
//	u32 APB1ENR=0x00000000;
//	u32 BDCR=0x00000000;
//	u32 CSR=0x0C000000;


	void Enable(int ppp_bit)
	{
		if(ppp_bit<32)
		{
			RCC->APB1ENR |= 1<<(ppp_bit);
		}
		else if(ppp_bit<64)
		{
			RCC->APB2ENR |= 1<<(ppp_bit-32);
		}
		else
		{
			RCC->AHBENR |= 1<<(ppp_bit-64);
		}
	}
	void Reset(int ppp_bit)
	{
		if(ppp_bit<32)
		{
			RCC->APB1RSTR |= 1<<(ppp_bit);
		}
		else if(ppp_bit<64)
		{
			RCC->APB2RSTR |= 1<<(ppp_bit-32);
		}
	}
		
	void Init(int ppp_bit,int enable)
	{
	
	}

//	void DeInit()
//	{
//		CR=0x00000083;
//		CFRG=0x00000000;
//		CIR=0x00000000;
//		APB2RSTR=0x00000000;
//		APB1RSTR=0x00000000;
//		AHBENR=0x00000014;
//		APB2ENR=0x00000000;
//		APB1ENR=0x00000000;
//		BDCR=0x00000000;
//		CSR=0x0C000000;
//	}
	void Config();
	
}



//namespace periph{
//	namespace rcc_reg{
//			
//			/**	@brief	设置 AHB 时钟预分频器
//			*	@param	div: 设置分频系数，参数可以是1, 2, 4, 8, 16, ..., 512
//			*/
//			void RCC_Struct::SetAHB_Prescaler(u8 div)
//			{
//				u8 temp = 0;
//				if(div != 1)
//				{
//					temp = BByte(1000);
//					div >>= 2;
//					while(div)
//					{
//						temp++;
//						div >>= 1;
//					}
//				}
//				CFGR = assignf(CFGR, HPRE, temp);
//			}
//			
//			/**	@brief	设置 APB2 时钟预分频器
//			*	@param	div:	设置分频系数，参数可以是1, 2, 4, 8, 16
//			*/
//			void RCC_Struct::SetAPB2_Prescaler(u8 div)
//			{
//				u8 temp = 0;
//				if(div != 1)
//				{
//					temp = BByte(100);
//					div >>= 2;
//					while(div)
//					{
//						temp++;
//						div >>= 1;
//					}
//				}
//				CFGR = assignf(CFGR, PPRE2, temp);
//			}
//			
//			void RCC_Struct::SetAPB1_Prescaler(u8 div)
//			{
//				u8 temp = 0;
//				if(div != 1)
//				{
//					temp = BByte(100);
//					div >>= 2;
//					while(div)
//					{
//						temp++;
//						div >>= 1;
//					}
//				}
//				CFGR = assignf(CFGR, PPRE1, temp);
//			}
//			
//			u8 RCC_Struct::GetAPB1_Prescaler()
//			{
//				u8 pre1 = readf(CFGR, PPRE1);
//				u8 ret = (pre1&BByte(100) != 0)? 2 :1;
//				pre1 &= BByte(011);
//				while(pre1)
//				{
//					ret <<= 1;	// ret *= 2;
//					pre1--;
//				}
//				return ret;
//			}
//			
//			void RCC_Struct::DeInit()
//			{
//				APB1RSTR = 0x00000000;			 
//				APB2RSTR = 0x00000000; 
//				APB2ENR = 0x00000000; //外设时钟关闭.			   
//				APB1ENR = 0x00000000;
//				
//				AHBENR = PERIPH_FLITF | PERIPH_SRAM;	// flash时钟,闪存时钟使能.DMA时钟关闭	
//				
//				CIR = 0x00000000;						// 关闭所有中断			
//				
//				ClockControl(HSI, ENABLE);				// 使能内部高速时钟HSION	
//				while(!IsHSI_Ready());					// 等待 HSI 就绪
//				
//				SetClockOutput(NO_CLOCK);				// 没有时钟输出
//				SysclkSwitch(HSI_AS_SYSCLK);			// 切换 HSI 为系统时钟
//				SetADC_Prescaler(2);
//				SetAPB1_Prescaler(1);
//				SetAPB2_Prescaler(1);
//				SetAHB_Prescaler(1);
//				SetUSB_Prescaler(PLL_DIV_1D5);
//				while( HSI_AS_SYSCLK != GetSysclkSwitchStatus());
//				
//				ClockControl(CLOCK_SECURITY_SYSTEM, DISABLE);
//				ClockControl(PLL, DISABLE);
//				ClockControl(HSE, DISABLE);
//				ClockControl(HSE_BYPASS, DISABLE);
//				SetPLL_Mul(2);
//			}
//			
//			/**	@brief	配置系统时钟。
//			*		@note	函数内部会根据选择的系统时钟，自动配置是否开启外部时钟，是否开启PLL。
//			*		@note	函数内部会自动根据系统时钟的频率来设定 flash 延时。(其实这个我不太懂，看手册的推荐值配置的)
//			*		@note	函数配置得到的系统时钟会使现有的 APB1 时钟大于36M，函数内部会自动提高 APB1 的预分频系数。
//			*		@note	函数只会自动使能需要使能时钟，其它配置会尽量保持原状。(说尽量是因为APB1的预分频系数也可能被修改)
//			*	@param	scs :选择的系统时钟源
//			*		@arg	HSI_AS_SYSCLK: 如果使用这个参数，那么函数后面的参数会被自动忽略，并且设置HSI为系统时钟。
//			*		@arg	HSE_AS_SYSCLK: 如果使用这个参数，那么函数后面的参数会被自动忽略，并且设置HSE为系统时钟。
//			*			@note	如果外部时钟 HSE 不稳定，程序可能会陷入死循环
//			*		@arg	PLL_AS_SYSCLK: 设置 PLL 为系统时钟，只有使用这个参数时，后面的参数 pll_s, pll_mul的配置才效。
//			*							   这个时候函数会自动配置和开启系统的 PLL 。
//			*	@param	pll_s: PLL 时钟源的选择，参考 PLL_Source 的定义。
//			*	@param	pll_mul: PLL 倍频数，参数可以是 2 - 16。
//			*			@note	这个函数配置的系统时钟超过72M，否则，会自动切换为 HSI 作为系统时钟
//			*	@return		返回配置后的系统时钟频率
//			*/
//			u32 RCC_Struct::SysclkConfig(SystemClockSelection scs,PLL_Source pll_s, u8 pll_mul,u32 hse_freq)
//			{
//				u32 fclk = HSI_FREQ;						// 系统时钟频率
//				AHBENR = PERIPH_FLITF | PERIPH_SRAM;	// flash时钟,闪存时钟使能.DMA时钟关闭
//				
//				u32 temp;
//				temp = CIR;								// 保存原来的中断使能
//				
//				CIR = 0x00000000;						// 关闭所有RCC中断，防止中断妨碍函数工作
//				
//				u32 hsi_flag = CR & HSION;				// 记录下HSI的状态
//				
//				ClockControl(HSI, ENABLE);
//				while(!IsHSI_Ready());
//				
//				SysclkSwitch(HSI_AS_SYSCLK);			// 先切换 HSI 为系统时钟
//				flash.SetLatency(HSI_FREQ);				// 设置flash的延时
//				while( HSI_AS_SYSCLK != GetSysclkSwitchStatus());
//				
//				switch(scs)
//				{
//					case PLL_AS_SYSCLK:
//					{
//						if(pll_s == HSE_DIV_1)
//							fclk = hse_freq*pll_mul;
//						else if(pll_s == HSE_DIV_2)
//							fclk = (hse_freq/2)*pll_mul;
//						else	// HSI_DIV_2
//							fclk = (HSI_FREQ/2)*pll_mul;
//						
//						if(fclk > SYSCLK_MAX)	// 如果要设置的频率超过最大限制，不进行配置。
//						{
//							fclk = HSI_FREQ;
//							break;
//						}
//						
//						ClockControl(PLL, DISABLE);		// 为了能够配置PLL
//						
//						if(pll_s != HSI_DIV_2)			// 如果 PLL 时钟源是外部时钟，那么先开外部时钟
//						{
//							ClockControl(HSE_BYPASS, DISABLE);
//							ClockControl(HSE, ENABLE);
//							while(!IsHSE_Ready());		// 等待HSE
//						}

//						u8 apb1_prescaler = GetAPB1_Prescaler();
//						if( fclk / apb1_prescaler > APB1_MAX)		// 防止 APB1 时钟过大
//						{
//							while(apb1_prescaler<=16)
//							{
//								apb1_prescaler <<= 1;
//								if( fclk / apb1_prescaler <= APB1_MAX)
//									break;
//							}
//							SetAPB1_Prescaler(apb1_prescaler);		// 重新设置
//						}
//						
//						PLL_Config(pll_s, pll_mul);
//						ClockControl(PLL, ENABLE);
//						while(!IsPLL_Ready());
//						
//						flash.SetLatency(fclk);		// 设置 FLASH 延时
//						
//						SysclkSwitch(PLL_AS_SYSCLK);
//						while(PLL_AS_SYSCLK != GetSysclkSwitchStatus());
//						
//						if(hsi_flag == 0)
//							ClockControl(HSI, DISABLE);		// 恢复原来的 HSI 状态
//					}break;
//					case HSE_AS_SYSCLK:
//					{
//						ClockControl(HSE_BYPASS, DISABLE);
//						ClockControl(HSE, ENABLE);
//						while(!IsHSE_Ready());
//						
//						flash.SetLatency(hse_freq);		// 设置 flash 的延时，具体原因不太懂。
//						
//						SysclkSwitch(HSE_AS_SYSCLK);
//						while(HSE_AS_SYSCLK != GetSysclkSwitchStatus());
//						
//						if(hsi_flag == 0)
//							ClockControl(HSI, DISABLE);	// 恢复原来的 HSI 状态
//					}break;
//					case HSI_AS_SYSCLK:	break;	//已经配置了
//					default:	break;
//				}
//				
//				CIR = temp;		// 恢复
//				return fclk; 
//			}
//	}
//}


