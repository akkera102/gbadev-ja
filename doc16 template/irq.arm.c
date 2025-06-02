#include "irq.arm.h"
#include "main.h"

//---------------------------------------------------------------------------
extern ST_MAIN Main;

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
		ST_MAIN* p = &Main;

		p->frameCount++;
		p->fpsTimer++;

		if(p->fpsTimer == 60)
		{
			p->fps = p->fpsCount;
			p->fpsTimer = 0;
			p->fpsCount = 0;
		}

		REG_IRQ_WAITFLAGS |= IRQ_VBLANK;
	}

	REG_IF  = flag;
	REG_IME = 1;
}
