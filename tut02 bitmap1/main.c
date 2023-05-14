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

	s32 i;

	for(i=0; i<20; i++)
	{
		Mode3PutPixel(5+i, 5+i, RGB5(31, 31, 31));
	}

	for(i=0; i<32; i++)
	{
		Mode3PutPixel(20+i*2, 50, RGB5(i, 0, 0));
		Mode3PutPixel(20+i*2, 60, RGB5(0, i, 0));
		Mode3PutPixel(20+i*2, 70, RGB5(0, 0, i));
		Mode3PutPixel(20+i*2, 80, RGB5(i, i, i));
	}


	for(;;)
	{
		WaitForVsync();
	}
}
