#include "GPIO_typedef.h"

namespace gpio
{

	bool gpio_conf::pin(uint16_t bits)
	{
		if(MODE==0x00||MODE==0x04||0x08)
			return (bool)(PPP_NAM->IDR&BITS);
		else
			return (bool)(PPP_NAM->ODR&BITS);
	}

	void gpio_conf::port(uint16_t bits,bool ER)
	{
		if(ER)
			PPP_NAM->ODR|=bits;
		else
			PPP_NAM->ODR&=~bits;
		return;
	}

	int gpio_conf::lock(uint16_t bits)//锁定设置
	{
		u8 count=0;
		PPP_NAM->LCKR|=bits;
		PPP_NAM->LCKR|=(1<<16);
		PPP_NAM->LCKR&=~(0<<16);
		PPP_NAM->LCKR|=(1<<16);
		if(PPP_NAM->LCKR&(1<<16))
		{
			do{
				count++;
			}while((PPP_NAM->LCKR&(1<<16))||count<15);
			if(count<15)
				return 0;//跳出循环且原因为读到1，则锁定成功，返回0
		}
		return 0;//锁定失败，返回1
	}

	void gpio_conf::Update(void)
	{
		uint32_t cofmode=(uint32_t)MODE;//Mode Configuration
		u8 pin8=(u8)(0x00ff&BITS);//CRL Configuration
		uint32_t tmpin=0x0;
		for(u8 i=0;i<8;i++)
		{
			if (pin8&(1<<i))
			{
				tmpin|=(cofmode<<(i*4));
				cofmode=(uint32_t)MODE;
			}
		}
		CRL = tmpin;
		cofmode=(uint32_t)MODE;
		tmpin=0x0;
		pin8=(u8)((0x00ff&BITS)>>8);//CRH Configuration
		for(u8 i=0;i<8;i++)
		{
			if (pin8&(1<<i))
			{
				tmpin|=(cofmode<<(i*4));
				cofmode=(uint32_t)MODE;
			}
		}
		CRH = tmpin;
		
		if(MODE==0x08)
		{
			u16 pin16=BITS;
			if(CMODE==0x0C)//设置为上拉电阻输入，ODR默认为1，BSRR低16位置位
				for(u8 i=0;i<16;i++){
					if (pin16&(1<<i))
						BSRR|=(1<<i);
				}
			else//设置为下拉电阻输入，ODR默认为0，BSRR高16位置位
				for(u8 i=0;i<16;i++){
					if (pin16&(1<<i))
						BSRR|=(1<<(i+16));
				}
		}
	}

	void gpio_conf::Init(void)
	{
		PPP_NAM->CRL|=CRL;
		PPP_NAM->CRH|=CRH;
		PPP_NAM->BSRR|=BSRR;
	}

	void gpio_conf::DeInit(void)
	{
		uint32_t cofmode=(uint32_t)0x04;//Mode Configuration
		u8 pin8=(u8)(0x00ff&BITS);//CRL Configuration
		uint32_t tmpin=0x0;
		for(u8 i=0;i<8;i++)
		{
			if (pin8&(1<<i))
			{
				tmpin|=(cofmode<<(i*4));
				cofmode=(uint32_t)0x04;
			}
		}
		PPP_NAM->CRL = tmpin;
		cofmode=(uint32_t)0x04;
		tmpin=0x0;
		pin8=(u8)((0x00ff&BITS)>>8);//CRH Configuration
		for(u8 i=0;i<8;i++)
		{
			if (pin8&(1<<i))
			{
				tmpin|=(cofmode<<(i*4));
				cofmode=(uint32_t)0x04;
			}
		}
		PPP_NAM->CRH = tmpin;
	}

}
