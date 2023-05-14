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
	const u32 mapBase[]  = {  8,  9, 10, 11 };
	const u32 tileBase[] = {  0,  0,  0,  0 };
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

	REG_DISPCNT = (MODE_0 | BG0_ON);
	REG_BG0CNT  = (BG_SIZE_0 | BG_256_COLOR | Bg[0].tileBase | Bg[0].mapBase | 0);
}
//---------------------------------------------------------------------------
void Bg0SetTile(u16* pDat, u32 size)
{
	vu32 i;

	for(i=0; i<size; i++)
	{
		Bg[0].tileBaseAdr[i] = pDat[i];
	}
}
//---------------------------------------------------------------------------
void Bg0SetPal(u16* pDat)
{
	vu32 i;

	for(i=0; i<256; i++)
	{
		BG_PALETTE[i]  = pDat[i];
	}
}
//---------------------------------------------------------------------------
void Bg0SetMap(u16* pDat, u32 size)
{
	vu32 i;

	for(i=0; i<size; i++)
	{
		Bg[0].mapBaseAdr[i] = pDat[i];
	}
}
//---------------------------------------------------------------------------
int main(void)
{
	BgInit();

	Bg0SetTile((u16*)&bg0Tiles, bg0TilesLen/2);
	Bg0SetPal ((u16*)&bg0Pal);
	Bg0SetMap ((u16*)&ResBg0Map, BG0_MAP_SIZE/2);

	u32 x = 0;
	u32 y = 0;

	for(;;)
	{
		WaitForVsync();

		if( !(REG_KEYINPUT & KEY_UP)   ) y--;
		if( !(REG_KEYINPUT & KEY_DOWN) ) y++;
		if( !(REG_KEYINPUT & KEY_LEFT) ) x--;
		if( !(REG_KEYINPUT & KEY_RIGHT)) x++;

		x = x & 0xff;
		y = y & 0xff;

		REG_BG0HOFS = x;
		REG_BG0VOFS = y;
	}
}
