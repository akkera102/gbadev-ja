#include "lib/gba.h"
#include "irq.arm.h"
#include "key.h"
#include "mode3.h"

//---------------------------------------------------------------------------

typedef struct {
	s32 cur;	// Œ»Ý’l
	s32 min;
	s32 max;
	s32 adj;	// ‘Œ¸’l
} ST_PARAM;

//---------------------------------------------------------------------------

const u32 wave[8*13] = { 
	// 0 ?
	0x02468ace,0xfdb97531,0x02468ace,0xfdb97531,
	0x2064a8ec,0xdf9b5713,0x2064a8ec,0xdf9b5713,
	// 1 double saw
	0x01234567,0x89abcdef,0x01234567,0x89abcdef,
	0x10325476,0x98badcfe,0x10325476,0x98badcfe,
	// 2 ?
	0x88808fff,0x88808880,0x00080888,0x80008000,
	0x8808f8ff,0x88088808,0x00808088,0x08000800,
	// 3 ?
	0x34455667,0x899aabbc,0x34455667,0x899aabbc,
	0x43546576,0x98a9bacd,0x43546576,0x98a9bacb,
	// 4 ?
	0x23345667,0x899abcde,0x23345667,0x899abcde,
	0x32436576,0x98a9cded,0x32436576,0x98a9cded,
	// 5 ?
	0xacddda48,0x3602cf16,0x2c04e52c,0xacddda48,
	0xcaddad84,0x6320fc61,0xc2405ec2,0xcaddad84,
	// 6 triangular
	0x10325476,0x67452301,0xefcdab89,0x98badcfe,
	0x01234567,0x76543210,0xfedcba98,0x89abcdef,
	// 7 ?
	0x01234567,0x89abcdef,0xffffffff,0xfedcba98,
	0x10325376,0x98badcfe,0xffffffff,0xefcdab89,
	// 8 ?
	0xf0eeca86,0x0a468ace,0xffeeca86,0x0a468ace,
	0x0feeac68,0xa064a8ec,0xffeeac68,0xa064a8ec,
	// 9 ?
	0x7ec9cea7,0xcfe8ab72,0x8d757203,0x85136317,
	0xe79cec7a,0xfc8eba27,0xd8572730,0x58313671,
	// 10 ?
	0xfedcba98,0x76543210,0x76543210,0x44002200,
	0xefcdab89,0x67452301,0x67452301,0x44002200,
	// 11 ?
	0x02468ace,0xffffffff,0xeca86420,0x00448844,
	0x2064a8ec,0xffffffff,0xce8a4602,0x00448844,
	// 12 ?
	0xFFFFFFFF,0xFFFFFFFF,0x00000000,0x00000000,
	0x00000000,0x00000000,0xFFFFFFFF,0xFFFFFFFF,
};

const u8 score[32*3] = {
	// 0
	19,8,15,8,19,15,8,15,19,15,8,15,19,8,15,19,5,12,17,12,5,17,12,17,5,17,12,17,5,12,17,5,
	// 1
	19,19,24,19,24,24,19,27,19,24,19,26,24,19,24,24,17,17,24,17,24,24,17,12,24,12,19,24,12,19,24,24,
	// 2
	31,31,36,31,36,36,31,39,31,36,31,38,36,31,36,36,29,29,36,29,36,36,29,24,36,24,31,36,24,31,36,36,
};

const u16 freq[12*6] = {
	// C      C+       D      D+       E       F      F+       G      G+       A      A+       B
	  44,    156,    262,    363,    457,    547,    631,    710,    786,    854,    923,    986,   // o3
	1046,   1102,   1155,   1205,   1253,   1297,   1339,   1379,   1417,   1452,   1486,   1517,   // o4
	1546,   1575,   1602,   1627,   1650,   1673,   1694,   1714,   1732,   1750,   1767,   1783,   // o5
	1798,   1812,   1825,   1837,   1849,   1860,   1871,   1881,   1890,   1899,   1907,   1915,   // o6
	1923,   1930,   1936,   1943,   1949,   1954,   1959,   1964,   1969,   1974,   1978,   1982,   // o7
	1985,   1988,   1992,   1995,   1998,   2001,   2004,   2006,   2009,   2011,   2013,   2015,   // o8
};

//---------------------------------------------------------------------------
void LoadWave(ST_PARAM* p, u32 select)
{
	u32 inst = p[0].cur * 8 + select * 4;

	DMA_Copy(3, (u32)&wave[inst], (u32)WAVE_RAM, DMA_SRC_INC | DMA_DST_INC | DMA32 | 4);

	// bank number
	if(p[1].cur == 0)
	{
		p[7].cur = inst;
	}
	else
	{
		p[8].cur = inst;
	}

	p[1].cur = (p[1].cur == 0) ? 1 : 0;
	REG_SOUND3CNT_L^= SOUND3_SETBANK(1);
}
//---------------------------------------------------------------------------
void DrawParam(ST_PARAM* p)
{
	// wave, bank number
	Mode3DrawPrintf(1,  6, "%02X", p[0].cur);
	Mode3DrawPrintf(1,  7, "%02X", p[1].cur);

	// bank mode
	if(p[2].cur == 0) Mode3DrawPrintf(1,  8, "1x32");
	else              Mode3DrawPrintf(1,  8, "1x64");

	// length, pattern, pan, note
	Mode3DrawPrintf(1,  9, "%02X", p[3].cur);
	Mode3DrawPrintf(1, 10, "%02X", p[4].cur);
	Mode3DrawPrintf(1, 11, "%02X", p[5].cur);
	Mode3DrawPrintf(1, 12, "%02X", p[6].cur);

	if(REG_SOUND3CNT_L & SOUND3_SETBANK(1))
	{
		Mode3DrawPrintf(1, 13, "1");
	}
	else
	{
		Mode3DrawPrintf(1, 13, "0");
	}
}
//---------------------------------------------------------------------------
void DrawWave(ST_PARAM* p)
{
	u32 inst1 = p[7].cur;
	u32 inst2 = p[8].cur;

	// bank0 wave
	Mode3DrawPrintf(10, 1, "%08X", wave[inst1+0]);
	Mode3DrawPrintf(10, 2, "%08X", wave[inst1+1]);
	Mode3DrawPrintf(10, 3, "%08X", wave[inst1+2]);
	Mode3DrawPrintf(10, 4, "%08X", wave[inst1+3]);

	// bank1 wave
	Mode3DrawPrintf(29, 1, "%08X", wave[inst2+0]);
	Mode3DrawPrintf(29, 2, "%08X", wave[inst2+1]);
	Mode3DrawPrintf(29, 3, "%08X", wave[inst2+2]);
	Mode3DrawPrintf(29, 4, "%08X", wave[inst2+3]);
}
//---------------------------------------------------------------------------
int main(void)
{
	REG_WSCNT = 0x4317;

	Mode3Init();
	IrqInit();
	KeyInit();


	ST_PARAM param[9];

	_Memset(&param, 0x00, sizeof(param));

	param[0].cur = 0x1;		// wave
	param[1].cur = 0x0;		// bank number
	param[2].cur = 0x0;		// dimension
	param[3].cur = 0xeb;	// sound length
	param[4].cur = 0x0;		// sound pattern
	param[5].cur = 0x0;		// pan
	param[6].cur = 0x0;		// tone
	param[7].cur = 0x0;		// bank0 wave
	param[8].cur = 0x0;		// bank1 wave

	param[0].min = 0x0;
	param[1].min = 0x0;
	param[2].min = 0x0;
	param[3].min = 0x0;
	param[4].min = 0x0;
	param[5].min = 0x0;
	param[6].min = 0x0;

	param[0].max = 0xc;
	param[1].max = 0x1;
	param[2].max = 0x1;
	param[3].max = 0xff;
	param[4].max = 0x2;
	param[5].max = 0x1;
	param[6].max = 0x1f;

	param[0].adj = 0x1;
	param[1].adj = 0x1;
	param[2].adj = 0x1;
	param[3].adj = 0x1;
	param[4].adj = 0x1;
	param[5].adj = 0x1;
	param[6].adj = 0x1;

	Mode3DrawStr(1,  0, "-----Bank 0------  -----Bank 1------");
	Mode3DrawStr(1,  1, "WAVERAM0:          WAVERAM0:        ");
	Mode3DrawStr(1,  2, "WAVERAM1:          WAVERAM1:        ");
	Mode3DrawStr(1,  3, "WAVERAM2:          WAVERAM2:        ");
	Mode3DrawStr(1,  4, "WAVERAM3:          WAVERAM3:        ");

	Mode3DrawStr(8,  6, "L/R : Change Wave");
	Mode3DrawStr(8,  7, "A   : Wave RAM Bank Number");
	Mode3DrawStr(8,  8, "B   : Wave RAM Dimension");
	Mode3DrawStr(8,  9, "U/D : Change Sound Length");
	Mode3DrawStr(8, 10, "L/R : Change Sound Pattern");
	Mode3DrawStr(8, 11, "STA : Toggle Stereo Auto-Pan");
	Mode3DrawStr(8, 12, "    : Note");
	Mode3DrawStr(8, 13, "    : Playback Bank Number");
	Mode3DrawStr(8, 14, "      (SOUND3CNT_L Wave Select)");

	REG_SOUNDCNT_X = 0x80;		// turn on sound circuit
	REG_SOUNDCNT_L = 0x4477;	// full volume, enable sound 3 to left and right
	REG_SOUNDCNT_H = 2;			// Overall output ratio - Full

	REG_SOUND3CNT_L = SOUND3_PLAY | SOUND3_STEP32 | SOUND3_SETBANK(1);
	REG_SOUND3CNT_H = TRILENVOL_100;
	REG_SOUND3CNT_X = TRIFREQ_RESET;

	LoadWave(param, 0);
	LoadWave(param, 0);

	DrawWave(param);
	DrawParam(param);

	u32 PanMask = 0x4000;
	u32 waitVblank = 0;

	bool isWave = false;
	bool isBank = false;
	bool isDimension = false;

	for(;;)
	{
	    VBlankIntrWait();

		DrawWave(param);
		DrawParam(param);

		KeyExec();
		u16 rep = KeyGetRep();
		u16 trg = KeyGetTrg();

		if(trg & KEY_L)
		{
			if(param[0].cur >  param[0].min)
			{
				param[0].cur--;
			}
			else
			{
				param[0].cur = param[0].max;
			}

			isWave = true;
		}

		if(trg & KEY_R)
		{
			if(param[0].cur <  param[0].max)
			{
				param[0].cur++;
			}
			else
			{
				param[0].cur = param[0].min;
			}

			isWave = true;
		}

		if(trg & KEY_A)
		{
			isBank = true;
		}

		if(trg & KEY_B)
		{
			isDimension = true;
		}

		if(rep & KEY_UP  && param[3].cur <  param[3].max)
		{
			param[3].cur++;
		}

		if(rep & KEY_DOWN && param[3].cur >  param[3].min)
		{
			param[3].cur--;
		}

		if(trg & KEY_RIGHT  && param[4].cur <  param[4].max)
		{
			param[4].cur++;
		}

		if(trg & KEY_LEFT && param[4].cur >  param[4].min)
		{
			param[4].cur--;
		}

		if(trg & KEY_START)
		{
			param[5].cur = (param[5].cur == 0) ? 1 : 0;
		}


		// wait vblank
		if(++waitVblank < 7)
		{
			continue;
		}
		waitVblank = 0;


		// length
		REG_SOUND3CNT_H = TRILENVOL_100 | param[3].cur;

		// pattern + note
		u32 t = param[4].cur * 32 + param[6].cur;
		u32 s = score[t];
		_ASSERT(t < 32*3 && s < 12*6);
		REG_SOUND3CNT_X = freq[s] | TRIFREQ_TIMED | TRIFREQ_RESET;

		// pan
		if(param[5].cur == 1) REG_SOUNDCNT_L  = (REG_SOUNDCNT_L & 0xBBFF) | PanMask;
		else                  REG_SOUNDCNT_L |= 0x4400;
		PanMask^=0x4400;

		// bank number
		if(isBank == true)
		{
			REG_SOUND3CNT_L ^= SOUND3_SETBANK(1);

			param[1].cur = (param[1].cur == 0) ? 1 : 0;
			isBank = false;
		}

		// dimension
		if(isDimension == true)
		{
			REG_SOUND3CNT_L^= SOUND3_STEP64;

			param[2].cur = (param[2].cur == 0) ? 1 : 0;
			isDimension = false;
		}

		// wave
		if(isWave == true)
		{
			REG_SOUND3CNT_L &= ~SOUND3_PLAY;

			if(param[2].cur == 0)
			{
				// 0 = One bank/32 digits
				LoadWave(param, 0);
			}
			else
			{
				// 1 = Two banks/64 digits
				LoadWave(param, 0);
				LoadWave(param, 1);
			}

			REG_SOUND3CNT_L |= SOUND3_PLAY;
			REG_SOUND3CNT_X |= TRIFREQ_RESET;

			isWave = false;
		}


		// note++
		if(param[6].cur++ >= param[6].max)
		{
			param[6].cur = 0;
		}
	}
}
