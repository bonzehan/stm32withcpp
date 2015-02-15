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
	enum{IN_AN = 0x00,IN_FLOATING = 0x04,IN_DW = 0x08,IN_UP = 0x0C,//���룺ģ�⣬���գ�Ĭ�ϣ�����������,��������(0x08,����0x0C���)
			OUT_OP2 = 0x02,OUT_OP10 = 0x01,OUT_OP = 0x03,//�����ͨ�ã�O�����죨P����2/10/50MHz���Զ���Ĭ�ϣ�
			OUT_OD2 = 0x06,OUT_OD10 = 0x05,OUT_OD = 0x07,//�����ͨ�ÿ�©��2/10/50MHz���Զ���Ĭ�ϣ�
			OUT_AP2 = 0x0A,OUT_AP10 = 0x09,OUT_AP = 0x0B,//������������죺2/10/50MHz���Զ���Ĭ�ϣ�
			OUT_AD2 = 0x0E,OUT_AD10 = 0x0D,OUT_AD = 0x0F//��������ã�A����©��D����2/10/50MHz���Զ���Ĭ�ϣ�
		};

	class gpio_conf
	{
	private:
		u32 CRL;
		u32 CRH;
		u32 BSRR;
	
	public:		
		
		GPIO_TypeDef* PPP_NAM;
		u8 CMODE;//������0xC�ı���
		u8 MODE;//������0xC
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
		}//��ʼ����������(��)���������ģʽ���������룩��λ���գ�
		
		bool pin(uint16_t bits);//����λֵ,��λ���ʱ����һλΪ1�����true������ģʽ��IDR�����ģʽ��ODR
		void port(uint16_t bits,bool ER);//д��λ
		int lock(uint16_t bits);//�������ã��ɹ�����0��ʧ�ܷ���1
		
		bool operator == (bool& ER)//����������Ϊ��ֵʹ��
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

		#define PAout(n)   BIT_ADDR(GPIOA_ODR_Addr,n)  //��� 
		#define PAin(n)    BIT_ADDR(GPIOA_IDR_Addr,n)  //���� 

		#define PBout(n)   BIT_ADDR(GPIOB_ODR_Addr,n)  //��� 
		#define PBin(n)    BIT_ADDR(GPIOB_IDR_Addr,n)  //���� 

		#define PCout(n)   BIT_ADDR(GPIOC_ODR_Addr,n)  //��� 
		#define PCin(n)    BIT_ADDR(GPIOC_IDR_Addr,n)  //���� 

		#define PDout(n)   BIT_ADDR(GPIOD_ODR_Addr,n)  //��� 
		#define PDin(n)    BIT_ADDR(GPIOD_IDR_Addr,n)  //���� 

		#define PEout(n)   BIT_ADDR(GPIOE_ODR_Addr,n)  //��� 
		#define PEin(n)    BIT_ADDR(GPIOE_IDR_Addr,n)  //����

		#define PFout(n)   BIT_ADDR(GPIOF_ODR_Addr,n)  //��� 
		#define PFin(n)    BIT_ADDR(GPIOF_IDR_Addr,n)  //����

		#define PGout(n)   BIT_ADDR(GPIOG_ODR_Addr,n)  //��� 
		#define PGin(n)    BIT_ADDR(GPIOG_IDR_Addr,n)  //����


	};
}
#endif
