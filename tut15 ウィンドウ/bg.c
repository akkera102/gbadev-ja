#include "res.h"
#include "bg.h"


//bg0 ASCII
//bg1 mask
//bg2 stage

//---------------------------------------------------------------------------
ST_BG Bg[BG_MAX_CNT];

//---------------------------------------------------------------------------
EWRAM_CODE void BgInit()
{
	BgInitLcd();

	Bg0Init();
	Bg1Init();
//	Bg2Init();
//	Bg3Init();

	REG_DISPCNT = (MODE_0 | BG0_ON | BG1_ON | WIN0_ENABLE);
	REG_BG0CNT  = (BG_SIZE_0 | BG_16_COLOR | Bg[0].tileBase | Bg[0].mapBase | 0);
	REG_BG1CNT  = (BG_SIZE_0 | BG_16_COLOR | Bg[1].tileBase | Bg[1].mapBase | 0);
//	REG_BG2CNT  = (BG_SIZE_0 | BG_16_COLOR | Bg[2].tileBase | Bg[2].mapBase | 0 | BG_SIZE_1);
//	REG_BG3CNT  = (BG_SIZE_0 | BG_16_COLOR | Bg[3].tileBase | Bg[3].mapBase | 3 | BG_WRAP);

}
//---------------------------------------------------------------------------
EWRAM_CODE void BgInitLcd()
{
	const u32 mapBase[]  = { 11, 12,  0,  0 };
	const u32 tileBase[] = {  0,  2,  0,  0 };
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
EWRAM_CODE void Bg0Init()
{
	vu32 i;

	for(i=0; i<imageTilesLen/2; i++)
	{
		Bg[0].tileBaseAdr[i] = imageTiles[i];
	}

	for(i=0; i<imagePalLen/2; i++)
	{
		BG_PALETTE[i]  = imagePal[i];
	}

	for(i=0; i<32*20; i++)
	{
		Bg[0].mapBaseAdr[i] = i;
	}
}
//---------------------------------------------------------------------------
EWRAM_CODE void Bg1Init()
{
	vu32 i;

	for(i=0; i<image2TilesLen/2; i++)
	{
		Bg[1].tileBaseAdr[i] = image2Tiles[i];
	}

	for(i=0; i<image2PalLen/2; i++)
	{
		BG_PALETTE[16+i]  = image2Pal[i];
	}

	for(i=0; i<32*20; i++)
	{
		Bg[1].mapBaseAdr[i] = i | (1 << 12);
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
