#include "lib/gba.h"
#include "bg.h"
#include "irq.arm.h"
#include "rnd.h"
#include "key.h"

//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
int main(void)
{
	REG_WSCNT = 0x4317;

	BgInit();
	IrqInit();
	RndInit(5489UL);
	KeyInit();


	char str[32];

	u32 num[0x10];
	_Memset(&num, 0x00, sizeof(num));

	for(;;)
	{
//		VBlankIntrWait();
		KeyExec();

		// Stop
		if(KeyGetCnt() & KEY_A)
		{
			continue;
		}

		num[RndU32() & 0xf]++;

		for(s32 i=0; i<0x10; i++)
		{
			_Sprintf(str, "0x%x:%d", i, num[i]);
			BgAsciiDrawStr(0, i, str);
		}
	}
}
