#ifndef GPIO_TYPEDEF
#define GPIO_TYPEDEF

#include "stm32f10x.h"
#include "RCC_typedef.h"

using namespace rcc_reg;
namespace gpio
{
	enum{P0 = (uint16_t) 0x0001,P1 = (uint16_t) 0x0002,P2 = (uint16_t) 0x0004,P3 = (uint16_t) 0x0008,
			P4 = (uint16_t) 0x0010,P5 = (uint16_t) 0x0020,P6 = (uint16_t) 0x0040,P7 = (uint16_t) 0x0080,
			P8 = (uint16_t) 0x0100,P9 = (uint16_t) 0x0200,P10 = (uint16_t) 0x0400,P11 = (uint16_t) 0x0800,
			P12 = (uint16_t) 0x1000,P13 = (uint16_t) 0x2000,P14 = (uint16_t) 0x4000,P15 = (uint16_t) 0x8000,
			PA = (uint16_t) 0xFFFF
		};
	enum{IN_AN = 0x00,IN_FLOATING = 0x04,IN_DW = 0x08,IN_UP = 0x0C,//输入：模拟，浮空（默认），下拉电阻,上拉电阻(0x08,暂用0x0C替代)
			OUT_OP2 = 0x02,OUT_OP10 = 0x01,OUT_OP = 0x03,//输出：通用（O）推挽（P）：2/10/50MHz（自定义默认）
			OUT_OD2 = 0x06,OUT_OD10 = 0x05,OUT_OD = 0x07,//输出：通用开漏：2/10/50MHz（自定义默认）
			OUT_AP2 = 0x0A,OUT_AP10 = 0x09,OUT_AP = 0x0B,//输出：复用推挽：2/10/50MHz（自定义默认）
			OUT_AD2 = 0x0E,OUT_AD10 = 0x0D,OUT_AD = 0x0F//输出：复用（A）开漏（D）：2/10/50MHz（自定义默认）
		};

	class gpio_conf
	{
	private:
		u32 CRL;
		u32 CRH;
		u32 BSRR;
	
	public:		
		
		GPIO_TypeDef* PPP_NAM;
		u8 CMODE;//包含了0xC的变量
		u8 MODE;//不包含0xC
		u16 BITS;
			
		gpio_conf(GPIO_TypeDef* ppp_nam=0,unsigned char cmode=0x04,uint16_t bits=0x0000)
		{
			PPP_NAM=ppp_nam;
			CMODE=cmode;
			if(cmode==0x0C)
			{
				MODE=0x08;	
			}
			else MODE=cmode;
			BITS=bits;
			
			CRL=0x00000000;
			CRH=0x00000000;
			BSRR=0x00000000;
			Update();
		}//初始化：外设名(空)，输入输出模式（浮空输入），位（空）
		
		bool pin(uint16_t bits);//读出位值,多位混读时，有一位为1则输出true，输入模式读IDR，输出模式读ODR
		void port(uint16_t bits,bool ER);//写入位
		int lock(uint16_t bits);//锁定设置，成功返回0，失败返回1
		
		bool operator == (bool& ER)//类名必须作为左值使用
		{
			return this->pin(PA);
		}
		void operator = (bool ER)
		{
			if(ER)
				return this->port(BITS,1);
			else
				return this->port(BITS,0);
		}

		void Update(void);
		void Init(void);
		void DeInit(void);


		#define BIT_ADDR(addr, bitnum)   *((volatile unsigned long*)(addr & 0xF0000000)+0x2000000+((addr &0xFFFFF)<<5)+(bitnum<<2))

		#define GPIOA_ODR_Addr    (GPIOA_BASE+12) //0x4001080C 
		#define GPIOB_ODR_Addr    (GPIOB_BASE+12) //0x40010C0C 
		#define GPIOC_ODR_Addr    (GPIOC_BASE+12) //0x4001100C 
		#define GPIOD_ODR_Addr    (GPIOD_BASE+12) //0x4001140C 
		#define GPIOE_ODR_Addr    (GPIOE_BASE+12) //0x4001180C 
		#define GPIOF_ODR_Addr    (GPIOF_BASE+12) //0x40011A0C    
		#define GPIOG_ODR_Addr    (GPIOG_BASE+12) //0x40011E0C    

		#define GPIOA_IDR_Addr    (GPIOA_BASE+8) //0x40010808 
		#define GPIOB_IDR_Addr    (GPIOB_BASE+8) //0x40010C08 
		#define GPIOC_IDR_Addr    (GPIOC_BASE+8) //0x40011008 
		#define GPIOD_IDR_Addr    (GPIOD_BASE+8) //0x40011408 
		#define GPIOE_IDR_Addr    (GPIOE_BASE+8) //0x40011808 
		#define GPIOF_IDR_Addr    (GPIOF_BASE+8) //0x40011A08 
		#define GPIOG_IDR_Addr    (GPIOG_BASE+8) //0x40011E08

		#define PAout(n)   BIT_ADDR(GPIOA_ODR_Addr,n)  //输出 
		#define PAin(n)    BIT_ADDR(GPIOA_IDR_Addr,n)  //输入 

		#define PBout(n)   BIT_ADDR(GPIOB_ODR_Addr,n)  //输出 
		#define PBin(n)    BIT_ADDR(GPIOB_IDR_Addr,n)  //输入 

		#define PCout(n)   BIT_ADDR(GPIOC_ODR_Addr,n)  //输出 
		#define PCin(n)    BIT_ADDR(GPIOC_IDR_Addr,n)  //输入 

		#define PDout(n)   BIT_ADDR(GPIOD_ODR_Addr,n)  //输出 
		#define PDin(n)    BIT_ADDR(GPIOD_IDR_Addr,n)  //输入 

		#define PEout(n)   BIT_ADDR(GPIOE_ODR_Addr,n)  //输出 
		#define PEin(n)    BIT_ADDR(GPIOE_IDR_Addr,n)  //输入

		#define PFout(n)   BIT_ADDR(GPIOF_ODR_Addr,n)  //输出 
		#define PFin(n)    BIT_ADDR(GPIOF_IDR_Addr,n)  //输入

		#define PGout(n)   BIT_ADDR(GPIOG_ODR_Addr,n)  //输出 
		#define PGin(n)    BIT_ADDR(GPIOG_IDR_Addr,n)  //输入


	};
}
#endif
