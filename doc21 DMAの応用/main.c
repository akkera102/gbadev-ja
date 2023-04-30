#include "lib/gba.h"
#include "bg.h"
#include "irq.arm.h"
#include "key.h"

//---------------------------------------------------------------------------
int main(void)
{
	REG_WSCNT = 0x4317;

	BgInit();
	IrqInit();
	KeyInit();

	char str[64];
	s32 rr=64, x0=120, y0=80;
	u16 cnt;


	for(;;)
	{
	    VBlankIntrWait();

		KeyExec();
		cnt = KeyGetCnt();

		if(cnt & KEY_UP   ) y0--;
		if(cnt & KEY_DOWN ) y0++;
		if(cnt & KEY_LEFT ) x0--;
		if(cnt & KEY_RIGHT) x0++;
		if(cnt & KEY_A    ) rr--;
		if(cnt & KEY_B    ) rr++;

		if(rr < 0)
		{
			rr= 0;
		}

		BgCreateWindowCircleDma(x0, y0, rr);

		_Sprintf(str, "%d %d | %d", x0, y0, rr);
		BgAsciiDrawStr(0, 1, "              ");
		BgAsciiDrawStr(1, 1, str);
	}
}
