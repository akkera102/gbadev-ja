#include "lib/gba.h"
#include "res.h"
#include "irq.arm.h"
#include "key.h"

//---------------------------------------------------------------------------
int main(void)
{
	REG_WSCNT = 0x4317;

	IrqInit();
	KeyInit();

	SetMode(MODE_3 | BG2_ENABLE);
	REG_BG2CNT = BG_MOSAIC;

	REG_DMA3SAD = (u32)&imageBitmap;
	REG_DMA3DAD = (u32)VRAM;
	REG_DMA3CNT = (u32)(240*160) | (DMA_SRC_INC | DMA_DST_INC | DMA16 | DMA_ENABLE);

	s32 cx = 5;
	s32 cy = 5;
	u32 cnt;

	for(;;)
	{
		VBlankIntrWait();

		REG_MOSAIC = MOSAIC_BG_H(cx) | MOSAIC_BG_V(cy);

		KeyExec();
		cnt = KeyGetCnt();

		if(cnt & KEY_UP   ) cy--;
		if(cnt & KEY_DOWN ) cy++;
		if(cnt & KEY_LEFT ) cx--;
		if(cnt & KEY_RIGHT) cx++;

		if(cx <  0) cx =  0;
		if(cx > 15) cx = 15;
		if(cy <  0) cy =  0;
		if(cy > 15) cy = 15;
	}
}
