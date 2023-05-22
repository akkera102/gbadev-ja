#include "lib/gba.h"
#include "irq.arm.h"
#include "bg.h"

//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
int main(void)
{
	REG_WSCNT = 0x4317;

	u32 i = 0xbeefbeef;
	u32 j;
	u32 k;

	char a[10];


	BgInit();
	IrqInit();

	BgDrawPrintf(0, 0, "&i    = %X", (u32)&i);
	BgDrawPrintf(0, 1, "&j    = %X", (u32)&j);
	BgDrawPrintf(0, 2, "&k    = %X", (u32)&k);

	for(i=0; i<10; i++)
	{
		BgDrawPrintf(0, 4+i, "&a[%d] = %X", i, (u32)&a[i]);
	}

	for(;;)
	{
		VBlankIntrWait();
	}
}
