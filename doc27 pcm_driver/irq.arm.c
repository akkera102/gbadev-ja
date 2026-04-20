#include "irq.arm.h"
#include "ad.arm.h"
#include "snd.arm.h"

//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
void IrqInit(void)
{
	REG_IME = 0;

	INT_VECTOR   = (u32)IrqHandler;
	REG_IE       = IRQ_VBLANK;
	REG_DISPSTAT = LCDC_VBL;

	REG_IME = 1;
}
//---------------------------------------------------------------------------
void IrqInitAd(void)
{
	REG_IME = 0;

	INT_VECTOR   = (u32)IrqHandlerAd;
	REG_IE       = IRQ_VBLANK | IRQ_VCOUNT;;
	REG_DISPSTAT = LCDC_VBL| LCDC_VCNT | VCOUNT(60);

	REG_IME = 1;
}
//---------------------------------------------------------------------------
void IrqInitSnd(void)
{
	REG_IME = 0;

	INT_VECTOR   = (u32)IrqHandlerSnd;
	REG_IE       = IRQ_VBLANK;
	REG_DISPSTAT = LCDC_VBL;

	REG_IME = 1;
}
//---------------------------------------------------------------------------
IWRAM_CODE void IrqHandler(void)
{
	REG_IME  = 0;
	u16 flag = REG_IF;

	if(flag & IRQ_VBLANK)
	{
		REG_IRQ_WAITFLAGS |= IRQ_VBLANK;
	}

	REG_IF  = flag;
	REG_IME = 1;
}
//---------------------------------------------------------------------------
IWRAM_CODE void IrqHandlerAd(void)
{
	REG_IME  = 0;
	u16 flag = REG_IF;

	if(flag & IRQ_VCOUNT)
	{
		AdIntrVcount();
	}

	if(flag & IRQ_VBLANK)
	{
		AdIntrVblank();

		REG_IRQ_WAITFLAGS |= IRQ_VBLANK;
	}

	REG_IF  = flag;
	REG_IME = 1;
}
//---------------------------------------------------------------------------
IWRAM_CODE void IrqHandlerSnd(void)
{
	REG_IME  = 0;
	u16 flag = REG_IF;

	if(flag & IRQ_VBLANK)
	{
		SndIntrVblank();

		REG_IRQ_WAITFLAGS |= IRQ_VBLANK;
	}

	REG_IF  = flag;
	REG_IME = 1;
}
