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

 	s32 bld = 10;
	u32 cnt;

	for(;;)
	{
	    VBlankIntrWait();

 		REG_BLDALPHA = BLEND_BALANCE(bld);

		KeyExec();
		cnt = KeyGetCnt();

 		if(cnt & KEY_UP  ) bld--;
 		if(cnt & KEY_DOWN) bld++;
 		if(bld <  0) bld =  0;
 		if(bld > 16) bld = 16;
	}
}
