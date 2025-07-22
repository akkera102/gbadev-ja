#include "lib/gba.h"
#include "irq.arm.h"
#include "key.h"
#include "font.h"
#include "spr.h"

//---------------------------------------------------------------------------
int main(void)
{
	REG_WSCNT = 0x4317;

	IrqInit();
	KeyInit();
	FontInit();
	SprInit();

	SetMode(MODE_3 | BG2_ENABLE | OBJ_ENABLE | OBJ_1D_MAP);

	s32 x = 40;
	s32 y = 40;
	u32 cnt;

	SprSetSize (0, OBJ_SIZE(1), OBJ_SQUARE, OBJ_16_COLOR);
	SprSetChr  (0, 512);
	SprSetXy   (0, x, y);

	SprSetRotateFlag(0, 0, OBJ_DOUBLE);
	SprSetScale(0, 200, 200);

	for(;;)
	{
		VBlankIntrWait();

		SprSetXy(0, x, y);
		FontDrawPrintf(16, 16, RGB5(31,31,31), "[%3d][%3d]", x, y);

		KeyExec();
		cnt = KeyGetCnt();

		if(cnt & KEY_UP   ) y--;
		if(cnt & KEY_DOWN ) y++;
		if(cnt & KEY_LEFT ) x--;
		if(cnt & KEY_RIGHT) x++;

		if(x > 240+32) x = 240+32;
		if(x <    -32) x =    -32;
		if(y > 160+32) y = 160+32;
		if(y <    -32) y =    -32;

		if(cnt & KEY_A) SprSetScale(0, 100, 100);
		if(cnt & KEY_B) SprSetScale(0, 200, 200);
	}
}
