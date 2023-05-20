#include "lib/gba.h"
#include "irq.arm.h"
#include "key.h"
#include "mode3.h"

//---------------------------------------------------------------------------

typedef struct {
	s32 cur;
	s32 min;
	s32 max;
	s32 adj;	// ëùå∏íl
} ST_PARAM;

//---------------------------------------------------------------------------
ST_PARAM param[11];
s16 sel;

//---------------------------------------------------------------------------
void DrawMessage(void)
{
	Mode3DrawStr(0,  0, "  0x04000060 (REG_SOUND1CNT_L) = ");
	Mode3DrawStr(0,  1, "  0x04000062 (REG_SOUND1CNT_H) = ");
	Mode3DrawStr(0,  2, "  0x04000064 (REG_SOUND1CNT_X) = ");

	Mode3DrawStr(0,  4, "  Sweep Shifts    :");
	Mode3DrawStr(0,  5, "  Sweep Direction :");
	Mode3DrawStr(0,  6, "  Sweep Time      :");
	Mode3DrawStr(0,  7, "  Sound Lenght    :");
	Mode3DrawStr(0,  8, "  Wave Duty Cycle :");
	Mode3DrawStr(0,  9, "  Envlp Step Time :");
	Mode3DrawStr(0, 10, "  Envlp Step Dir  :");
	Mode3DrawStr(0, 11, "  Envlp Init Vol  :");
	Mode3DrawStr(0, 12, "  Frequency       :");
	Mode3DrawStr(0, 13, "  Loop Mode       :");
	Mode3DrawStr(0, 14, "  Resampling Freq :");
}
//---------------------------------------------------------------------------
void DrawParam(void)
{
	for(s32 i=0; i<9; i++)
	{
		Mode3DrawPrintf(20,  4+i, "%04X", param[i].cur);
	}

	if(param[1].cur == 0) Mode3DrawStr(25, 4+1, "(Add)");
	else                  Mode3DrawStr(25, 4+1, "(Sub)");

	switch(param[4].cur)
	{
	case 0: Mode3DrawStr(25, 4+4, "(12.5)"); break;
	case 1: Mode3DrawStr(25, 4+4, "(25)  "); break;
	case 2: Mode3DrawStr(25, 4+4, "(50)  "); break;
	case 3: Mode3DrawStr(25, 4+4, "(75)  "); break;
	}

	if(param[6].cur == 0) Mode3DrawStr(25, 4+6, "(Dec)");
	else                  Mode3DrawStr(25, 4+6, "(Inc)");

	if(param[9].cur == 0) Mode3DrawStr(20, 13, "Loop");
	else                  Mode3DrawStr(20, 13, "Time");

	switch(param[10].cur)
	{
	case 0: Mode3DrawStr(20, 14, "9-bits/32768 Hz "); break;
	case 1: Mode3DrawStr(20, 14, "8-bits/65536 Hz "); break;
	case 2: Mode3DrawStr(20, 14, "7-bits/131072 Hz"); break;
	case 3: Mode3DrawStr(20, 14, "6-bits/262144 Hz"); break;
	}


//	l = (sweeptime<<4)+(sweepdir<<3)+sweepshifts;
//	h = (envinit<<12)+(envdir<<11)+(envsteptime<<8)+(waveduty<<6)+soundlength;
//	x = (loopmode<<14)+sfreq

	u16 l, h, x;

	l = (param[2].cur<<4)  + (param[1].cur<< 3) + (param[0].cur);
	h = (param[7].cur<<12) + (param[6].cur<<11) + (param[5].cur<<8) + (param[4].cur<<6) + (param[3].cur);
	x = (param[9].cur<<14) + (param[8].cur);

	Mode3DrawPrintf(33, 0, "%04X", l);
	Mode3DrawPrintf(33, 1, "%04X", h);
	Mode3DrawPrintf(33, 2, "%04X", x);
}
//---------------------------------------------------------------------------
void DrawSelect(void)
{
	for(s32 i=0; i<11; i++)
	{
		Mode3DrawStr(0,  4+i, " ");
	}
	Mode3DrawStr(0, 4+sel, ">");
}
//---------------------------------------------------------------------------
int main(void)
{
	REG_WSCNT = 0x4317;

	Mode3Init();
	IrqInit();
	KeyInit();

	_Memset(&param, 0x00, sizeof(param));

	param[ 0].cur = 0x2;
	param[ 1].cur = 0x1;
	param[ 2].cur = 0x7;
	param[ 3].cur = 0x1;
	param[ 4].cur = 0x2;
	param[ 5].cur = 0x7;
	param[ 6].cur = 0x0;
	param[ 7].cur = 0xf;
	param[ 8].cur = 0x400;
	param[ 9].cur = 0x0;
	param[10].cur = 0x1;

	param[ 0].min = 0x0;
	param[ 1].min = 0x0;
	param[ 2].min = 0x0;
	param[ 3].min = 0x0;
	param[ 4].min = 0x0;
	param[ 5].min = 0x0;
	param[ 6].min = 0x0;
	param[ 7].min = 0x0;
	param[ 8].min = 0x0;
	param[ 9].min = 0x0;
	param[10].min = 0x0;

	param[ 0].max = 0x7;
	param[ 1].max = 0x1;
	param[ 2].max = 0xf;
	param[ 3].max = 0x3f;
	param[ 4].max = 0x3;
	param[ 5].max = 0x7;
	param[ 6].max = 0x1;
	param[ 7].max = 0xf;
	param[ 8].max = 0x800;
	param[ 9].max = 0x1;
	param[10].max = 0x3;

	param[ 0].adj = 0x1;
	param[ 1].adj = 0x1;
	param[ 2].adj = 0x1;
	param[ 3].adj = 0x1;
	param[ 4].adj = 0x1;
	param[ 5].adj = 0x1;
	param[ 6].adj = 0x1;
	param[ 7].adj = 0x1;
	param[ 8].adj = 0x10;
	param[ 9].adj = 0x1;
	param[10].adj = 0x1;

	bool is = FALSE;
	sel = 0;

	DrawMessage();
	DrawParam();
	DrawSelect();

	//turn on sound circuit
	REG_SOUNDCNT_X = 0x80;

	//full volume, enable sound 1 to left and right
	REG_SOUNDCNT_L=0x1177;

	// Overall output ratio - Full
	REG_SOUNDCNT_H = 2;

	for(;;)
	{
	    VBlankIntrWait();

		KeyExec();
		u16 rep = KeyGetRep();

		if(rep & KEY_UP && sel >  0)
		{
			sel--;
			DrawSelect();
		}

		if(rep & KEY_DOWN  && sel < 10)
		{
			sel++;
			DrawSelect();
		}

		if((rep & KEY_RIGHT) && (param[sel].cur < param[sel].max))
		{
				param[sel].cur += param[sel].adj;
				DrawParam();

				is = TRUE;
		}

		if((rep & KEY_LEFT) && (param[sel].cur > param[sel].min))
		{
				param[sel].cur -= param[sel].adj;
				DrawParam();

				is = TRUE;
		}

		if(is == TRUE)
		{
			u16 l, h, x;

			l = (param[2].cur<<4)  + (param[1].cur<< 3) + (param[0].cur);
			h = (param[7].cur<<12) + (param[6].cur<<11) + (param[5].cur<<8) + (param[4].cur<<6) + (param[3].cur);
			x = (param[9].cur<<14) + (param[8].cur);

			REG_SOUND1CNT_L = l;
			REG_SOUND1CNT_H = h;
			REG_SOUND1CNT_X = SOUND1_RESET+x;

			is = FALSE;
		}
	}
}
