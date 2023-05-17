#include "lib/gba.h"
#include "irq.arm.h"
#include "bg.h"
#include "key.h"
#include "math.h"

//---------------------------------------------------------------------------
vs32 shakeAngle;		// â°óhÇÍÇÃ1é¸ä˙ì‡ÇÃà íu
vs32 shakeCycle;		// â°óhÇÍÇÃé¸ä˙
vs32 shakeCx;			// â°êUÇÍÇÃïù


//---------------------------------------------------------------------------
int main(void)
{
	REG_WSCNT = 0x4317;

	shakeAngle =  0;
	shakeCycle =  4;
	shakeCx    = 32;

	IrqInit();
	KeyInit();
	BgInit();

	u16 cnt, trg;

	for(;;)
	{
		VBlankIntrWait();

		BgAsciiDrawPrintf(1, 1, "cycle = [%3d]", shakeCycle);
		BgAsciiDrawPrintf(1, 2, "cx    = [%3d]", shakeCx);

		KeyExec();
		cnt = KeyGetCnt();
		trg = KeyGetTrg();

		if(trg & KEY_UP)    { shakeAngle=0; shakeCycle--; }
		if(trg & KEY_DOWN)  { shakeAngle=0; shakeCycle++; }
		if(cnt & KEY_LEFT)  { shakeAngle=0; shakeCx--;    }
		if(cnt & KEY_RIGHT) { shakeAngle=0; shakeCx++;    }

		shakeCycle = MathClamp(shakeCycle, 1, 32);
		shakeCx    = MathClamp(shakeCx, 1, 64);


		if(shakeAngle == Div(360, shakeCycle))
		{
			shakeAngle = 0;
		}
		shakeAngle++;

	}
}
