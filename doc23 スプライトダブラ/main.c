#include "lib/gba.h"
#include "irq.arm.h"
#include "bg.h"
#include "key.h"
#include "spr.arm.h"
#include "bullet.arm.h"
#include "rnd.arm.h"

//---------------------------------------------------------------------------
int main(void)
{
	REG_WSCNT = 0x4317;

	BgInit();
	KeyInit();
	RndInit();
	SprInit();
	BulletInit();
	IrqInit();

	for(;;)
	{
		VBlankIntrWait();

		for(s32 i=0; i<BULLET_MAX_IDX_CNT-1; i++)
		{
			BgAsciiDrawPrintf(26, i, "%3d", BulletGetIdxCnt(i+1));
		}
		BgAsciiDrawPrintf(23, 0, "%3d", BulletGetMaxCnt());

		BulletExec();

		SprInitItem();
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
