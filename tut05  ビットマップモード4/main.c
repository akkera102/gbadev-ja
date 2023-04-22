#include "lib/gba.h"
#include "res.h"

//---------------------------------------------------------------------------
void WaitForVsync(void)
{
	while(*(vu16*)0x4000006 >= 160) {};
	while(*(vu16*)0x4000006 <  160) {};
}
//---------------------------------------------------------------------------
void Mode5SetFrame(u8* img, u32 f)
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
int main(void)
{
	// モード設定。フレーム2を指定
	SetMode(MODE_5 | BG2_ENABLE | BACKBUFFER);

	// 画像の読み込み
	Mode5SetFrame((u8*)&frame1Bitmap, 1);
	Mode5SetFrame((u8*)&frame2Bitmap, 2);


	for(;;)
	{
	    WaitForVsync();
	}
}
