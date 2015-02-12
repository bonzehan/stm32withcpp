#include "stm32f10x.h"
#include "stm32f10x_rcc.h"

#ifndef RCC_TYPEDEF
#define RCC_TYPEDEF

namespace rcc_reg
{
	enum{
		TIM2ER=0,TIM3ER=1,TIM4ER,TIM5ER,TIM6ER,TIM7ER,
		WWDGER=11,
		SPI2ER=14,SPI3ER=15,
		USART2ER=17,USART3ER,USART4ER,USART5ER,I2C1ER=21,I2C2ER=22,USBER=23,
		CANER=25,
		BKPER=27,PWRER=28,DACER=29,
		AFIOER=32,
		GPIOAER=34,GPIOBER,GPIOCER,GPIODER,GPIOEER,GPIOFER,GPIOGER,
		ADC1ER=41,ADC2ER=42,TIM1ER=43,SPI1ER=44,TIM8ER=45,USART1ER=46,ADC3ER=47
	};//����APB1��APB2���踴λ�Ĵ���������ʱ��ʹ�ܼĴ���������APB1���裬��ӦֵΪλ�ţ�����APB2���裬��ӦֵΪλ��+32
	enum{
		DMA1E=64,DMA2E,SRAME,
		FLITFE=68,
		CRCE=70,
		FSMCE=72,
		SDIOE=74
	};//����AHB����ʱ��ʹ�ܼĴ�������ӦֵΪλ��+64
	void Enable(int ppp_bit);
	void Reset(int ppp_bit);
	//void Init();

	//void DeInit();
	void Config();
	
}

#endif

//namespace periph
//{
//	//	ʱ��Ƶ�ʶ���
//	enum{
//		  HSI_FREQ			= 8000000
//		, APB1_MAX			= 36000000
//		, SYSCLK_MAX		= 72000000
//	};
//	/** @brief	ʱ�����ѡ�� micorcontroler clock output select.
//	*/
//	enum RCC_MCO_Selection{
//		  NO_CLOCK			= 0
//		, OUTPUT_SYSCLK		= BByte(100)	// System clock (SYSCLK) selected
//		, OUTPUT_HSI		= BByte(101)	// HSI clock selected
//		, OUTPUT_HSE		= BByte(110)	// HSE clock selected
//		, OUTPUT_PLL_DIV_2	= BByte(111)	// PLL clock divided by 2 selected
//	};
//	
//	/** @brief	ϵͳʱ��ѡ��
//	*/
//	enum SystemClockSelection{
//		  HSI_AS_SYSCLK		= BByte(00)
//		, HSE_AS_SYSCLK		= BByte(01)
//		, PLL_AS_SYSCLK		= BByte(10)
//	};
//	
//	/** @brief	USB ʱ�ӷ�Ƶ��
//	*/
//	enum USB_Prescaler{
//		  PLL_DIV_1D5		= 0		// PLL clock is divided by 1.5
//		, PLL_DIV_1			= 1		// PLL is not divided
//	};
//	
//	/**	@brief PLL��ʱ��Դ
//	*/
//	enum PLL_Source{
//		  HSI_DIV_2			= BByte(00)
//		, HSE_DIV_1			= BByte(01)
//		, HSE_DIV_2			= BByte(11)
//	};
//	
//	enum PeriphReset{
//		  IN_RESET_STATE	= 1		// ʹ������븴λ״̬
//		, OUT_RESET_STATE	= 0		// ʹ�����˳���λ״̬
//	};
//	
//	namespace rcc_reg{
//		/**	@brief	RCC_CR �Ĵ�����λ����
//		*/
//		enum RCC_CR{	
//			  PLLRDY	= Bit(25)			// r, PLL clock ready flag
//			, PLLON		= Bit(24)			// rw, PLL enable
//			, CSSON		= Bit(19)			// rw, Clock security system enable
//			, HSEBYP	= Bit(18)			// rw, External high-speed clock bypass
//			, HSERDY	= Bit(17)			// r, External high-speed clock ready flag
//			, HSEON		= Bit(16)			// rw, HSE clock enable
//			, HSICAL	= BitFromTo(15, 8)	// r, Internal high-speed clock calibration
//			, HSITRIM	= BitFromTo(7, 3)	// rw, Internal high-speed clock trimming
//			, HSIRDY	= Bit(1)			// r, Internal high-speed clock ready flag
//			, HSION		= Bit(0)			// rw, Internal high-speed clock enable
//		};
//	}
//	
//	/**	@brief	�� RCC_CR �Ĵ������Ƶ�ʱ��
//	*/
//	enum RCC_CR_Control
//	{
//		  PLL					= rcc_reg::PLLON
//		, CLOCK_SECURITY_SYSTEM	= rcc_reg::CSSON
//		, HSE_BYPASS			= rcc_reg::HSEBYP
//		, HSE					= rcc_reg::HSEON
//		, HSI					= rcc_reg::HSION
//	};
//	
//	namespace rcc_reg{
//		
//		/**	@brief	RCC_CFGR �Ĵ�����λ����
//		*/
//		enum RCC_CFGR{		// configuration register
//			  MCO			= BitFromTo(26, 24)	// rw, Microntroller clock output
//			, USBPRE		= Bit(22)			// USB prescaler
//			, PLLMUL		= BitFromTo(21, 18)	// PLL multiplication factor
//			, PLLXTPRE		= Bit(17)			// HSE devider for pll entry
//			, PLLSRC		= Bit(16)			// PLL entry clock source,  This bit can be written only when PLL is disabled.
//			, ADCPRE		= BitFromTo(15, 14)	// ADC prescaler 
//			, PPRE2			= BitFromTo(13, 11)	// APB high-speed prescaler (APB2)
//			, PPRE1			= BitFromTo(10, 8)	// APB low-speed prescaler (APB1)
//			, HPRE			= BitFromTo(7, 4)	// AHB prescaler
//			, SWS			= BitFromTo(3, 2)	// System clock switch status
//			, SW			= BitFromTo(1, 0)	// System clock switch
//		};
//		
//		/**	@brief	RCC_CIR �Ĵ�����λ����
//		*/
//		enum RCC_CIR{		// Clock interrupt register
//			  CSSC			= Bit(23)			// Clock security system interrupt clear
//			, PLLRDYC		= Bit(20)			// PLL ready interrupt clear
//			, HSERDYC		= Bit(19)			// HSE ready interrupt clear
//			, HSIRDYC		= Bit(18)			// HSI ready interrupt clear
//			, LSERDYC		= Bit(17)			// LSE ready interrupt clear
//			, LSIRDYC		= Bit(16)			// LSI ready interrupt clear
//			, PLLRDYIE		= Bit(12)			// PLL ready interrupt enable
//			, HSERDYIE		= Bit(11)			// HSE ready interrupt enable
//			, HSIRDYIE		= Bit(10)			// HSI ready interrupt enable
//			, LSERDYIE		= Bit(9)			// LSE ready interrupt enable
//			, LSIRDYIE		= Bit(8)			// LSI ready interrupt enable
//			, CSSF			= Bit(7)			// clock security system interrupt flag
//			, PLLRDYF		= Bit(4)			// PLL ready interrupt flag
//			, HSERDYF		= Bit(3)			// HSE ready interrupt flag
//			, HSIRDF		= Bit(2)			// HSI ready interrupt flag
//			, LSERDYF		= Bit(1)			// LSE ready interrupt flag
//			, LSIRDYF		= Bit(0)			// LSI ready interrupt flag
//		};
//		
//		/** @brief	RCC_AHB_PERIPHERAL �Ĵ�����λ����
//		*/
//		enum RCC_AHB_PERIPHERAL
//		{
//			  PERIPH_SDIO	= Bit(10)
//			, PERIPH_FSMC	= Bit(8)
//			, PERIPH_CRC	= Bit(6)
//			, PERIPH_FLITF	= Bit(4)
//			, PERIPH_SRAM	= Bit(2)
//			, PERIPH_DMA2	= Bit(1)
//			, PERIPH_DMA1	= Bit(0)
//		};
//		
//		/** @brief	APB2 ���裬������PeriphControl�����Ĳ���
//		*	@note	�󲿷�����ṹ�嶼�Ѿ������� RCC_APB2_PERIPHERAL() ��������
//		*			���Բ���ֱ��ʹ������� identifier��Ϊ������
//		*			���磬ʹ��GPIOA��ʱ��: rcc.PeriphControl(gpioa, ENABLE);
//		*/
//		enum RCC_APB2_PERIPHERAL{
//		  PERIPH_TIM11		= Bit(21)
//		, PERIPH_TIM10		= Bit(20)
//		, PERIPH_TIM9		= Bit(19)
//		, PERIPH_USART1		= Bit(14)		// USART1 clock enable
//		, PERIPH_TIM8		= Bit(13)
//		, PERIPH_TIM1		= Bit(11)
//		, PERIPH_GPIOG		= Bit(8)
//		, PERIPH_GPIOF		= Bit(7)
//		, PERIPH_GPIOE		= Bit(6)
//		, PERIPH_GPIOD		= Bit(5)
//		, PERIPH_GPIOC		= Bit(4)
//		, PERIPH_GPIOB		= Bit(3)
//		, PERIPH_GPIOA		= Bit(2)
//		, PERIPH_AFIO		= Bit(0)	// Alternate function I/O clock enable
//		};
//		
//		/** @brief	APB1 ���裬������PeriphControl�����Ĳ���
//		*	@note	�󲿷�����ṹ�嶼�Ѿ������� RCC_APB1_PERIPHERAL() ��������
//		*			���Բ���ֱ��ʹ������� identifier��Ϊ������
//		*			���磬ʹ��WWDG��ʱ��: rcc.PeriphControl(wwdg, ENABLE);
//		*/
//		enum RCC_APB1_PERIPHERAL{
//			  PERIPH_WWDG	= Bit(11)		// window watch dog
//			, PERIPH_TIM5	= Bit(3)
//			, PERIPH_TIM4	= Bit(2)
//			, PERIPH_TIM3	= Bit(1)
//			, PERIPH_TIM2	= Bit(0)
//		};

//		typedef struct RCC_Struct
//		{	
//			__IO uint32_t CR;
//			__IO uint32_t CFGR;
//			__IO uint32_t CIR;
//			__IO uint32_t APB2RSTR;
//			__IO uint32_t APB1RSTR;
//			__IO uint32_t AHBENR;
//			__IO uint32_t APB2ENR;
//			__IO uint32_t APB1ENR;
//			__IO uint32_t BDCR;
//			__IO uint32_t CSR;
//		
//			#ifdef STM32F10X_CL  
//				__IO uint32_t AHBRSTR;
//				__IO uint32_t CFGR2;
//			#endif /* STM32F10X_CL */ 
//		
//			#if defined (STM32F10X_LD_VL) || defined (STM32F10X_MD_VL) || defined (STM32F10X_HD_VL)   
//				uint32_t RESERVED0;
//				__IO uint32_t CFGR2;
//			#endif /* STM32F10X_LD_VL || STM32F10X_MD_VL || STM32F10X_HD_VL */
//			protected:
//			RCC_Struct(){}	// ��ֹ�ⲿ��������
//			
//			/**	@brief	���� PLL �ı�Ƶ��
//			*	@param	mul: ������2, 3, 4, 5, ..., 16
//			*	@return	none
//			*	@note	ֻ���� PLL Ϊʧ��״̬ʱ������������ò���Ч��
//			*/
//			finline void SetPLL_Mul(u8 mul)		{ CFGR = assignf(CFGR, PLLMUL, mul-2);}
//			
//			/**	@brief	���� PLL ��ʱ��Դ
//			*	@param	s: �ο� PLL_Source ö����Ķ��塣
//			*	@note	ֻ���� PLL Ϊʧ��״̬ʱ������������ò���Ч��	
//			*/
//			finline void SetPLL_Source(PLL_Source s)	{ CFGR = assignf(CFGR, PLLXTPRE | PLLSRC, s);}
//		
//			public:
//			
//			/**	@brief	ѡ��STM32��ʱ�����
//			*	@param	s: �ο�RCC_MCO_Selectö����Ķ��塣
//			*/
//			void finline SetClockOutput(RCC_MCO_Selection s)		{CFGR = assignf(CFGR, MCO, s); }
//			
//			/**	@brief	ѡ��ϵͳʱ��
//			*	@param	s: �ο�SystemClockSelectionö����Ķ��塣
//			*	@note	ѡ��ϵͳʱ�Ӻ���Ҫ���ú��� GetCurSystemClockSwitch���ж��䷵��ֵ
//			*			һֱ�� GetCurSystemClockSwitch �������õ�ֵΪֹ������ɹ���
//			*/
//			void finline  SysclkSwitch(SystemClockSelection s)		{CFGR = assignf(CFGR, SW, s); }
//			
//			/**	@brief	�õ���ǰ��ϵͳʱ��Դ
//			*	@param	none
//			*	@return ��ǰ��ϵͳʱ��Դ��
//			*/
//			SystemClockSelection GetSysclkSwitchStatus()	{return (SystemClockSelection)readf(CFGR, SWS);}
//			
//			
//			/**	@brief	���� APB1 ʱ��Ԥ��Ƶ��
//			*	@param	div:	���÷�Ƶϵ��������������1, 2, 4, 8, 16
//			*/
//			void SetAPB1_Prescaler(u8 div);
//			/**	@brief	�õ� APB1 ʱ��Ԥ��Ƶ��
//			*	@param	div:	���÷�Ƶϵ��������������1, 2, 4, 8, 16
//			*/
//			u8 GetAPB1_Prescaler();
//			
//			/**	@brief	���� APB2 ʱ��Ԥ��Ƶ��
//			*	@param	div:	���÷�Ƶϵ��������������1, 2, 4, 8, 16
//			*/
//			void SetAPB2_Prescaler(u8 div);
//			
//			/**	@brief	���� AHB ʱ��Ԥ��Ƶ��
//			*	@param	div: ���÷�Ƶϵ��������������1, 2, 4, 8, 16, ..., 512
//			*/
//			void SetAHB_Prescaler(u8 div);
//			
//			/**	@brief	���� ADC ʱ��Ԥ��Ƶ��
//			*	@param	div: ���÷�Ƶϵ�������������� 2, 4, 6, 8
//			*/
//			void SetADC_Prescaler(u8 div)			{ CFGR = assignf(CFGR, ADCPRE, (div>>1) - 1); }
//			
//			/**	@brief	���� USB ʱ��Ԥ��Ƶ��
//			*	@param	p: �ο� USB_Prescaler ö����Ķ���
//			*	@return	none
//			*/
//			void SetUSB_Prescaler(USB_Prescaler p)	{CFGR = assignf(CFGR, USBPRE, p);}
//			
//			/**	@brief	����PLL
//			*	@param	s: PLLʱ��Դ���ο� PLL_Source �Ķ��塣
//			*	@param	mul: PLL ��Ƶ��
//			*	@note	ֻ���� PLL Ϊʧ��״̬ʱ������������ò���Ч��
//			*/
//			finline void PLL_Config(PLL_Source s, u8 mul)	{SetPLL_Source(s);SetPLL_Mul(mul); }
//			
//			/** @brief	��Ĭ�ϵķ�ʽ��ʼ��RCC����ʵ���ǰ�RCC�ļĴ������ûظ�λֵ��
//			*			����ֻ��ϵͳ��ʼ����ʱ��ʹ��
//			*/
//			void DeInit();
//			
//			/**	@brief	ʹ��/��ֹʱ��
//			*	@param	c: �ο�RCC_CR_Control�Ķ���
//			*		@note	��� c ֱ�ӻ��ӵı�����ϵͳʱ�ӣ���ô��������޷�������ֹ��
//			*		@arg	PLL: pll �Ŀ�����ر�
//			*		@arg	CLOCK_SECURITY_SYSTEM
//			*		@arg	HSE: �����ⲿʱ��
//			*		@arg	HSE_BYPASS: �����ⲿʱ����·
//			*		@arg	HSI: �����ڲ�ʱ��
//			*	@param	s: ʹ�ܻ��ֹ���ο�FunctionalState�Ķ��塣
//			*/
//			finline void ClockControl(RCC_CR_Control c, FunctionalState s)				{ CR = (s==DISABLE)? clearb(CR, c): setb(CR, c);}
//			
//			
//			/**	@brief	ʹ��/��ֹ APB2 ����
//			*	@param	c: �ο� @ref RCC_APB2_PERIPHERAL �Ķ���
//			*	@param	s: ʹ�ܻ��ֹ���ο�FunctionalState�Ķ��塣
//			*/
//			finline void PeriphControl(RCC_APB2_PERIPHERAL c, FunctionalState s)		{ APB2ENR =(s==DISABLE)? clearb(APB2ENR, c):setb(APB2ENR, c); }
//			
//			/**	@brief	ʹ APB2 �������/�˳���λ״̬
//			*	@param	c: �ο� @ref RCC_APB2PERIPHRAL �Ķ��塣
//			*	@param	s: ʹ���������˳���λ״̬��ָ�
//			*		@arg	IN_RESET_STATE: ���븴λ״̬
//			*		@arg	OUT_RESET_STATE: �˳���λ״̬
//			*/
//			finline void PeriphControl(RCC_APB2_PERIPHERAL c, PeriphReset s)			{ APB2RSTR = (s==OUT_RESET_STATE)? clearb(APB2RSTR, c):setb(APB2RSTR, c); }
//			
//			/**	@brief	ʹ��/��ֹ APB1 ����
//			*	@param	c: �ο�RCC_APB2_PERIPHERAL�Ķ���
//			*	@param	s: ʹ�ܻ��ֹ���ο� @ref FunctionalState �Ķ��塣
//			*/
//			finline void PeriphControl(RCC_APB1_PERIPHERAL c, FunctionalState s)		{ APB1ENR =(s==DISABLE)? clearb(APB1ENR, c):setb(APB1ENR, c); }
//			/**	@brief	ʹ APB2 �������/�˳���λ״̬
//			*	@param	c: �ο�RCC_APB2PERIPHRAL�Ķ��塣
//			*/
//			finline void PeriphControl(RCC_APB1_PERIPHERAL c, PeriphReset s)			{ APB1RSTR = (s==OUT_RESET_STATE)? clearb(APB1RSTR, c):setb(APB1RSTR, c); }
//			
//			finline bool IsPLL_Ready()		{ return checkb(CR, PLLRDY)!=0;}
//			finline bool IsHSE_Ready()		{ return checkb(CR, HSERDY)!=0;}
//			finline bool IsHSI_Ready()		{ return checkb(CR, HSIRDY)!=0; }
//			
//			u32 SysclkConfig(SystemClockSelection scs,PLL_Source pll_s = HSI_DIV_2, u8 pll_mul = 2, u32 hse_freq = 8000000);
//		} RCC_TypeDef;
//	}	
//}

//#define rcc					(*RCC)

//using periph::rcc_reg::RCC_TypeDef;

//#endif
