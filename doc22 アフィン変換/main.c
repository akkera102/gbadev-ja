#include "lib/gba.h"
#include "irq.arm.h"
#include "bg.h"
#include "key.h"
#include "spr.h"
#include "math.h"

//---------------------------------------------------------------------------
int main(void)
{
	REG_WSCNT = 0x4317;

	IrqInit();
	KeyInit();
	BgInit();
	SprInit();


	u16 cnt, trg;

	s32 x  = 240/2 - 64/2;
	s32 y  = 160/2 - 64/2;

	s16 pa = 0x0100;
	s16 pb = 0x0000;
	s16 pc = 0x0000;
	s16 pd = 0x0100;
	s16 ta = pa;
	s16 tb = pb;
	s16 tc = pc;
	s16 td = pd;

	s32 angle = 0;
	bool isDouble = FALSE;

	// metro
	SprSetSize (0, OBJ_SIZE(3), OBJ_SQUARE, OBJ_16_COLOR);
	SprSetChr  (0, 0);
	SprSetPal  (0, 0);

	// Shadow
	SprSetSize (1, OBJ_SIZE(3), OBJ_SQUARE, OBJ_16_COLOR);
	SprSetChr  (1, 0);
	SprSetPal  (1, 1);

	SprSetScaleRot(1, pa, pb, pc, pd);
	SprSetRotScale(1, 1, TRUE);

	for(;;)
	{
		VBlankIntrWait();

		BgAsciiDrawPrintf(1, 17, "P=|%4X %4X|", pa, pb);
		BgAsciiDrawPrintf(1, 18, "  |%4X %4X|", pc, pd);

		SprSetXy(0, x, y);
		SprSetXy(1, x, y);

		SprSetScaleRot(0, pa, pb, pc, pd);
		SprSetRotScale(0, 0, TRUE);

		SprSetDubleFlag(0, 0, isDouble);
		SprSetDubleFlag(1, 1, isDouble);


		KeyExec();
		cnt = KeyGetCnt();
		trg = KeyGetTrg();

		// START+SELECT: Reset
		if((trg & KEY_START) && (trg & KEY_SELECT))
		{
			x  = 240/2 - 64/2;
			y  = 160/2 - 64/2;

			pa = 0x0100;
			pb = 0x0000;
			pc = 0x0000;
			pd = 0x0100;

			ta = pa; tb = pb; tc = pc; td = pd; angle = 0;
			isDouble = FALSE;

			continue;
		}

		// START: Double-size flag
		if(trg & KEY_START)
		{
			isDouble = (isDouble == TRUE) ? FALSE : TRUE;
			continue;
		}

		// UP, DOWN, LEFT, RIGHT+SELECT: Move
		if((cnt & KEY_UP)    && (cnt & KEY_SELECT)) { y--; continue; }
		if((cnt & KEY_DOWN)  && (cnt & KEY_SELECT)) { y++; continue; }
		if((cnt & KEY_LEFT)  && (cnt & KEY_SELECT)) { x--; continue; }
		if((cnt & KEY_RIGHT) && (cnt & KEY_SELECT)) { x++; continue; }


		// A+SELECT: Scales x down
		if((cnt & KEY_A) && (cnt & KEY_SELECT))
		{
			pa += 4;
			ta = pa; tb = pb; tc = pc; td = pd; angle = 0;

			continue;
		}
		// A: Scales x up
		if(cnt & KEY_A)
		{
			pa -= 4;
			ta = pa; tb = pb; tc = pc; td = pd; angle = 0;

			continue;
		}

		// B+SELECT: Scales y down
		if((cnt & KEY_B) && (cnt & KEY_SELECT))
		{
			pd += 4;
			ta = pa; tb = pb; tc = pc; td = pd; angle = 0;

			continue;
		}
		// A: Scales x up
		if(cnt & KEY_B)
		{
			pd -= 4;
			ta = pa; tb = pb; tc = pc; td = pd; angle = 0;

			continue;
		}


		// LEFT: Shear x--
		if(cnt & KEY_LEFT)
		{
			pb -= 4;
			ta = pa; tb = pb; tc = pc; td = pd; angle = 0;

			continue;
		}

		// RIGHT: Shear x++
		if(cnt & KEY_RIGHT)
		{
			pb += 4;
			ta = pa; tb = pb; tc = pc; td = pd; angle = 0;

			continue;
		}

		// UP: Shear y++
		if(cnt & KEY_UP)
		{
			pc += 4;
			ta = pa; tb = pb; tc = pc; td = pd; angle = 0;

			continue;
		}

		// DOWN: Shear y--
		if(cnt & KEY_DOWN)
		{
			pc -= 4;
			ta = pa; tb = pb; tc = pc; td = pd; angle = 0;

			continue;
		}


		// L: Rotates left
		if(cnt & KEY_L)
		{
			angle += 128;

			s32 ss = MathSin(angle) >> 4;
			s32 cc = MathCos(angle) >> 4;

			s32 sa =  cc;
			s32 sb = -ss;
			s32 sc =  ss;
			s32 sd =  cc;

			pa = (ta*sa + tb*sc) >> 8;
			pb = (ta*sb + tb*sd) >> 8;
			pc = (tc*sa + td*sc) >> 8;
			pd = (tc*sb + td*sd) >> 8;

			continue;
		}

		// R Rotates right
		if(cnt & KEY_R)
		{
			angle -= 128;

			s32 ss = MathSin(angle) >> 4;
			s32 cc = MathCos(angle) >> 4;

			s32 sa =  cc;
			s32 sb = -ss;
			s32 sc =  ss;
			s32 sd =  cc;

			pa = (ta*sa + tb*sc) >> 8;
			pb = (ta*sb + tb*sd) >> 8;
			pc = (tc*sa + td*sc) >> 8;
			pd = (tc*sb + td*sd) >> 8;

			continue;
		}
	}
}
