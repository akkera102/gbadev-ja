#include "lib/gba.h"
#include "irq.arm.h"
#include "bg.h"
#include "code.h"

//---------------------------------------------------------------------------
int main(void)
{
	BgInit();
	IrqInit();

	s32 r, e, i;
	u16 ws;

	ws = *(volatile u16*)0x4000204;

	VBlankIntrWait();
	r = CodeRom();

	VBlankIntrWait();
	e = CodeEwram();

	VBlankIntrWait();
	i = CodeIwram();

	BgDrawPrintf(1, 1, "REG_WSCNT=0x%04X", ws);
	BgDrawPrintf(1, 2, "  ROM:%d", r);
	BgDrawPrintf(1, 3, "EWRAM:%d", e);
	BgDrawPrintf(1, 4, "IWRAM:%d", i);


	*(volatile u16*)0x4000204 = 0x4317;
	ws = *(volatile u16*)0x4000204;

	VBlankIntrWait();
	r = CodeRom();

	VBlankIntrWait();
	e = CodeEwram();

	VBlankIntrWait();
	i = CodeIwram();

	BgDrawPrintf(1,  6, "REG_WSCNT=0x%04X", ws);
	BgDrawPrintf(1,  7, "  ROM:%d", r);
	BgDrawPrintf(1,  8, "EWRAM:%d", e);
	BgDrawPrintf(1,  9, "IWRAM:%d", i);


	*(volatile u16*)0x4000204 = 0x0317;
	ws = *(volatile u16*)0x4000204;

	VBlankIntrWait();
	r = CodeRom();

	VBlankIntrWait();
	e = CodeEwram();

	VBlankIntrWait();
	i = CodeIwram();

	BgDrawPrintf(1, 11, "REG_WSCNT=0x%04X(no prefetch)", ws);
	BgDrawPrintf(1, 12, "  ROM:%d", r);
	BgDrawPrintf(1, 13, "EWRAM:%d", e);
	BgDrawPrintf(1, 14, "IWRAM:%d", i);


	for(;;)
	{
		VBlankIntrWait();
	}
}
