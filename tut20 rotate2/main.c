#include "lib/gba.h"
#include "irq.arm.h"
#include "spr.h"
#include "math.h"

//---------------------------------------------------------------------------
int main(void)
{
	REG_WSCNT = 0x4317;

	IrqInit();
	SprInit();


	s32 x  = 240/2 - 64/2;
	s32 y  = 160/2 - 64/2;
	s32 angle = 0;

	SprSetSize (0, OBJ_SIZE(3), OBJ_SQUARE, OBJ_16_COLOR);
	SprSetChr  (0, 0);
	SprSetPal  (0, 0);
	SprSetXy(0, x, y);
	SprSetRotScale(0, 0, TRUE);

	for(;;)
	{
		VBlankIntrWait();

		SprSetRotate(0, angle);

		angle++;

		if(angle > 360)
		{
			angle = 0;
		}
	}
}
