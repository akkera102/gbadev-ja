#include "lib/gba.h"
#include "irq.arm.h"
#include "key.h"
#include "mode3.h"

//---------------------------------------------------------------------------

typedef struct {
	s32 cur;	// åªç›íl
	s32 min;
	s32 max;
	s32 adj;	// ëùå∏íl
} ST_PARAM;

//---------------------------------------------------------------------------

const u16 freq[12*6] = {
	44,		// C3
	156,
	262,
	363,
	457,
	547,
	631,
	710,
	786,
	854,
	923,
	986,
	1046,	// C4
	1102,
	1155,
	1205,
	1253,
	1297,
	1339,
	1379,
	1417,
	1452,
	1486,
	1517,
	1546,	// C5
	1575,
	1602,
	1627,
	1650,
	1673,
	1694,
	1714,
	1732,
	1750,
	1767,
	1783,
	1798,	// C6
	1812,
	1825,
	1837,
	1849,
	1860,
	1871,
	1881,
	1890,
	1899,
	1907,
	1915,
	1923,	// C7
	1930,
	1936,
	1943,
	1949,
	1954,
	1959,
	1964,
	1969,
	1974,
	1978,
	1982,
	1985,	// C8
	1988,
	1992,
	1995,
	1998,
	2001,
	2004,
	2006,
	2009,
	2011,
	2013,
	2015,
}; 


//---------------------------------------------------------------------------
void DrawParam(ST_PARAM* p)
{
	Mode3DrawPrintf(20,  7+0, "%04X", p[0].cur);
	Mode3DrawPrintf(20,  7+1, "%04X", p[1].cur);
	Mode3DrawPrintf(20,  7+2, "%04X", p[2].cur);
	Mode3DrawPrintf(20,  7+3, "%04X", p[3].cur);
	Mode3DrawPrintf(20,  7+4, "%04X", p[4].cur);
	Mode3DrawPrintf(20,  7+5, "%04X", freq[p[5].cur]);
	Mode3DrawPrintf(20,  7+6, "%04X", p[6].cur);

	switch(p[1].cur)
	{
	case 0: Mode3DrawStr(25, 4+4, "(12.5)"); break;
	case 1: Mode3DrawStr(25, 4+4, "(25)  "); break;
	case 2: Mode3DrawStr(25, 4+4, "(50)  "); break;
	case 3: Mode3DrawStr(25, 4+4, "(75)  "); break;
	}

	if(p[3].cur == 0) Mode3DrawStr(25, 4+6, "(Dec)");
	else              Mode3DrawStr(25, 4+6, "(Inc)");

	switch(p[7].cur)
	{
	case 0: Mode3DrawStr(20, 14, "9-bits/32768 Hz "); break;
	case 1: Mode3DrawStr(20, 14, "8-bits/65536 Hz "); break;
	case 2: Mode3DrawStr(20, 14, "7-bits/131072 Hz"); break;
	case 3: Mode3DrawStr(20, 14, "6-bits/262144 Hz"); break;
	}

	u16 L, H;

	L = (p[4].cur<<12) + (p[3].cur<<11) + (p[2].cur<< 8) + (p[1].cur<< 6) + (p[0].cur);
	H = (p[6].cur<<14) + (freq[p[5].cur]);

	Mode3DrawPrintf(33, 0, "%04X", L);
	Mode3DrawPrintf(33, 1, "%04X", H);
}
//---------------------------------------------------------------------------
int main(void)
{
	REG_WSCNT = 0x4317;

	Mode3Init();
	IrqInit();
	KeyInit();


	ST_PARAM param[8];

	bool isSnd = FALSE;
	s16 sel = 0;

	_Memset(&param, 0x00, sizeof(param));

	param[ 0].cur = 0x0;
	param[ 1].cur = 0x0;
	param[ 2].cur = 0x7;
	param[ 3].cur = 0x0;
	param[ 4].cur = 0xF;
	param[ 5].cur = 0x0;
	param[ 6].cur = 0x0;
	param[ 7].cur = 0x3;

	param[ 0].min = 0x0;
	param[ 1].min = 0x0;
	param[ 2].min = 0x0;
	param[ 3].min = 0x0;
	param[ 4].min = 0x0;
	param[ 5].min = 0x0;
	param[ 6].min = 0x0;
	param[ 7].min = 0x0;

	param[ 0].max = 0x3f;
	param[ 1].max = 0x3;
	param[ 2].max = 0x7;
	param[ 3].max = 0x1;
	param[ 4].max = 0xF;
	param[ 5].max = 12*6-1;
	param[ 6].max = 0x1;
	param[ 7].max = 0x3;

	param[ 0].adj = 0x1;
	param[ 1].adj = 0x1;
	param[ 2].adj = 0x1;
	param[ 3].adj = 0x1;
	param[ 4].adj = 0x1;
	param[ 5].adj = 0x1;
	param[ 6].adj = 0x1;
	param[ 7].adj = 0x1;

	Mode3DrawStr(2,  0, "0x04000068 (REG_SOUND2CNT_L) = ");
	Mode3DrawStr(2,  1, "0x0400006C (REG_SOUND2CNT_H) = ");

//	Mode3DrawStr(2,  4, "Sweep Shifts    :");
//	Mode3DrawStr(2,  5, "Sweep Direction :");
//	Mode3DrawStr(2,  6, "Sweep Time      :");
	Mode3DrawStr(2,  7, "Sound Length    :");
	Mode3DrawStr(2,  8, "Wave Duty Cycle :");
	Mode3DrawStr(2,  9, "Envlp Step Time :");
	Mode3DrawStr(2, 10, "Envlp Step Dir  :");
	Mode3DrawStr(2, 11, "Envlp Init Vol  :");
	Mode3DrawStr(2, 12, "Frequency       :");
	Mode3DrawStr(2, 13, "Length Flag     :");
	Mode3DrawStr(2, 14, "Resampling Freq :");

	Mode3DrawStr(0, 7+sel, ">");
	DrawParam(param);

	REG_SOUNDCNT_X = 0x80;		// turn on sound circuit
	REG_SOUNDCNT_L = 0x2277;	// full volume, enable sound 2 to left and right
	REG_SOUNDCNT_H = 2;			// Overall output ratio - Full

	for(;;)
	{
	    VBlankIntrWait();

		KeyExec();
		u16 rep = KeyGetRep();
		u16 trg = KeyGetTrg();

		if(rep & KEY_UP && sel >  0)
		{
			Mode3DrawStr(0, 7+sel, " ");
			sel--;
			Mode3DrawStr(0, 7+sel, ">");
		}

		if(rep & KEY_DOWN  && sel < 7)
		{
			Mode3DrawStr(0, 7+sel, " ");
			sel++;
			Mode3DrawStr(0, 7+sel, ">");
		}

		if((rep & KEY_RIGHT) && (param[sel].cur < param[sel].max))
		{
				param[sel].cur += param[sel].adj;
				DrawParam(param);

				isSnd = TRUE;
		}

		if((rep & KEY_LEFT) && (param[sel].cur > param[sel].min))
		{
				param[sel].cur -= param[sel].adj;
				DrawParam(param);

				isSnd = TRUE;
		}

		if(isSnd == TRUE || trg & KEY_A)
		{
			u16 B, L, H;

			B = (param[7].cur<<14) + (REG_SOUNDBIAS & 0x3fff);
			L = (param[4].cur<<12) + (param[3].cur<<11) + (param[2].cur<< 8) + (param[1].cur<< 6) + (param[0].cur);
			H = (param[6].cur<<14) + freq[param[5].cur];

			REG_SOUNDBIAS   = B;
			REG_SOUND2CNT_L = L;
			REG_SOUND2CNT_H = H + TRIFREQ_RESET;

			isSnd = FALSE;
		}
	}
}
