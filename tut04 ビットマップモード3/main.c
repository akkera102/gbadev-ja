#include "lib/gba.h"
#include "res.h"

//---------------------------------------------------------------------------
void WaitForVsync(void)
{
	while(*(vu16*)0x4000006 >= 160) {};
	while(*(vu16*)0x4000006 <  160) {};
}
//---------------------------------------------------------------------------
void Mode4SetFrame(u8* img, u32 f)
{
	u8* fr;

	if(f == 1)
	{
		fr = (u8*)0x6000000;
	}
	else
	{
		fr = (u8*)0x600A000;
	}

	u32 x, y;

	for(y=0; y<160; y++)
	{
		for(x=0; x<240; x++)
		{
			fr[y*240+x] = img[y*240+x];
		}
	}
}
//---------------------------------------------------------------------------
void Mode4SetPalette(u16* pDat)
{
	u16* pPalette = (u16*)0x05000000;
	u32 i;

	for(i=0; i<256; i++)
	{
		pPalette[i] = pDat[i];
	}
}
//---------------------------------------------------------------------------
int main(void)
{
	// モード設定
	// 4bit目（BACKBUFFER）を1にすることで、フレーム2が有効になります
	SetMode(MODE_4 | BG2_ENABLE | BACKBUFFER);

	// 画像と色データの読み込み
	Mode4SetFrame((u8*)&frame1Bitmap, 1);
	Mode4SetFrame((u8*)&frame2Bitmap, 2);

	Mode4SetPalette((u16*)&frame1Pal);

	for(;;)
	{
	    WaitForVsync();
	}
}
