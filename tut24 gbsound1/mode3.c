#include "mode3.h"
#include "res.h"


//---------------------------------------------------------------------------
ST_MODE3 Mode3;

//---------------------------------------------------------------------------
void Mode3Init(void)
{
	SetMode(MODE_3 | BG2_ENABLE);

	Mode3.pDat  = (u8*) &k6x10Bitmap;
	Mode3.imgCx = 960;
	Mode3.cx    = 6;
	Mode3.cy    = 10;
}
//---------------------------------------------------------------------------
IWRAM_CODE void Mode3DrawChr(s32 sx, s32 sy, u16 chr)
{
	// 書き込む起点位置を求めます
	u16* pScreen = (u16*)VRAM + ((sy * Mode3.cy) * 240) + (sx * Mode3.cx);

	// 書き込むフォントデータの位置を求めます
	u8*  pDat = Mode3.pDat + (chr - 0x20) * Mode3.cx;

	s32 x, y;
	for(y=0; y<Mode3.cy; y++)
	{
		for(x=0; x<Mode3.cx; x++)
		{
			if(pDat[y*Mode3.imgCx + x] == 0x00)
			{
				pScreen[y*240 + x] = RGB5(0, 0, 0);
			}
			else
			{
				pScreen[y*240 + x] = RGB5(31, 31, 31);
			}
		}
	}
}
//---------------------------------------------------------------------------
IWRAM_CODE void Mode3DrawStr(s32 sx, s32 sy, char* str)
{
	u16 chr;
	s32 i=0, x=0, y=0;

	for(;;)
	{
		chr = str[i++];

		if(chr == '\0') return;
		if(chr ==   CR) return;
		if(chr ==   LF) return;

		// 改行処理
		if(sx + x >= 240)
		{
			x = 0;
			y++;

			if(sy + y + Mode3.cy >= 160)
			{
				return;
			}
		}

		Mode3DrawChr(sx + x, sy + y, chr);
		x++;
	}
}
//---------------------------------------------------------------------------
IWRAM_CODE void Mode3DrawPrintf(s32 sx, s32 sy, char* format, ...)
{
	char s[100] ALIGN(4);

	char* ap;
	va_start(ap, format);
	_DoSprintf(s, format, ap);
	va_end(ap);

	Mode3DrawStr(sx, sy, s);
}
