#include "lib/gba.h"
#include "res.h"

#define BG_MAX_CNT 4

typedef struct {
	u32  mapBase;
	u16* mapBaseAdr;
	u32  tileBase;
	u16* tileBaseAdr;
} ST_BG;

//---------------------------------------------------------------------------
ST_BG Bg[BG_MAX_CNT];

//---------------------------------------------------------------------------
void WaitForVsync(void)
{
	while(*(vu16*)0x4000006 >= 160) {};
	while(*(vu16*)0x4000006 <  160) {};
}
//---------------------------------------------------------------------------
void BgInitMem(void)
{
	const u32 mapBase[]  = { 11, 12,  0,  0 };
	const u32 tileBase[] = {  0,  2,  0,  0 };
	vs32 i;

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
void BgInit(void)
{
	BgInitMem();

	REG_DISPCNT = (MODE_0 | BG0_ON | BG1_ON);

	REG_BG0CNT = (BG_SIZE_0 | BG_16_COLOR | Bg[0].tileBase | Bg[0].mapBase);
	REG_BG1CNT = (BG_SIZE_0 | BG_16_COLOR | Bg[1].tileBase | Bg[1].mapBase);
}
//---------------------------------------------------------------------------
void BgSetTile(u32 bg, u16* pDat, u32 size)
{
	vu32 i;

	for(i=0; i<size; i++)
	{
		Bg[bg].tileBaseAdr[i] = pDat[i];
	}
}
//---------------------------------------------------------------------------
void BgSetPal(u32 pal, u16* pDat)
{
	vu32 i;

	for(i=0; i<16; i++)
	{
		BG_PALETTE[pal*16+i] |= pDat[i];
	}
}
//---------------------------------------------------------------------------
void BgSetMap(void)
{
	vu32 i;

	for(i=0; i<32*20; i++)
	{
		Bg[0].mapBaseAdr[i] = i;
		Bg[1].mapBaseAdr[i] = i | (1 << 12);	// バレット番号1を選択
	}
}
//---------------------------------------------------------------------------
int main(void)
{
	BgInit();

	BgSetTile(0, (u16*)&bg0kusaTiles, bg0kusaTilesLen/2);
	BgSetTile(1, (u16*)&bg1kumoTiles, bg1kumoTilesLen/2);

	BgSetPal(0, (u16*)&bg0kusaPal);
	BgSetPal(1, (u16*)&bg1kumoPal);

	BgSetMap();

	for(;;)
	{
		WaitForVsync();
	}
}
