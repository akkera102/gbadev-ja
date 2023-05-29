#include "bg.h"
#include "res.h"

//---------------------------------------------------------------------------
ST_BG Bg[BG_MAX_CNT];


//---------------------------------------------------------------------------
EWRAM_CODE void BgInit(void)
{
	BgInitLcd();

	Bg0Init();
	Bg1Init();
//	Bg2Init();
//	Bg3Init();

	REG_DISPCNT = (MODE_0 | BG0_ON | BG1_ON | OBJ_ENABLE | OBJ_1D_MAP);
	REG_BG0CNT  = (BG_SIZE_0 | BG_16_COLOR | Bg[0].tileBase | Bg[0].mapBase | 0);
	REG_BG1CNT  = (BG_SIZE_0 | BG_16_COLOR | Bg[1].tileBase | Bg[1].mapBase | 0);
//	REG_BG2CNT  = (BG_SIZE_0 | BG_16_COLOR | Bg[2].tileBase | Bg[2].mapBase | 2 | BG_WRAP);
//	REG_BG3CNT  = (BG_SIZE_0 | BG_16_COLOR | Bg[3].tileBase | Bg[3].mapBase | 3 | BG_WRAP);
}
//---------------------------------------------------------------------------
EWRAM_CODE void BgInitLcd(void)
{
	const u32 mapBase[]  = { 29, 30, 31,  0 };
	const u32 tileBase[] = {  0,  1,  3,  0 };
	s32 i;

	for(i=0; i<BG_MAX_CNT; i++)
	{
		Bg[i].mapBase     = MAP_BASE(mapBase[i]);
		Bg[i].mapBaseAdr  = MAP_BASE_ADR(mapBase[i]);
		Bg[i].tileBase    = TILE_BASE(tileBase[i]);
		Bg[i].tileBaseAdr = TILE_BASE_ADR(tileBase[i]);
	}
}
//---------------------------------------------------------------------------
EWRAM_CODE void Bg0Init(void)
{
	vs32 i;

	for(i=0; i<font_asciiTilesLen/2; i++)
	{
		Bg[0].tileBaseAdr[i] = font_asciiTiles[i];
	}

	for(i=0; i<16; i++)
	{
		BG_PALETTE[i] = font_asciiPal[i];
	}
}
//---------------------------------------------------------------------------
EWRAM_CODE void Bg1Init(void)
{
	vs32 i;

	for(i=0; i<bg_keyboardTilesLen/2; i++)
	{
		Bg[1].tileBaseAdr[i] = bg_keyboardTiles[i];
	}

	for(i=0; i<16; i++)
	{
		BG_PALETTE[16+i] = bg_keyboardPal[i];
	}

	for(i=0; i<32*20; i++)
	{
		Bg[1].mapBaseAdr[i] = i | (1 << 12);	// バレット番号1を選択
	}
}
//---------------------------------------------------------------------------
IWRAM_CODE void BgDrawStr(s32 x, s32 y, char* s)
{
	u16* map = &Bg[0].mapBaseAdr[x + y * 32];

	while(*s != NULL)
	{
		*map++ = *s++ - ' ';
	}
}
//---------------------------------------------------------------------------
IWRAM_CODE void BgDrawPrintf(s32 x, s32 y, char* format, ...)
{
	char s[100] ALIGN(4);

	char* ap;
	va_start(ap, format);
	_DoSprintf(s, format, ap);
	va_end(ap);

	BgDrawStr(x, y, s);
}
