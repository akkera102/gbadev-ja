#include "irq.arm.h"
#include "spr.arm.h"


//---------------------------------------------------------------------------
EWRAM_CODE void IrqInit(void)
{
	REG_IME = 0;

	INT_VECTOR   = (u32)IrqHandler;
	REG_IE       = IRQ_VBLANK | IRQ_VCOUNT;
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
		SprVBlank();

		REG_IRQ_WAITFLAGS |= IRQ_VBLANK;
	}

	if(flag & IRQ_VCOUNT)
	{
		SprVCount();
	}

	REG_IF  = flag;
	REG_IME = 1;
}
