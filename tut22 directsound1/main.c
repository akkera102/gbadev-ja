#include "lib/gba.h"
#include "irq.arm.h"
#include "bg.h"
#include "key.h"
#include "snd.arm.h"
#include "res.h"

//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
int main(void)
{
	REG_WSCNT = 0x4317;

	BgInit();
	KeyInit();
	SndInit();

	IrqInit();

	BgDrawPrintf(0,  0, " L: c3 DO");
	BgDrawPrintf(0,  1, " R: d3 RE");
	BgDrawPrintf(0,  2, " A: e3 MI");
	BgDrawPrintf(0,  3, " B: f3 FA");
	BgDrawPrintf(0,  4, "LE: g3 SO");
	BgDrawPrintf(0,  5, "UP: a3 RA");
	BgDrawPrintf(0,  6, "DO: b3 SI");
	BgDrawPrintf(0,  7, "RI: c4 DO");

	BgDrawPrintf(0, 10, "KAERU NO UTA");
	BgDrawPrintf(0, 12, "L R A B A R L.");
	BgDrawPrintf(0, 13, "A B LE UP LE B A.");
	BgDrawPrintf(0, 14, "L L L L");
	BgDrawPrintf(0, 15, "L L R R A A B B");
	BgDrawPrintf(0, 16, "A R L.");


	for(;;)
	{
		VBlankIntrWait();

		KeyExec();
		u32 trg = KeyGetTrg();

		if(trg & KEY_L)     SndPlaySe((u8*)&_1_c3_bin, 16384, 0, false);
		if(trg & KEY_R)     SndPlaySe((u8*)&_2_d3_bin, 16384, 0, false);
		if(trg & KEY_A)     SndPlaySe((u8*)&_3_e3_bin, 16384, 0, false);
		if(trg & KEY_B)     SndPlaySe((u8*)&_4_f3_bin, 16384, 0, false);
		if(trg & KEY_LEFT)  SndPlaySe((u8*)&_5_g3_bin, 16384, 0, false);
		if(trg & KEY_UP)    SndPlaySe((u8*)&_6_a3_bin, 16384, 0, false);
		if(trg & KEY_DOWN)  SndPlaySe((u8*)&_7_b3_bin, 16384, 0, false);
		if(trg & KEY_RIGHT) SndPlaySe((u8*)&_8_c4_bin, 16384, 0, false);
	}
}
