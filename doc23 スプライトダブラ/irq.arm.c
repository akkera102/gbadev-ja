#include "irq.arm.h"
#include "spr.arm.h"
#include "main.h"

//---------------------------------------------------------------------------
// main.c
extern ST_MAIN Main;


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
		Main.frameCount++;
		Main.fpsTimer++;

		if(Main.fpsTimer == 60)
		{
			Main.fps = Main.fpsCount;
			Main.fpsTimer = 0;
			Main.fpsCount = 0;
		}

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
