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

const u32 voice[8*12] = { 
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
};

const u8 tone[32*3] = {
	// 0
	19,8,15,8,19,15,8,15,19,15,8,15,19,8,15,19,5,12,17,12,5,17,12,17,5,17,12,17,5,12,17,5,
	// 1
	19,19,24,19,24,24,19,27,19,24,19,26,24,19,24,24,17,17,24,17,24,24,17,12,24,12,19,24,12,19,24,24,
	// 2
	31,31,36,31,36,36,31,39,31,36,31,38,36,31,36,36,29,29,36,29,36,36,29,24,36,24,31,36,24,31,36,36,
};

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
void LoadWav(s32 inst)
{
	DMA_Copy(3, (u32)&voice[inst * 4], (u32)WAVE_RAM, DMA_SRC_INC | DMA_DST_INC | DMA32 | 4);

	REG_SOUND3CNT_L^= SOUND3_SETBANK(1);
}
//---------------------------------------------------------------------------
void DrawParam(ST_PARAM* p)
{
	// voice
	// bank playing
	Mode3DrawPrintf(1,  6, "%02X", p[0].cur);
	Mode3DrawPrintf(1,  7, "%02X", p[1].cur);

	// bank mode
	if(p[2].cur == 0) Mode3DrawPrintf(1,  8, "Sing");
	else              Mode3DrawPrintf(1,  8, "Dual");

	// sound length
	// pattern
	// pan
	// note
	Mode3DrawPrintf(1, 10, "%02X", p[3].cur);
	Mode3DrawPrintf(1, 11, "%02X", p[4].cur);
	Mode3DrawPrintf(1, 12, "%02X", p[5].cur);
	Mode3DrawPrintf(1, 13, "%02X", p[6].cur);

	// bank
	u32 inst = p[0].cur * 4;

	if(REG_SOUND3CNT_L & SOUND3_SETBANK(1))
	{
		// bank1
		Mode3DrawPrintf(29, 1, "%08X", voice[inst+0]);
		Mode3DrawPrintf(29, 2, "%08X", voice[inst+1]);
		Mode3DrawPrintf(29, 3, "%08X", voice[inst+2]);
		Mode3DrawPrintf(29, 4, "%08X", voice[inst+3]);
	}
	else
	{
		// bank0
		Mode3DrawPrintf(10, 1, "%08X", voice[inst+0]);
		Mode3DrawPrintf(10, 2, "%08X", voice[inst+1]);
		Mode3DrawPrintf(10, 3, "%08X", voice[inst+2]);
		Mode3DrawPrintf(10, 4, "%08X", voice[inst+3]);
	}
}
//---------------------------------------------------------------------------
int main(void)
{
	REG_WSCNT = 0x4317;

	Mode3Init();
	IrqInit();
	KeyInit();


	ST_PARAM param[8];

	_Memset(&param, 0x00, sizeof(param));

	param[0].cur = 0x3;		// voice
	param[1].cur = 0x0;		// bank playing
	param[2].cur = 0x0;		// bank mode
	param[3].cur = 0xeb;	// sound length
	param[4].cur = 0x0;		// pattern
	param[5].cur = 0x0;		// pan
	param[6].cur = 0x0;		// tone

	param[0].min = 0x0;
	param[1].min = 0x0;
	param[2].min = 0x0;
	param[3].min = 0x0;
	param[4].min = 0x0;
	param[5].min = 0x0;
	param[6].min = 0x0;

	param[0].max = 0x17;
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
	Mode3DrawStr(1,  1, "WAVERAM0:          WAVERAM0: NoUse  ");
	Mode3DrawStr(1,  2, "WAVERAM1:          WAVERAM1:        ");
	Mode3DrawStr(1,  3, "WAVERAM2:          WAVERAM2:        ");
	Mode3DrawStr(1,  4, "WAVERAM3:          WAVERAM3:        ");

	Mode3DrawStr(8,  6, "L/R : Change Voice");
	Mode3DrawStr(8,  7, "A   : Swap playing bank");
	Mode3DrawStr(8,  8, "B   : Change bank mode");
	Mode3DrawStr(8,  9, "       (2x32or1x64samples)");
	Mode3DrawStr(8, 10, "U/D : Change sound length");
	Mode3DrawStr(8, 11, "L/R : Change sound Pattern");
	Mode3DrawStr(8, 12, "STA : Toggle stereo auto-pan");
	Mode3DrawStr(8, 13, "    : Tone");

	REG_SOUNDCNT_L = 0x4477;	// full volume, enable sound 3 to left and right
	REG_SOUNDCNT_H = 2;			// Overall output ratio - Full
	REG_SOUNDCNT_X = 0x80;		// turn on sound circuit

	REG_SOUND3CNT_L = SOUND3_PLAY | SOUND3_STEP32 | SOUND3_SETBANK(1);
	REG_SOUND3CNT_H = TRILENVOL_100;
	REG_SOUND3CNT_X = TRIFREQ_RESET;

	LoadWav(param[0].cur);
	DrawParam(param);

	u32 f, s;
	u32 PanMask = 0x4000;
	u32 wait = 0;

	bool isVoice = FALSE;
	bool isSwap  = FALSE;
	bool isDual  = FALSE;

	for(;;)
	{
	    VBlankIntrWait();

		DrawParam(param);


		KeyExec();
		u16 rep = KeyGetRep();
		u16 trg = KeyGetTrg();

		if(trg & KEY_L && param[0].cur >  param[0].min)
		{
			param[0].cur--;
			isVoice = TRUE;
		}

		if(trg & KEY_R && param[0].cur <  param[0].max)
		{
			param[0].cur++;
			isVoice = TRUE;
		}

		if(trg & KEY_A)
		{
			isSwap = TRUE;
		}

		if(trg & KEY_B)
		{
			isDual = TRUE;
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

		// wait
		if(wait++ < 6)
		{
			continue;
		}
		wait = 0;

		// length
		REG_SOUND3CNT_H = TRILENVOL_100 | param[3].cur;

		// pattern + note
		s = (param[4].cur << 5) + param[6].cur;
		f = tone[s];
		_ASSERT(s < 32*3 && f < 72);

		REG_SOUND3CNT_X = freq[f] | TRIFREQ_TIMED | TRIFREQ_RESET;

		// pan
		if(param[5].cur == 1)
		{
			REG_SOUNDCNT_L = (REG_SOUNDCNT_L & 0xBBFF) | PanMask;
		}
		else
		{
			REG_SOUNDCNT_L |= 0x4400;
		}
		PanMask^=0x4400;

		// voice
		if(isVoice == TRUE)
		{
			if(REG_SOUND3CNT_L & SOUND3_SETBANK(1))
			{
				// load sound in single bank mode
				// it uses to normal instrument so it sounds a bit crappy
				// but you get the idea...
				// you have to stop the sound before reloading
				// wave ram when using the single bank mode or
				// no reloading will take place
				// Sound init is required when restarting sound
				REG_SOUND3CNT_L &= ~SOUND3_PLAY; //stop sound

				LoadWav(param[0].cur);
				LoadWav(param[0].cur+2);

				REG_SOUND3CNT_L |= SOUND3_PLAY;
				REG_SOUND3CNT_X |= TRIFREQ_RESET; 
			}
			else
			{
				LoadWav(param[0].cur);	//load new instrument in dual-bank mode
			}

			isVoice = FALSE;
		}

		// swap play bank
		if(isSwap == TRUE)
		{
			param[1].cur = (param[1].cur == 0) ? 1 : 0;

			REG_SOUND3CNT_L ^= SOUND3_SETBANK(1);
			isSwap = FALSE;
		}

		// switch dual/single bank
		if(isDual == TRUE)
		{
			param[2].cur = (param[2].cur == 0) ? 1 : 0;

			REG_SOUND3CNT_L^= SOUND3_STEP64;
			isDual = FALSE;
		}

		// tone++
		if(param[6].cur++ >= param[6].max)
		{
			param[6].cur = 0;
		}
	}
}
