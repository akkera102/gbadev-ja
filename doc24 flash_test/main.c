#include "lib/gba.h"
#include "irq.arm.h"
#include "bg.h"
#include "key.h"
#include "flash.h"

//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
int main(void)
{
	REG_WSCNT = 0x4317;

	BgInit();
	KeyInit();
	IrqInit();

	FlashInit();
	FlashExec();

	for(;;)
	{
		VBlankIntrWait();

		KeyExec();
	}
}
