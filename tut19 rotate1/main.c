#include "lib/gba.h"
#include "irq.arm.h"
#include "math.h"
#include "res.h"


//---------------------------------------------------------------------------
//BG2ÇÃècÅEâ°ÇÃägëÂó¶Ç%Ç≈éwíË
void RotateBG2(s32 angle)
{
	REG_BG2PA =  MathCos(angle);
	REG_BG2PB =  MathSin(angle);
	REG_BG2PC = -MathSin(angle);
	REG_BG2PD =  MathCos(angle);

	// bgx = x1 - Éø *  cos(É∆-É¿) * hzoom
	// bgy = y1 - Éø * -sin(É∆-É¿) * vzoom
	s32 bg2x = 120 * 256 - 144 * ( MathCos(angle - 33));
	s32 bg2y =  80 * 256 - 144 * (-MathSin(angle - 33));

	if(bg2x < 0)
	{
	 	REG_BG2X = 0xFFFFFFF - MathAbs(bg2x);
	}
	else
	{
		REG_BG2X = MathAbs(bg2x);
	}
	
	if(bg2y < 0)
	{
		REG_BG2Y = 0xFFFFFFF - MathAbs(bg2y);
	}
	else
	{
		REG_BG2Y = MathAbs(bg2y);
	}
}
//---------------------------------------------------------------------------
int main(void)
{
	REG_WSCNT = 0x4317;
	REG_DISPCNT = (MODE_3 | BG2_ON);

	IrqInit();

	REG_DMA3SAD = (u32)&imageBitmap;
	REG_DMA3DAD = (u32)VRAM;
	REG_DMA3CNT = (u32)(240*160) | (DMA_SRC_INC | DMA_DST_INC | DMA16 | DMA_ENABLE);


	s32 angle = 0;

	for(;;)
	{
		VBlankIntrWait();

		RotateBG2(angle);

		angle++;

		if(angle > 360)
		{
			angle = 0;
		}
	}
}
