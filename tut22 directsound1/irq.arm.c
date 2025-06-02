#include "irq.arm.h"
#include "snd.arm.h"

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
IWRAM_CODE void IrqHandler(void)
{
	REG_IME  = 0;
	u16 flag = REG_IF;

	if(flag & IRQ_VBLANK)
	{
		SndIntrBgm();
		SndIntrSe();

		REG_IRQ_WAITFLAGS |= IRQ_VBLANK;
	}

	REG_IF  = flag;
	REG_IME = 1;
}
