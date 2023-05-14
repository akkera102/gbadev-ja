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

	REG_WININ  = WIN_0_BG1;
	REG_WINOUT = WIN_0_BG0;

	s32 ofx = 20;
	s32 ofy = 20;
	u16 cnt;

	for(;;)
	{
		VBlankIntrWait();

		KeyExec();
		cnt = KeyGetCnt();


		if(cnt & KEY_UP   ) ofy--;
		if(cnt & KEY_DOWN ) ofy++;
		if(cnt & KEY_LEFT ) ofx--;
		if(cnt & KEY_RIGHT) ofx++;

		if(ofx < 0)      ofx = 0;
		if(ofx > 240-64) ofx = 240-64;
		if(ofy < 0)      ofy = 0;
		if(ofy > 160-64) ofy = 160-64;

		REG_WIN0H = WIN_LEFT(ofx) | WIN_RIGHT(ofx+64);
		REG_WIN0V = WIN_TOP(ofy)  | WIN_DOWN(ofy+64);


		if(cnt & KEY_A)
		{
			REG_WININ  = WIN_0_BG1;
			REG_WINOUT = WIN_0_BG0;
		}
		if(cnt & KEY_B)
		{
			REG_WININ  = WIN_0_BG0;
			REG_WINOUT = WIN_0_BG1;
		}
	}
}
