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
	Bg2Init();
//	Bg3Init();

	REG_DISPCNT = (MODE_0 | BG0_ON | BG1_ON | BG2_ON | WIN0_ON);
	REG_BG0CNT  = (BG_SIZE_0 | BG_16_COLOR | Bg[0].tileBase | Bg[0].mapBase | 0);
	REG_BG1CNT  = (BG_SIZE_0 | BG_16_COLOR | Bg[1].tileBase | Bg[1].mapBase | 0);
	REG_BG2CNT  = (BG_SIZE_0 | BG_16_COLOR | Bg[2].tileBase | Bg[2].mapBase | 0 | BG_SIZE_1);
//	REG_BG3CNT  = (BG_SIZE_0 | BG_16_COLOR | Bg[3].tileBase | Bg[3].mapBase | 3 | BG_WRAP);

	REG_BG2HOFS = 120;
	REG_BG2VOFS = 64;

	REG_WIN0H  = 0;
	REG_WIN0V  = SCREEN_HEIGHT;
	REG_WININ  = WIN_0_BG0 | WIN_0_BG2;
	REG_WINOUT = WIN_0_BG0 | WIN_0_BG1;
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
*	\param x0	X-coord of circle center.
*	\param y0	Y-coord of circle center.
*	\param rr	Circle radius.
*/

u16 BgWinh[SCREEN_HEIGHT+1] ALIGN(4);

IWRAM_CODE void BgCreateWindowCircleDma(s32 x0, s32 y0, s32 rr)
{
	// Zero clear
	for(vs32 i=0; i<SCREEN_HEIGHT+1; i++)
	{
		BgWinh[i] = 0;
	}


	s32 x=0, y=rr, d=1-rr;
	u32 tmp;

	while(y >= x)
	{
		// Side octs
		tmp  = BgClamp(x0 + y, 0, SCREEN_WIDTH+1);
		tmp += BgClamp(x0 - y, 0, SCREEN_WIDTH+1) << 8;

		// o4, o7
		if(BgInRange(y0-x, 0, SCREEN_HEIGHT))
		{
			BgWinh[y0 - x]= tmp;
		}

		// o0, o3
		if(BgInRange(y0+x, 0, SCREEN_HEIGHT))
		{
			BgWinh[y0 + x]= tmp;
		}

		// Change in y: top/bottom octs
		if(d >= 0)
		{
			tmp  = BgClamp(x0 + x, 0, SCREEN_WIDTH+1);
			tmp += BgClamp(x0 - x, 0, SCREEN_WIDTH+1) << 8;

			// o5, o6
			if(BgInRange(y0-y, 0, SCREEN_HEIGHT))
			{
				BgWinh[y0 - y]= tmp;
			}

			// o1, o2
			if(BgInRange(y0+y, 0, SCREEN_HEIGHT))
			{
				BgWinh[y0 + y]= tmp;
			}

			d -= 2 * (--y);
		}

		d += 2 * (x++) + 3;
	}

/*
	for(vs32 i=0; i<SCREEN_HEIGHT+1; i++)
	{
		TRACE("%d: %4x\n", i, BgWinh[i]);
	}
	for(;;){}
*/

	REG_DMA3CNT = 0;
	REG_DMA3SAD = (u32)&BgWinh[1];
	REG_DMA3DAD = (u32)&REG_WIN0H;
	REG_DMA3CNT = 1 | (DMA_DST_RELOAD | DMA_REPEAT | DMA_HBLANK | DMA_ENABLE);
}
//---------------------------------------------------------------------------
IWRAM_CODE s32 BgClamp(s32 val, s32 min, s32 max)
{
	if(val < min)
	{
		return min;
    }

	if(val > max)
	{
		return max;
	}

	return val;
}
//---------------------------------------------------------------------------
IWRAM_CODE bool BgInRange(s32 x, s32 min, s32 max)
{
	return ((x)>=(min)) && ((x)<(max)) ? TRUE : FALSE;
}
