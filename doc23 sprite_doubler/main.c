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


		for(s32 i=0; i<20; i++)
		{
			BgAsciiDrawPrintf(20, i, "%3d", BulletGetIdxCnt(i));
			BgAsciiDrawPrintf(23, i, "%3d", BulletGetIdxCnt(20+i));
		}
		BgAsciiDrawPrintf(26, 0, "%3d", BulletGetIdxCnt(40));
		BgAsciiDrawPrintf(26, 1, "%3d", BulletGetIdxCnt(41));
		BgAsciiDrawPrintf(17, 0, "%3d", BulletGetMaxCnt());


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
