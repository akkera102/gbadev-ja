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

	REG_WSCNT = 0x0000;

	VBlankIntrWait();
	r = CodeRom();

	VBlankIntrWait();
	e = CodeEwram();

	VBlankIntrWait();
	i = CodeIwram();

	BgDrawPrintf(1, 1, "REG_WSCNT=0x0000");
	BgDrawPrintf(1, 2, "  ROM:%d", r);
	BgDrawPrintf(1, 3, "EWRAM:%d", e);
	BgDrawPrintf(1, 4, "IWRAM:%d", i);


	REG_WSCNT = 0x4317;

	VBlankIntrWait();
	r = CodeRom();

	VBlankIntrWait();
	e = CodeEwram();

	VBlankIntrWait();
	i = CodeIwram();

	BgDrawPrintf(1,  6, "REG_WSCNT=0x4317");
	BgDrawPrintf(1,  7, "  ROM:%d", r);
	BgDrawPrintf(1,  8, "EWRAM:%d", e);
	BgDrawPrintf(1,  9, "IWRAM:%d", i);


	REG_WSCNT = 0x0317;

	VBlankIntrWait();
	r = CodeRom();

	VBlankIntrWait();
	e = CodeEwram();

	VBlankIntrWait();
	i = CodeIwram();

	BgDrawPrintf(1, 11, "REG_WSCNT=0x0317(no prefetch)");
	BgDrawPrintf(1, 12, "  ROM:%d", r);
	BgDrawPrintf(1, 13, "EWRAM:%d", e);
	BgDrawPrintf(1, 14, "IWRAM:%d", i);


	for(;;)
	{
		VBlankIntrWait();
	}
}
