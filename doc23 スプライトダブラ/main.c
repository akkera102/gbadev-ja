#include "main.h"
#include "irq.arm.h"
#include "bg.h"
#include "key.h"
#include "spr.arm.h"
#include "bullet.arm.h"
#include "rnd.arm.h"

//---------------------------------------------------------------------------
ST_MAIN Main;


//---------------------------------------------------------------------------
int main(void)
{
	REG_WSCNT = 0x4317;

	_Memset(&Main,  0x00, sizeof(ST_MAIN));
	ST_MAIN* p = &Main;

	BgInit();
	KeyInit();
	RndInit();
	SprInit();
	BulletInit();
	IrqInit();

	for(;;)
	{
		VBlankIntrWait();

		p->fpsCount++;
		p->gameTime++;
		p->gameFrame++;

		if(p->gameFrame < p->frameCount)
		{
			p->delay     = p->frameCount - p->gameFrame;
			p->gameFrame = p->frameCount;
		}
		else
		{
			p->delay = 0;
		}

		for(s32 i=0; i<BULLET_MAX_IDX_CNT-1; i++)
		{
			BgAsciiDrawPrintf(26, i, "%3d", BulletGetIdxCnt(i+1));
		}
		BgAsciiDrawPrintf(23, 0, "%3d", BulletGetMaxCnt());
		BgAsciiDrawPrintf(0, 0, "FREAME:%3d", p->frameCount);
		BgAsciiDrawPrintf(0, 1, "DELAY :%3d", p->delay);
		BgAsciiDrawPrintf(0, 2, "FPS   :%3d", p->fps);

		BulletExec();
		SprExec();

		KeyExec();
		u16 cnt = KeyGetCnt();

		if(cnt & KEY_A)
		{
			BulletReg(240/2, 160/2);
		}

		if(cnt & KEY_B)
		{
			for(s32 i=0; i<5; i++)
			{
				BulletReg(240/2, 160/2);
			}
		}
	}
}
