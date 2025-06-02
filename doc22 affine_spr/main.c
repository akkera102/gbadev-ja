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


	s32 x  = 240/2 - 64/2;
	s32 y  = 160/2 - 64/2;

	s32 pa = 0x0100;
	s32 pb = 0x0000;
	s32 pc = 0x0000;
	s32 pd = 0x0100;
	s32 ta = pa;
	s32 tb = pb;
	s32 tc = pc;
	s32 td = pd;

	s32 angle = 0;
	bool isDouble = false;

	// metro
	SprSetSize(0, OBJ_SIZE(3), OBJ_SQUARE, OBJ_16_COLOR);
	SprSetChr (0, 0);
	SprSetPal (0, 0);
	SprSetRotScale(0, 0, true);

	// Shadow
	SprSetSize(1, OBJ_SIZE(3), OBJ_SQUARE, OBJ_16_COLOR);
	SprSetChr (1, 0);
	SprSetPal (1, 1);
	SprSetScaleRot(1, 0x0100, 0, 0, 0x0100);
	SprSetRotScale(1, 1, true);

	for(;;)
	{
		VBlankIntrWait();


		s32 ss = MathSin(angle);
		s32 cc = MathCos(angle);
		s32 sa =  cc;
		s32 sb = -ss;
		s32 sc =  ss;
		s32 sd =  cc;

		pa = (ta*sa + tb*sc) >> 8;
		pb = (ta*sb + tb*sd) >> 8;
		pc = (tc*sa + td*sc) >> 8;
		pd = (tc*sb + td*sd) >> 8;

		SprSetScaleRot(0, pa, pb, pc, pd);
		SprSetXy(0, x, y);
		SprSetXy(1, x, y);
		SprSetDubleFlag(0, 0, isDouble);
		SprSetDubleFlag(1, 1, isDouble);

		BgAsciiDrawPrintf(1, 17, "P=|%4X %4X|", pa, pb);
		BgAsciiDrawPrintf(1, 18, "  |%4X %4X|", pc, pd);



		KeyExec();
		u16 cnt = KeyGetCnt();
		u16 trg = KeyGetTrg();

		// START+SELECT: Reset
		if((trg & KEY_START) && (trg & KEY_SELECT))
		{
			x  = 240/2 - 64/2;
			y  = 160/2 - 64/2;

			pa = 0x0100;
			pb = 0x0000;
			pc = 0x0000;
			pd = 0x0100;
			ta = pa;
			tb = pb;
			tc = pc;
			td = pd;

			angle = 0;
			isDouble = false;
			continue;
		}

		// START: Double-size flag
		if(trg & KEY_START)
		{
			if(isDouble == false)
			{
				x -= 64/2;
				y -= 64/2;
				isDouble = true;
			}
			else
			{
				x += 64/2;
				y += 64/2;
				isDouble = false;
			}
			continue;
		}

		// UP, DOWN, LEFT, RIGHT+SELECT: Move
		if((cnt & KEY_UP)    && (cnt & KEY_SELECT))
		{
			y--;
			continue;
		}

		if((cnt & KEY_DOWN)  && (cnt & KEY_SELECT))
		{
			y++;
			continue;
		}

		if((cnt & KEY_LEFT)  && (cnt & KEY_SELECT))
		{
			x--;
			continue;
		}

		if((cnt & KEY_RIGHT) && (cnt & KEY_SELECT))
		{
			x++;
			continue;
		}

		// A+SELECT: Scales x down
		if((cnt & KEY_A) && (cnt & KEY_SELECT))
		{
			ta += 4;
			continue;
		}
		// A: Scales x up
		if(cnt & KEY_A)
		{
			ta -= 4;
			continue;
		}

		// B+SELECT: Scales y down
		if((cnt & KEY_B) && (cnt & KEY_SELECT))
		{
			td += 4;
			continue;
		}
		// A: Scales x up
		if(cnt & KEY_B)
		{
			td -= 4;
			continue;
		}


		// LEFT: Shear x down
		if(cnt & KEY_LEFT)
		{
			tb -= 4;
			continue;
		}

		// RIGHT: Shear x up
		if(cnt & KEY_RIGHT)
		{
			tb += 4;
			continue;
		}

		// DOWN: Shear y down
		if(cnt & KEY_DOWN)
		{
			tc -= 4;
			continue;
		}

		// UP: Shear y up
		if(cnt & KEY_UP)
		{
			tc += 4;
			continue;
		}

		// L: Rotates left
		if(cnt & KEY_L)
		{
			angle += 128;
			continue;
		}

		// R Rotates right
		if(cnt & KEY_R)
		{
			angle -= 128;
			continue;
		}
	}
}
