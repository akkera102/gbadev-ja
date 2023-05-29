#include "libmm/maxmod.h"
#include "lib/gba.h"
#include "irq.arm.h"
#include "bg.h"
#include "key.h"
#include "res.h"


//---------------------------------------------------------------------------
// 効果音の登録（id, rate, handle, volume, panning)
mm_sound_effect ambulance = { {SFX_AMBULANCE}, 1024, 0, 255, 0 };
mm_sound_effect boom = { {SFX_BOOM}, 1024, 0, 255, 255 };

// sound effect handle (for cancelling it later)
mm_sfxhand amb = 0;

//---------------------------------------------------------------------------
int main(void)
{
	REG_WSCNT = 0x4317;

	BgInit();
	KeyInit();
	IrqInit();

	mmInitDefault((mm_addr)soundbank_bin, 8);
	mmStart(MOD_FLATOUTLIES, MM_PLAY_LOOP);

	BgDrawPrintf(0, 0, "MaxMod Audio demo");
	BgDrawPrintf(1, 2, "Hold  A for ambulance sound");
	BgDrawPrintf(1, 3, "Press B for boom sound");
	BgDrawPrintf(1, 4, "Press L for music stop");
	BgDrawPrintf(1, 5, "Press R for music start");

	BgDrawPrintf(1, 8, "CPU Usage");
	BgDrawPrintf(1, 9, " +2.6 percent BASE");
	BgDrawPrintf(1, 10, " +2   percent 1ch (max 8ch)");


	for(;;)
	{
		VBlankIntrWait();

		// start vcount 0
		while(*(vu16*)0x4000006 != 0) {};

		// パレット0を変更してcpu使用率の可視化をします
		// mmVBlank関数は本来、vblank割り込み中に処理を行います

		*(vu16*)0x5000000 = RGB5(31, 0, 0);
		mmVBlank();
		*(vu16*)0x5000000 = RGB5(0, 0, 31);
		mmFrame();
		*(vu16*)0x5000000 = RGB5( 0, 0, 0);


		KeyExec();
		u32 off = KeyGetOff();
		u32 trg = KeyGetTrg();

		if(trg & KEY_A) amb = mmEffectEx(&ambulance);
		if(off & KEY_A)       mmEffectCancel(amb);

		if(trg & KEY_B) mmEffectEx(&boom);
		if(trg & KEY_R) mmStart(MOD_FLATOUTLIES, MM_PLAY_LOOP);
		if(trg & KEY_L) mmStop();
	}
}
