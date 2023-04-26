#include "lib/gba.h"
#include "res.h"

//---------------------------------------------------------------------------
void WaitForVsync(void)
{
	while(*(vu16*)0x4000006 >= 160) {};
	while(*(vu16*)0x4000006 <  160) {};
}
//---------------------------------------------------------------------------
int main(void)
{
	// ���[�h�ݒ�
	SetMode(MODE_3 | BG2_ENABLE);

	// �摜�̓ǂݍ���
	REG_DMA3SAD = (u32)&imageBitmap;
	REG_DMA3DAD = (u32)VRAM;
	REG_DMA3CNT = (u32)(240*160) | (DMA_SRC_INC | DMA_DST_INC | DMA16 | DMA_ENABLE);

	for(;;)
	{
	    WaitForVsync();
	}
}
