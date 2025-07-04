#include "lib/gba.h"
#include "res.h"

//---------------------------------------------------------------------------
typedef struct {
	u32 chr;
	u32 map;
	u32 pal;
} ST_BG;

ST_BG BG3;
//---------------------------------------------------------------------------
void WaitForVsync(void)
{
	while(*(volatile u16*)0x4000006 >= 160) {};
	while(*(volatile u16*)0x4000006 <  160) {};
}
//---------------------------------------------------------------------------
void BGDrawChr(u32 mapNo, s32 x, s32 y, u16 chr)
{
	u16* BGMap = (u16*)MAP_BASE_ADR(mapNo) + x + (y * 32);

	*BGMap = chr;
}
//---------------------------------------------------------------------------
void BGDrawStr(u32 mapNo, s32 x, s32 y, char* str)
{
	u16 chr;
	s32 i=0, dx=0;

	for(;;)
	{
		chr = str[i++];

		if(chr == '\0')
		{
			return;
		}

		if(chr <= 0x7f)
		{
			// 1byte char
			BGDrawChr(mapNo, x + dx, y, chr);
		}
		else
		{
			// 2byte char
			switch(chr)
			{
				case 0x82: chr = str[i++] - 0x90 + 192; break;
				case 0x83: chr = str[i++] - 0x40 + 304; break;
				default:   chr = str[i++];              break;
			}

			BGDrawChr(mapNo, x + dx, y, chr);
		}

		dx++;
	}
}
//---------------------------------------------------------------------------
void BGSetPalData16(u16* palData, u32 palNo)
{
	u16* BGPal = BG_PALETTE + (16 * palNo);
	s32 i;

	for(i=0; i<16; i++)
	{
		*BGPal++ = *palData++;
	}
}
//---------------------------------------------------------------------------
void BGSetChrData(u16* chrData, s32 chrSize, u32 chrNo)
{
	u16* BGChr = CHAR_BASE_ADR(chrNo);
	s32  size  = chrSize / 2;
	s32  i;

	for(i=0; i<size; i++)
	{
		*BGChr++ = *chrData++;
	}
}
//---------------------------------------------------------------------------
void InitBG(void)
{
	BG3.chr =  1;
	BG3.map =  0;
	BG3.pal =  0;

	BGSetPalData16((u16*)&BGSmall8FontPal, BG3.pal);
	BGSetChrData  ((u16*)&BGSmall8FontTiles, BGSmall8FontTilesLen, BG3.chr);

	REG_BG3CNT = (BG_SIZE_0 | BG_16_COLOR | CHAR_BASE(BG3.chr) | MAP_BASE(BG3.map)); 

	SetMode(MODE_0 | BG3_ENABLE);
}
//---------------------------------------------------------------------------
int main(void)
{
	InitBG();

	BGDrawChr(BG3.map, 1, 1, 'A');

	BGDrawStr(BG3.map, 1, 3, "0123 ABCD abcd +-*/");
	BGDrawStr(BG3.map, 1, 4, "あいうえお アイウエオ");

	for(;;)
	{
	    WaitForVsync();
	}
}
