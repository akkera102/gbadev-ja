#include "lib/gba.h"

//---------------------------------------------------------------------------
void WaitForVsync(void)
{
	while(*(vu16*)0x4000006 >= 160) {};
	while(*(vu16*)0x4000006 <  160) {};
}
//---------------------------------------------------------------------------
void Mode3PutPixel(u32 x, u32 y, u16 color)
{
	u16* ScreenBuffer     = (u16*)0x6000000;
	ScreenBuffer[y*240+x] = color;
}
//---------------------------------------------------------------------------
int main(void)
{
	SetMode(MODE_3 | BG2_ENABLE);

	s32 x=0, y=0;

	for(;;)
	{
		WaitForVsync();

		Mode3PutPixel(x, y, RGB5(0, 0, 0));

		x++;
		y++;

		if(y >= 160)
		{
			x = 0;
			y = 0;
		}

		Mode3PutPixel(x, y, RGB5(31, 31, 31));
	}
}
