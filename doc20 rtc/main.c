#include "lib/gba.h"
#include "irq.arm.h"
#include "bg.h"
#include "key.h"
#include "rtc.h"

//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
IWRAM_CODE int main(void)
{
	REG_WSCNT = 0x4317;

	BgInit();
	KeyInit();
	RtcInit();

	IrqInit();

	for(;;)
	{
		VBlankIntrWait();

		KeyExec();
		RtcExec();
	}
}
