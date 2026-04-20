#include "lib/gba.h"
#include "ad.arm.h"
#include "snd.arm.h"
#include "irq.arm.h"
#include "bg.h"
#include "key.h"

//---------------------------------------------------------------------------
int main(void)
{
	REG_WSCNT = 0x4317;

	GbfsInit();
	BgInit();
	KeyInit();
	IrqInit();

	AdInit();
	SndInit();

	s32   sel  = 0;
	s32   max  = GbfsGetArcCnt() - 1;
	u8*   pS   = GbfsGetSafePointer2(sel);
	char* pF   = GbfsGetFileName();
	u32   size = GbfsGetFileSize();

	BgDrawPrintf(1, 1, "SOUND TEST");
	BgDrawPrintf(1, 2, "8ad/raw(13379/16384Hz)");

	for(;;)
	{
		VBlankIntrWait();

		BgDrawPrintf( 1, 4, "Select: (%2d/%2d)", sel, max);
		BgDrawPrintf( 9, 5, "            ");
		BgDrawPrintf( 1, 5, "Fname : %s", pF);
		BgDrawPrintf( 1, 6, "Fsize : %08d", size);

		bool isAd  = AdIsPlay();
		bool isSnd = SndIsPlay();

		BgDrawPrintf( 1, 7, "                ");

		if(isAd == true)
		{
			BgDrawPrintf( 1, 7, "Remnd : %08d", AdGetRem());
		}

		if(isSnd == true)
		{
			BgDrawPrintf( 1, 7, "Remnd : %08d", SndGetRem());
		}

		KeyExec();
		u16 trg = KeyGetTrg();

		if((trg & KEY_RIGHT) && sel < max)
		{
			sel++;

			pS = GbfsGetSafePointer2(sel);
			pF = GbfsGetFileName();
			size = GbfsGetFileSize();
		}

		if((trg & KEY_LEFT) && sel > 0)
		{
			sel--;

			pS = GbfsGetSafePointer2(sel);
			pF = GbfsGetFileName();
			size = GbfsGetFileSize();
		}

		if(trg & KEY_A)
		{
			if(isAd == true)
			{
				AdStop();
			}

			if(isSnd == true)
			{
				SndStop();
			}


			s32 len  = _Strlen(pF);

			// 8ad or raw
			if(pF[len-3] == '8')
			{
				IrqInitAd();
				AdPlay(pS, size, true);
			}
			else
			{
				IrqInitSnd();
				SndPlay(pS, size, 20, true);
			}
		}

		if(trg & KEY_B)
		{
			if(isAd == true)
			{
				AdStop();
			}

			if(isSnd == true)
			{
				SndStop();
			}
		}
	}
}
