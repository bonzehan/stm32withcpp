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
	};//用于APB1和APB2外设复位寄存器和外设时钟使能寄存器，对于APB1外设，相应值为位号，对于APB2外设，相应值为位号+32
	enum{
		DMA1E=64,DMA2E,SRAME,
		FLITFE=68,
		CRCE=70,
		FSMCE=72,
		SDIOE=74
	};//用于AHB外设时钟使能寄存器，相应值为位号+64
	void Enable(int ppp_bit);
	void Reset(int ppp_bit);
	//void Init();

	//void DeInit();
	void Config();
	
}

#endif

//namespace periph
//{
//	//	时钟频率定义
//	enum{
//		  HSI_FREQ			= 8000000
//		, APB1_MAX			= 36000000
//		, SYSCLK_MAX		= 72000000
//	};
//	/** @brief	时钟输出选择。 micorcontroler clock output select.
//	*/
//	enum RCC_MCO_Selection{
//		  NO_CLOCK			= 0
//		, OUTPUT_SYSCLK		= BByte(100)	// System clock (SYSCLK) selected
//		, OUTPUT_HSI		= BByte(101)	// HSI clock selected
//		, OUTPUT_HSE		= BByte(110)	// HSE clock selected
//		, OUTPUT_PLL_DIV_2	= BByte(111)	// PLL clock divided by 2 selected
//	};
//	
//	/** @brief	系统时钟选择
//	*/
//	enum SystemClockSelection{
//		  HSI_AS_SYSCLK		= BByte(00)
//		, HSE_AS_SYSCLK		= BByte(01)
//		, PLL_AS_SYSCLK		= BByte(10)
//	};
//	
//	/** @brief	USB 时钟分频数
//	*/
//	enum USB_Prescaler{
//		  PLL_DIV_1D5		= 0		// PLL clock is divided by 1.5
//		, PLL_DIV_1			= 1		// PLL is not divided
//	};
//	
//	/**	@brief PLL的时钟源
//	*/
//	enum PLL_Source{
//		  HSI_DIV_2			= BByte(00)
//		, HSE_DIV_1			= BByte(01)
//		, HSE_DIV_2			= BByte(11)
//	};
//	
//	enum PeriphReset{
//		  IN_RESET_STATE	= 1		// 使外设进入复位状态
//		, OUT_RESET_STATE	= 0		// 使外设退出复位状态
//	};
//	
//	namespace rcc_reg{
//		/**	@brief	RCC_CR 寄存器的位定义
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
//	/**	@brief	由 RCC_CR 寄存器控制的时钟
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
//		/**	@brief	RCC_CFGR 寄存器的位定义
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
//		/**	@brief	RCC_CIR 寄存器的位定义
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
//		/** @brief	RCC_AHB_PERIPHERAL 寄存器的位定义
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
//		/** @brief	APB2 外设，用来作PeriphControl函数的参数
//		*	@note	大部分外设结构体都已经重载了 RCC_APB2_PERIPHERAL() 操作符，
//		*			所以不必直接使用这里的 identifier作为参数，
//		*			例如，使能GPIOA的时钟: rcc.PeriphControl(gpioa, ENABLE);
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
//		/** @brief	APB1 外设，用来作PeriphControl函数的参数
//		*	@note	大部分外设结构体都已经重载了 RCC_APB1_PERIPHERAL() 操作符，
//		*			所以不必直接使用这里的 identifier作为参数，
//		*			例如，使能WWDG的时钟: rcc.PeriphControl(wwdg, ENABLE);
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
//			RCC_Struct(){}	// 禁止外部建立对象
//			
//			/**	@brief	设置 PLL 的倍频数
//			*	@param	mul: 可以是2, 3, 4, 5, ..., 16
//			*	@return	none
//			*	@note	只有在 PLL 为失能状态时这个函数的配置才有效。
//			*/
//			finline void SetPLL_Mul(u8 mul)		{ CFGR = assignf(CFGR, PLLMUL, mul-2);}
//			
//			/**	@brief	设置 PLL 的时钟源
//			*	@param	s: 参考 PLL_Source 枚举类的定义。
//			*	@note	只有在 PLL 为失能状态时这个函数的配置才有效。	
//			*/
//			finline void SetPLL_Source(PLL_Source s)	{ CFGR = assignf(CFGR, PLLXTPRE | PLLSRC, s);}
//		
//			public:
//			
//			/**	@brief	选择STM32的时钟输出
//			*	@param	s: 参考RCC_MCO_Select枚举类的定义。
//			*/
//			void finline SetClockOutput(RCC_MCO_Selection s)		{CFGR = assignf(CFGR, MCO, s); }
//			
//			/**	@brief	选择系统时钟
//			*	@param	s: 参考SystemClockSelection枚举类的定义。
//			*	@note	选择系统时钟后，需要调用函数 GetCurSystemClockSwitch，判断其返回值
//			*			一直到 GetCurSystemClockSwitch 返回设置的值为止，才算成功。
//			*/
//			void finline  SysclkSwitch(SystemClockSelection s)		{CFGR = assignf(CFGR, SW, s); }
//			
//			/**	@brief	得到当前的系统时钟源
//			*	@param	none
//			*	@return 当前的系统时钟源。
//			*/
//			SystemClockSelection GetSysclkSwitchStatus()	{return (SystemClockSelection)readf(CFGR, SWS);}
//			
//			
//			/**	@brief	设置 APB1 时钟预分频器
//			*	@param	div:	设置分频系数，参数可以是1, 2, 4, 8, 16
//			*/
//			void SetAPB1_Prescaler(u8 div);
//			/**	@brief	得到 APB1 时钟预分频器
//			*	@param	div:	设置分频系数，参数可以是1, 2, 4, 8, 16
//			*/
//			u8 GetAPB1_Prescaler();
//			
//			/**	@brief	设置 APB2 时钟预分频器
//			*	@param	div:	设置分频系数，参数可以是1, 2, 4, 8, 16
//			*/
//			void SetAPB2_Prescaler(u8 div);
//			
//			/**	@brief	设置 AHB 时钟预分频器
//			*	@param	div: 设置分频系数，参数可以是1, 2, 4, 8, 16, ..., 512
//			*/
//			void SetAHB_Prescaler(u8 div);
//			
//			/**	@brief	设置 ADC 时钟预分频器
//			*	@param	div: 设置分频系数，参数可以是 2, 4, 6, 8
//			*/
//			void SetADC_Prescaler(u8 div)			{ CFGR = assignf(CFGR, ADCPRE, (div>>1) - 1); }
//			
//			/**	@brief	设置 USB 时钟预分频器
//			*	@param	p: 参考 USB_Prescaler 枚举类的定义
//			*	@return	none
//			*/
//			void SetUSB_Prescaler(USB_Prescaler p)	{CFGR = assignf(CFGR, USBPRE, p);}
//			
//			/**	@brief	配置PLL
//			*	@param	s: PLL时钟源，参考 PLL_Source 的定义。
//			*	@param	mul: PLL 倍频数
//			*	@note	只有在 PLL 为失能状态时这个函数的配置才有效。
//			*/
//			finline void PLL_Config(PLL_Source s, u8 mul)	{SetPLL_Source(s);SetPLL_Mul(mul); }
//			
//			/** @brief	以默认的方式初始化RCC，其实就是把RCC的寄存器设置回复位值，
//			*			建议只在系统初始化的时候使用
//			*/
//			void DeInit();
//			
//			/**	@brief	使能/禁止时钟
//			*	@param	c: 参考RCC_CR_Control的定义
//			*		@note	如果 c 直接或间接的被用作系统时钟，那么这个函数无法将它禁止。
//			*		@arg	PLL: pll 的开启或关闭
//			*		@arg	CLOCK_SECURITY_SYSTEM
//			*		@arg	HSE: 高速外部时钟
//			*		@arg	HSE_BYPASS: 高速外部时钟旁路
//			*		@arg	HSI: 高速内部时钟
//			*	@param	s: 使能或禁止，参考FunctionalState的定义。
//			*/
//			finline void ClockControl(RCC_CR_Control c, FunctionalState s)				{ CR = (s==DISABLE)? clearb(CR, c): setb(CR, c);}
//			
//			
//			/**	@brief	使能/禁止 APB2 外设
//			*	@param	c: 参考 @ref RCC_APB2_PERIPHERAL 的定义
//			*	@param	s: 使能或禁止，参考FunctionalState的定义。
//			*/
//			finline void PeriphControl(RCC_APB2_PERIPHERAL c, FunctionalState s)		{ APB2ENR =(s==DISABLE)? clearb(APB2ENR, c):setb(APB2ENR, c); }
//			
//			/**	@brief	使 APB2 外设进入/退出复位状态
//			*	@param	c: 参考 @ref RCC_APB2PERIPHRAL 的定义。
//			*	@param	s: 使外设进入或退出复位状态的指令。
//			*		@arg	IN_RESET_STATE: 进入复位状态
//			*		@arg	OUT_RESET_STATE: 退出复位状态
//			*/
//			finline void PeriphControl(RCC_APB2_PERIPHERAL c, PeriphReset s)			{ APB2RSTR = (s==OUT_RESET_STATE)? clearb(APB2RSTR, c):setb(APB2RSTR, c); }
//			
//			/**	@brief	使能/禁止 APB1 外设
//			*	@param	c: 参考RCC_APB2_PERIPHERAL的定义
//			*	@param	s: 使能或禁止，参考 @ref FunctionalState 的定义。
//			*/
//			finline void PeriphControl(RCC_APB1_PERIPHERAL c, FunctionalState s)		{ APB1ENR =(s==DISABLE)? clearb(APB1ENR, c):setb(APB1ENR, c); }
//			/**	@brief	使 APB2 外设进入/退出复位状态
//			*	@param	c: 参考RCC_APB2PERIPHRAL的定义。
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
