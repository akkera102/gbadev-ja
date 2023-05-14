#include "lib/gba.h"
#include "res.h"

//---------------------------------------------------------------------------
void WaitForVsync(void)
{
	while (*(volatile u16*)0x4000006 >= 160) {};
	while (*(volatile u16*)0x4000006 <  160) {};
}
//---------------------------------------------------------------------------
int main(void)
{
	SetMode(MODE_3 | BG2_ENABLE);

	LZ77UnCompVram((void*)&imageBitmap, (void*)VRAM);

	for(;;)
	{
		WaitForVsync();
	}
}
