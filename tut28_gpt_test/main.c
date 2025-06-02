#include "libgpt/gbt_player.h"
#include "lib/gba.h"
#include "irq.arm.h"
#include "bg.h"
#include "res.h"
#include "tool/template1.h"
#include "tool/template2.h"
#include "tool/template3.h"
#include "spr.h"
#include "key.h"

//---------------------------------------------------------------------------
int main(void)
{
	REG_WSCNT = 0x4317;

	BgInit();
	SprInit();
	KeyInit();
	IrqInit();

    gbt_play(template3, -1);
    gbt_loop(1);

	BgDrawPrintf(0, 0, "GBT Player demo");
	BgDrawPrintf(2, 12, "+A In_the_Town");
	BgDrawPrintf(2, 13, "+B Joyous_Takeoff");
	BgDrawPrintf(2, 14, "+L template");

	for(;;)
	{
		VBlankIntrWait();

		s32 order;
		s32 row;
		s32 tick;

		gbt_get_position(&order, &row, &tick);

		BgDrawPrintf(0, 1, "order : %2d", order);
		BgDrawPrintf(0, 2, "row   : %2d", row);
		BgDrawPrintf(0, 3, "tick  : %2d", tick);

		//               0  1  2  3  4  5  6  7  8  9 10 11
		//               c c+  d d+  e  f f+  g g+  a a+  b
		const u8 x[] = { 0, 2, 4, 6, 8,12,14,16,18,20,22,24};
		const u8 y[] = { 0,16, 0,16, 0, 0,16, 0,16, 0,16, 0};

		u32 oct, note, idx;

		// ch1
		idx  = gbt_get_ch1_arpeggio_freq_index0();
		oct  = Div(idx, 12);
		note = Mod(idx, 12);
		SprSetXy(0, 17 + oct*28 + x[note], 0+59 - y[note]);

		// ch2
		idx  = gbt_get_ch2_arpeggio_freq_index0();
		oct  = Div(idx, 12);
		note = Mod(idx, 12);
		SprSetXy(1, 17 + oct*28 + x[note], 4+59 - y[note]);

		// ch3
		idx  = gbt_get_ch3_arpeggio_freq_index0();
		oct  = Div(idx, 12);
		note = Mod(idx, 12);
		SprSetXy(2, 17 + oct*28 + x[note], 8+59 - y[note]);


		KeyExec();
		u16 trg = KeyGetTrg();

		if(trg & KEY_A)
		{
			gbt_play(template1, -1);
			gbt_loop(1);
		}

		if(trg & KEY_B)
		{
			gbt_play(template2, -1);
			gbt_loop(1);
		}

		if(trg & KEY_L)
		{
			gbt_play(template3, -1);
			gbt_loop(1);
		}
	}
}
