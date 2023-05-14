#include "res.h"
#include "bg.h"


//bg0 ASCII
//bg1 みかちゃんフォント

//---------------------------------------------------------------------------
ST_BG Bg[BG_MAX_CNT];
ST_BG_FONT BgFont;

//---------------------------------------------------------------------------
EWRAM_CODE void BgInit()
{
	BgInitLcd();

	Bg0Init();
	Bg1Init();
//	Bg2Init();
//	Bg3Init();

	REG_DISPCNT = (MODE_0 | BG0_ON | BG1_ON | OBJ_1D_MAP);
	REG_BG0CNT  = (BG_SIZE_0 | BG_16_COLOR | Bg[0].tileBase | Bg[0].mapBase | 0);
	REG_BG1CNT  = (BG_SIZE_0 | BG_16_COLOR | Bg[1].tileBase | Bg[1].mapBase | 0);
//	REG_BG2CNT  = (BG_SIZE_0 | BG_16_COLOR | Bg[2].tileBase | Bg[2].mapBase | 2 | BG_WRAP);
//	REG_BG3CNT  = (BG_SIZE_0 | BG_16_COLOR | Bg[3].tileBase | Bg[3].mapBase | 3 | BG_WRAP);
}
//---------------------------------------------------------------------------
EWRAM_CODE void BgInitLcd()
{
	const u32 mapBase[]  = { 29, 30, 31,  0 };
	const u32 tileBase[] = {  0,  1,  3,  0 };
	volatile s32 i;

	for(i=0; i<BG_MAX_CNT; i++)
	{
		Bg[i].mapBase     = MAP_BASE(mapBase[i]);
		Bg[i].mapBaseAdr  = MAP_BASE_ADR(mapBase[i]);
		Bg[i].tileBase    = TILE_BASE(tileBase[i]);
		Bg[i].tileBaseAdr = TILE_BASE_ADR(tileBase[i]);
	}

	for(i=0; i<32*32; i++)
	{
		Bg[0].mapBaseAdr[i] = 0;
		Bg[1].mapBaseAdr[i] = 0;
		Bg[2].mapBaseAdr[i] = 0;
		Bg[3].mapBaseAdr[i] = 0;
	}

	for(i=0; i<0x2000; i++)
	{
		Bg[0].tileBaseAdr[i] = 0;
		Bg[1].tileBaseAdr[i] = 0;
		Bg[2].tileBaseAdr[i] = 0;
		Bg[3].tileBaseAdr[i] = 0;
	}
}
//---------------------------------------------------------------------------
// ASCIIフォントを設定します
EWRAM_CODE void Bg0Init()
{
	volatile s32 i;

	for(i=0; i<4096; i++)
	{
		Bg[0].tileBaseAdr[i] = font_asciiTiles[i];
	}

	for(i=0; i<16; i++)
	{
		BG_PALETTE[i]  = font_asciiPal[i];
	}
}
//---------------------------------------------------------------------------
// みかちゃんフォントを設定します
EWRAM_CODE void Bg1Init()
{
	volatile s32 i;

	for(i=0; i<32*32; i++)
	{
		Bg[1].mapBaseAdr[i] = i + (1<<12);
	}

	for(i=0; i<16; i++)
	{
		BG_PALETTE[i+16] = font_mikaPal[i];
	}
}
//---------------------------------------------------------------------------
EWRAM_CODE void Bg2Init()
{
	// EMPTY
}
//---------------------------------------------------------------------------
EWRAM_CODE void Bg3Init()
{
	// EMPTY
}
//---------------------------------------------------------------------------
EWRAM_CODE void BgAsciiDrawStr(s32 x, s32 y, char* s)
{
	u16* map = &Bg[0].mapBaseAdr[x + y * 32];

	while(*s != NULL)
	{
		*map++ = *s++ - ' ';
	}
}
//---------------------------------------------------------------------------
EWRAM_CODE void BgFontInit()
{
	_Memset((u8*)&BgFont, 0x00, sizeof(ST_BG_FONT));

	BgFont.pDat = (u16*)&font_mikaTiles;
	BgFont.pCct = (u8*)&cct_mika_bin + sizeof(ST_CCT_HEAD);
}
//---------------------------------------------------------------------------
EWRAM_CODE void BgFontDrawStr(s32 x, s32 y, char* str)
{
	s32 i = 0;
	u16 chr;

	for(;;)
	{
		chr = str[i++];

		if(chr == '\0' || chr == CR || chr == LF)
		{
			return;
		}

		if(_IsSJIS(chr) == FALSE)
		{
			continue;
		}

		chr = (chr << 8) | str[i++];

		BgFontDrawChr(x, y, chr);
		x++;

		if(x >= BG_FONT_SCX)
		{
			x = 0;
			y++;

			if(y >= BG_FONT_SCY)
			{
				return;
			}
		}
	}
}
//---------------------------------------------------------------------------
EWRAM_CODE void BgFontDrawChr(s32 x, s32 y, u16 chr)
{
	u16 idx = BgFontGetIdx(chr);
	s32 i;

	u16* s1 = BgFont.pDat + idx * BG_FONT_DAT_SIZE / 2;
	u16* s2 = s1 + 32 / 2;
	u16* s3 = s2 + 32 / 2;
	u16* s4 = s3 + 32 / 2;

	if(x & 0x1)
	{
		u16* d1 = Bg[1].tileBaseAdr + y*1024 + (((((x+1)/2)*3)-2) * 32 / 2) + 1;
		u16* d2 = d1 + 15;
		u16* d3 = d1 + 512;
		u16* d4 = d2 + 512;

		for(i=0; i<8; i++)
		{
			*d1++ = *s1++;
			d1++;

			*d2++ = *s1++;
			*d2++ = *s2++;
			s2++;
		}

		for(i=0; i<6; i++)
		{
			*d3++ = *s3++;
			d3++;

			*d4++ = *s3++;
			*d4++ = *s4++;
			s4++;
		}
	}
	else
	{
		u16* d1 = Bg[1].tileBaseAdr + y*1024 + ((x/2)*3) * 32 / 2;
		u16* d2 = d1 + 32 / 2;
		u16* d3 = d1 + 512;
		u16* d4 = d3 + 32 / 2;

		for(i=0; i<8; i++)
		{
			*d1++ = *s1++;
			*d1++ = *s1++;

			*d2++ = *s2++;
			d2++;
			s2++;
		}

		for(i=0; i<6; i++)
		{
			*d3++ = *s3++;
			*d3++ = *s3++;

			*d4++ = *s4++;
			d4++;
			s4++;
		}
	}
}
//---------------------------------------------------------------------------
EWRAM_CODE u16 BgFontGetIdx(u16 code)
{
	if(_IsSJIS(HIBYTE(code)) == FALSE)
	{
		return BG_FONT_INVALID_INDEX;
	}


	// level 1 ---------------------------------
	u16 c0 = HIBYTE(code) >> 5;
	u16 c1 = HIBYTE(code) & 0x1f;
	u16 i1;

	if(c0 == 4)
	{
		// 80-9F
		i1 = ((u16*)BgFont.pCct)[c1];
	}
	else
	{
		// E0-FF
		i1 = ((u16*)BgFont.pCct)[c1 + 32];
	}

	if(i1 == 0)
	{
		return BG_FONT_INVALID_INDEX;
	}


	// level 2 ---------------------------------
	u16 c2 = LOBYTE(code) >> 6;
	u16 i2 = ((u16*)(BgFont.pCct + i1))[c2];

	if(i2 == 0)
	{
		return BG_FONT_INVALID_INDEX;
	}

	ST_XCCTENT* pXccTent = (ST_XCCTENT*)(BgFont.pCct + i2);
	ST_XCCT*    pXcct    = (ST_XCCT*)(BgFont.pCct + i2 + sizeof(ST_XCCTENT));


	// level 3 ---------------------------------
	u16 c3 = LOBYTE(code) & 0x3f;
	u16 i;

	for(i=0; i<pXccTent->count; i++)
	{
		if(c3 >= pXcct->start && c3 <= pXcct->end)
		{
			return pXcct->offset + (c3 - pXcct->start);
		}

		pXcct++;
	}

	return BG_FONT_INVALID_INDEX;
}
