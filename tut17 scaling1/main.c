#include "lib/gba.h"
#include "res.h"
#include "irq.arm.h"
#include "key.h"
#include "font.h"

//---------------------------------------------------------------------------
void ScaleBG2(u32 xsc, u32 ysc)
{
	REG_BG2PA = Div(256 * 100, xsc);
	REG_BG2PB = 0;
	REG_BG2PC = 0;
	REG_BG2PD = Div(256 * 100, ysc);
}
//---------------------------------------------------------------------------
int main(void)
{
	REG_WSCNT = 0x4317;

	IrqInit();
	KeyInit();
	FontInit();

	SetMode(MODE_3 | BG2_ENABLE);

	s32 x = 150;
	s32 y = 150;
	u16 cnt;

	REG_DMA3SAD = (u32)&imageBitmap;
	REG_DMA3DAD = (u32)VRAM;
	REG_DMA3CNT = (u32)(240*160) | (DMA_SRC_INC | DMA_DST_INC | DMA16 | DMA_ENABLE);

	for(;;)
	{
		VBlankIntrWait();

		FontDrawPrintf(16, 16, RGB5(31,31,31), "[%3d][%3d]", x, y);

		ScaleBG2(x, y);

		KeyExec();
		cnt = KeyGetCnt();

		if(cnt & KEY_UP   ) y--;
		if(cnt & KEY_DOWN ) y++;
		if(cnt & KEY_LEFT ) x--;
		if(cnt & KEY_RIGHT) x++;

		if(x <   1) x =   1;
		if(x > 200) x = 200;
		if(y <   1) y =   1;
		if(y > 200) y = 200;
	}
}
