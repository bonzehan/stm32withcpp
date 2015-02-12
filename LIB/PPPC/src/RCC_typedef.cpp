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
//	};//����APB1��APB2���踴λ�Ĵ���������ʱ��ʹ�ܼĴ���������APB1���裬��ӦֵΪλ�ţ�����APB2���裬��ӦֵΪλ��+32
//	enum{
//		DMA1E=64,DMA2E,SRAME,
//		FLITFE=68,
//		CRCE=70,
//		FSMCE=72,
//		SDIOE=74
//	};//����AHB����ʱ��ʹ�ܼĴ�������ӦֵΪλ��+64
	
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
//			/**	@brief	���� AHB ʱ��Ԥ��Ƶ��
//			*	@param	div: ���÷�Ƶϵ��������������1, 2, 4, 8, 16, ..., 512
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
//			/**	@brief	���� APB2 ʱ��Ԥ��Ƶ��
//			*	@param	div:	���÷�Ƶϵ��������������1, 2, 4, 8, 16
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
//				APB2ENR = 0x00000000; //����ʱ�ӹر�.			   
//				APB1ENR = 0x00000000;
//				
//				AHBENR = PERIPH_FLITF | PERIPH_SRAM;	// flashʱ��,����ʱ��ʹ��.DMAʱ�ӹر�	
//				
//				CIR = 0x00000000;						// �ر������ж�			
//				
//				ClockControl(HSI, ENABLE);				// ʹ���ڲ�����ʱ��HSION	
//				while(!IsHSI_Ready());					// �ȴ� HSI ����
//				
//				SetClockOutput(NO_CLOCK);				// û��ʱ�����
//				SysclkSwitch(HSI_AS_SYSCLK);			// �л� HSI Ϊϵͳʱ��
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
//			/**	@brief	����ϵͳʱ�ӡ�
//			*		@note	�����ڲ������ѡ���ϵͳʱ�ӣ��Զ������Ƿ����ⲿʱ�ӣ��Ƿ���PLL��
//			*		@note	�����ڲ����Զ�����ϵͳʱ�ӵ�Ƶ�����趨 flash ��ʱ��(��ʵ����Ҳ�̫�������ֲ���Ƽ�ֵ���õ�)
//			*		@note	�������õõ���ϵͳʱ�ӻ�ʹ���е� APB1 ʱ�Ӵ���36M�������ڲ����Զ���� APB1 ��Ԥ��Ƶϵ����
//			*		@note	����ֻ���Զ�ʹ����Ҫʹ��ʱ�ӣ��������ûᾡ������ԭ״��(˵��������ΪAPB1��Ԥ��Ƶϵ��Ҳ���ܱ��޸�)
//			*	@param	scs :ѡ���ϵͳʱ��Դ
//			*		@arg	HSI_AS_SYSCLK: ���ʹ�������������ô��������Ĳ����ᱻ�Զ����ԣ���������HSIΪϵͳʱ�ӡ�
//			*		@arg	HSE_AS_SYSCLK: ���ʹ�������������ô��������Ĳ����ᱻ�Զ����ԣ���������HSEΪϵͳʱ�ӡ�
//			*			@note	����ⲿʱ�� HSE ���ȶ���������ܻ�������ѭ��
//			*		@arg	PLL_AS_SYSCLK: ���� PLL Ϊϵͳʱ�ӣ�ֻ��ʹ���������ʱ������Ĳ��� pll_s, pll_mul�����ò�Ч��
//			*							   ���ʱ�������Զ����úͿ���ϵͳ�� PLL ��
//			*	@param	pll_s: PLL ʱ��Դ��ѡ�񣬲ο� PLL_Source �Ķ��塣
//			*	@param	pll_mul: PLL ��Ƶ�������������� 2 - 16��
//			*			@note	����������õ�ϵͳʱ�ӳ���72M�����򣬻��Զ��л�Ϊ HSI ��Ϊϵͳʱ��
//			*	@return		�������ú��ϵͳʱ��Ƶ��
//			*/
//			u32 RCC_Struct::SysclkConfig(SystemClockSelection scs,PLL_Source pll_s, u8 pll_mul,u32 hse_freq)
//			{
//				u32 fclk = HSI_FREQ;						// ϵͳʱ��Ƶ��
//				AHBENR = PERIPH_FLITF | PERIPH_SRAM;	// flashʱ��,����ʱ��ʹ��.DMAʱ�ӹر�
//				
//				u32 temp;
//				temp = CIR;								// ����ԭ�����ж�ʹ��
//				
//				CIR = 0x00000000;						// �ر�����RCC�жϣ���ֹ�жϷ�����������
//				
//				u32 hsi_flag = CR & HSION;				// ��¼��HSI��״̬
//				
//				ClockControl(HSI, ENABLE);
//				while(!IsHSI_Ready());
//				
//				SysclkSwitch(HSI_AS_SYSCLK);			// ���л� HSI Ϊϵͳʱ��
//				flash.SetLatency(HSI_FREQ);				// ����flash����ʱ
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
//						if(fclk > SYSCLK_MAX)	// ���Ҫ���õ�Ƶ�ʳ���������ƣ����������á�
//						{
//							fclk = HSI_FREQ;
//							break;
//						}
//						
//						ClockControl(PLL, DISABLE);		// Ϊ���ܹ�����PLL
//						
//						if(pll_s != HSI_DIV_2)			// ��� PLL ʱ��Դ���ⲿʱ�ӣ���ô�ȿ��ⲿʱ��
//						{
//							ClockControl(HSE_BYPASS, DISABLE);
//							ClockControl(HSE, ENABLE);
//							while(!IsHSE_Ready());		// �ȴ�HSE
//						}

//						u8 apb1_prescaler = GetAPB1_Prescaler();
//						if( fclk / apb1_prescaler > APB1_MAX)		// ��ֹ APB1 ʱ�ӹ���
//						{
//							while(apb1_prescaler<=16)
//							{
//								apb1_prescaler <<= 1;
//								if( fclk / apb1_prescaler <= APB1_MAX)
//									break;
//							}
//							SetAPB1_Prescaler(apb1_prescaler);		// ��������
//						}
//						
//						PLL_Config(pll_s, pll_mul);
//						ClockControl(PLL, ENABLE);
//						while(!IsPLL_Ready());
//						
//						flash.SetLatency(fclk);		// ���� FLASH ��ʱ
//						
//						SysclkSwitch(PLL_AS_SYSCLK);
//						while(PLL_AS_SYSCLK != GetSysclkSwitchStatus());
//						
//						if(hsi_flag == 0)
//							ClockControl(HSI, DISABLE);		// �ָ�ԭ���� HSI ״̬
//					}break;
//					case HSE_AS_SYSCLK:
//					{
//						ClockControl(HSE_BYPASS, DISABLE);
//						ClockControl(HSE, ENABLE);
//						while(!IsHSE_Ready());
//						
//						flash.SetLatency(hse_freq);		// ���� flash ����ʱ������ԭ��̫����
//						
//						SysclkSwitch(HSE_AS_SYSCLK);
//						while(HSE_AS_SYSCLK != GetSysclkSwitchStatus());
//						
//						if(hsi_flag == 0)
//							ClockControl(HSI, DISABLE);	// �ָ�ԭ���� HSI ״̬
//					}break;
//					case HSI_AS_SYSCLK:	break;	//�Ѿ�������
//					default:	break;
//				}
//				
//				CIR = temp;		// �ָ�
//				return fclk; 
//			}
//	}
//}


