#include "lib/gba.h"
#include "bg.h"
#include "irq.arm.h"
#include "key.h"

//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
int main(void)
{
	REG_WSCNT = 0x4317;

	BgInit();
	IrqInit();
	KeyInit();

	char str[32];

	for(;;)
	{
	    VBlankIntrWait();

		KeyExec();

		_Sprintf(str, "cnt:[%04x]", KeyGetCnt());
		BgAsciiDrawStr(0, 0, str);

		_Sprintf(str, "trg:[%04x]", KeyGetTrg());
		BgAsciiDrawStr(0, 1, str);

		_Sprintf(str, "off:[%04x]", KeyGetOff());
		BgAsciiDrawStr(0, 2, str);

		_Sprintf(str, "rep:[%04x]", KeyGetRep());
		BgAsciiDrawStr(0, 3, str);
	}
}
