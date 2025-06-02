#include "lib/gba.h"

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

	GbfsInit();

	u16* pImg1 = GbfsGetSafePointer("image1.img");
	u16* pImg2 = GbfsGetSafePointer("image2.img");

	LZ77UnCompVram(pImg1, (void*)VRAM);

 	u32 c = 0;
 	bool is = false;
 
 	for(;;)
 	{
 		WaitForVsync();
 
 		// –ñ3•bŒã‚ÉpImg2‚ð•\Ž¦
 		if(c++ == 60*3 && is == false)
 		{
 				LZ77UnCompVram(pImg2, (void*)VRAM);
 				is = true;
 		}
 	}
 }
