#include "irq.arm.h"
#include "math.h"

//---------------------------------------------------------------------------
// main.c
extern vs32 shakeAngle;		// ���h���1�������̈ʒu
extern vs32 shakeCycle;		// ���h��̎���
extern vs32 shakeCx;		// ���U��̕�


//---------------------------------------------------------------------------
EWRAM_CODE void IrqInit(void)
{
	REG_IME = 0;

	INT_VECTOR   = (u32)IrqHandler;
	REG_IE       = IRQ_VBLANK | IRQ_HBLANK;
	REG_DISPSTAT = LCDC_VBL | LCDC_HBL;

	REG_IME = 1;
}
//---------------------------------------------------------------------------
IWRAM_CODE void IrqHandler(void)
{
	REG_IME  = 0;
	u16 flag = REG_IF;

	if(flag & IRQ_HBLANK)
	{
		if(REG_VCOUNT < 160)
		{
			// ��������h�炷
			REG_BG1HOFS = MathSin(shakeAngle * shakeCycle + REG_VCOUNT) * shakeCx / 256;
		}
		else if(REG_VCOUNT == 227)
		{
			// ���̃t���[����VCOUNT 0�p
			REG_BG1HOFS = MathSin(shakeAngle * shakeCycle + 0) * shakeCx / 256;
		}
	}

	if(flag & IRQ_VBLANK)
	{
		REG_IRQ_WAITFLAGS |= IRQ_VBLANK;
	}

	REG_IF  = flag;
	REG_IME = 1;
}
