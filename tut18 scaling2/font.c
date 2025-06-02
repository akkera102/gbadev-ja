#include "font.h"
#include "res.h"

//---------------------------------------------------------------------------
ST_FONT Font;


//---------------------------------------------------------------------------
void FontInit(void)
{
	_Memset(&Font, 0x00, sizeof(ST_FONT));

	Font.pDat  = (u8*)&k6x10Bitmap;
	Font.imgCx = 960;
	Font.cx    =   6;
	Font.cy    =  10;
}
//---------------------------------------------------------------------------
IWRAM_CODE void FontDrawChr(s32 sx, s32 sy, u16 col, u16 chr)
{
	vu16* pScreen = (u16*)VRAM + (sy * 240) + sx;
	u8*  pDat = Font.pDat + (chr - 0x20) * Font.cx;

	s32 x, y;

	for(y=0; y<Font.cy; y++)
	{
		for(x=0; x<Font.cx; x++)
		{
			if(pDat[y*Font.imgCx + x] == 0x00)
			{
				continue;
			}

			pScreen[y*240 + x] = col;
		}
	}
}
//---------------------------------------------------------------------------
IWRAM_CODE void FontDrawStr(s32 sx, s32 sy, u16 col, char* str)
{
	u16 chr;
	s32 i=0, x=0, y=0;

	for(;;)
	{
		chr = str[i++];

		if(chr == '\0') return;
		if(chr ==   CR) return;
		if(chr ==   LF) return;

		if(sx + x >= 240)
		{
			x  = 0;
			y += Font.cy;

			if(sy + y + Font.cy >= 160)
			{
				return;
			}
		}

		FontDrawChr(sx + x, sy + y, col, chr);
		x += Font.cx;
	}
}
//---------------------------------------------------------------------------
IWRAM_CODE void FontDrawPrintf(s32 sx, s32 sy, u16 col, char* format, ...)
{
	char s[100] ALIGN(4);

	char* ap;
	va_start(ap, format);
	_DoSprintf(s, format, ap);
	va_end(ap);

	FontDrawFillBox(sx, sy, _Strlen(s)*Font.cx, Font.cy, RGB5(0,0,0));
	FontDrawStr(sx, sy, col, s);
}
//---------------------------------------------------------------------------
IWRAM_CODE void FontDrawFillBox(s32 sx, s32 sy, s32 cx, s32 cy, u16 col)
{
	u16* Screen = (u16*)VRAM + (sy * 240) + sx;

	vs32 x, y;

	for(y=0; y<cy; y++)
	{
		for(x=0; x<cx; x++)
		{
			Screen[y*240 + x] = col;
		}
	}
}
