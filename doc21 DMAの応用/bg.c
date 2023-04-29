#include "res.h"
#include "bg.h"


//bg0 ASCII
//bg1 mask

//---------------------------------------------------------------------------
ST_BG Bg[BG_MAX_CNT];

//---------------------------------------------------------------------------
EWRAM_CODE void BgInit()
{
	BgInitLcd();

	Bg0Init();
	Bg1Init();
	Bg2Init();
//	Bg3Init();

	REG_DISPCNT = (MODE_0 | BG0_ON | BG1_ON | BG2_ON | WIN0_ON);
	REG_BG0CNT  = (BG_SIZE_0 | BG_16_COLOR | Bg[0].tileBase | Bg[0].mapBase | 0);
	REG_BG1CNT  = (BG_SIZE_0 | BG_16_COLOR | Bg[1].tileBase | Bg[1].mapBase | 0);
	REG_BG2CNT  = (BG_SIZE_0 | BG_16_COLOR | Bg[2].tileBase | Bg[2].mapBase | 0 | BG_SIZE_1);
//	REG_BG3CNT  = (BG_SIZE_0 | BG_16_COLOR | Bg[3].tileBase | Bg[3].mapBase | 3 | BG_WRAP);

	REG_BG2HOFS = 120;
	REG_BG2VOFS = 64;

	REG_WIN0H = 0;
	REG_WIN0V = SCREEN_HEIGHT;

#define WIN_BUILD(low, high)	( ((high)<<8) | (low) )
#define WIN_BG0			0x0001	//!< Windowed bg 0
#define WIN_BG1			0x0002	//!< Windowed bg 1
#define WIN_BG2			0x0004	//!< Windowed bg 2

	REG_WININ  = WIN_BUILD(WIN_BG0 | WIN_BG2, 0);
	REG_WINOUT = WIN_BUILD(WIN_BG0 | WIN_BG1, 0);
}
//---------------------------------------------------------------------------
EWRAM_CODE void BgInitLcd()
{
	const u32 mapBase[]  = { 23, 26, 29,  0 };
	const u32 tileBase[] = {  0,  1,  2,  0 };
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
	vs32 i;

	for(i=0; i<font_asciiTilesLen/2; i++)
	{
		Bg[0].tileBaseAdr[i] = font_asciiTiles[i];
	}

	for(i=0; i<font_asciiPalLen/2; i++)
	{
		BG_PALETTE[i]  = font_asciiPal[i];
	}
}
//---------------------------------------------------------------------------
EWRAM_CODE void Bg1Init()
{
	const u16 tiles[] = {
		0xF2F3, 0xF2F3, 0x3F2F, 0x3F2F, 0xF3F2, 0xF3F2, 0x2F3F, 0x2F3F,
		0xF2F3, 0xF2F3, 0x3F2F, 0x3F2F, 0xF3F2, 0xF3F2, 0x2F3F, 0x2F3F,
	};
	vu32 i;

	for(i=0; i<sizeof(tiles)/2; i++)
	{
		Bg[1].tileBaseAdr[i] = tiles[i];
	}

	BG_PALETTE[16*1+ 2] = RGB5(12,12,12);
	BG_PALETTE[16*1+ 3] = RGB5( 8, 8, 8);
	BG_PALETTE[16*1+15] = RGB5( 0, 0, 0);

	for(i=0; i<32*20; i++)
	{
		Bg[1].mapBaseAdr[i] = 0x1000;
	}
}
//---------------------------------------------------------------------------
EWRAM_CODE void Bg2Init()
{
	vs32 i;

	for(i=0; i<brinTilesLen/2; i++)
	{
		Bg[2].tileBaseAdr[i] = brinTiles[i];
	}

	for(i=0; i<brinPalLen/2; i++)
	{
		BG_PALETTE[16*2+i]  = brinPal[i];
	}

	for(i=0; i<brinMapLen; i++)
	{
		Bg[2].mapBaseAdr[i] = brinMap[i] | (2 << 12);
	}
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
/* Create an array of horizontal offsets for a circular window.
*	The offsets are to be copied to REG_WINxH each HBlank, either 
*	by HDMA or HBlank isr. Offsets provided by modified 
*	Bresenham's circle routine (of course); the clipping code is not
*	optional.
*
*	\param winh	Pointer to array to receive the offsets.
*	\param x0	X-coord of circle center.
*	\param y0	Y-coord of circle center.
*	\param rr	Circle radius.
*/
EWRAM_CODE void BgCreateWindowCircleDma(s32 x0, s32 y0, s32 rr)
{
	u16 g_winh[SCREEN_HEIGHT+1];

	int x=0, y= rr, d= 1-rr;
	u32 tmp;

	// clear the whole array first.
	memset16(winh, 0, SCREEN_HEIGHT+1);

	while(y >= x)
	{
		// Side octs
		tmp  = clamp(x0+y, 0, SCREEN_WIDTH+1);
		tmp += clamp(x0-y, 0, SCREEN_WIDTH+1)<<8;
		
		if(IN_RANGE(y0-x, 0, SCREEN_HEIGHT))		// o4, o7
			winh[y0-x]= tmp;
		if(IN_RANGE(y0+x, 0, SCREEN_HEIGHT))		// o0, o3
			winh[y0+x]= tmp;

		// Change in y: top/bottom octs
		if(d >= 0)		
		{
			tmp  = clamp(x0+x, 0, SCREEN_WIDTH+1);
			tmp += clamp(x0-x, 0, SCREEN_WIDTH+1)<<8;
			
			if(IN_RANGE(y0-y, 0, SCREEN_HEIGHT))	// o5, o6
				winh[y0-y]= tmp;
			if(IN_RANGE(y0+y, 0, SCREEN_HEIGHT))	// o1, o2
				winh[y0+y]= tmp;

			d -= 2*(--y);
		}
		d += 2*(x++)+3;
	}
	winh[SCREEN_HEIGHT]= winh[0];

	// Init win-circle HDMA
	DMA_TRANSFER(&REG_WIN0H, &g_winh[1], 1, 3, DMA_HDMA);

}
