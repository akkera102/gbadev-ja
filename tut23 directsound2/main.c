#include <maxmod.h>
#include "lib/gba.h"
#include "irq.arm.h"
#include "bg.h"
#include "key.h"
#include "res.h"

//---------------------------------------------------------------------------
// maxmod���C�u�������̔���J�֐�
u32 mmMixerChannelActive(mm_word channel);

//---------------------------------------------------------------------------
// ���ʉ��̓o�^�iid, rate, handle, volume, panning)
mm_sound_effect ambulance = { {SFX_AMBULANCE}, (int)(1.0f * (1<<10)), 0, 255, 0 };
mm_sound_effect boom = { {SFX_BOOM}, (int)(1.0f * (1<<10)), 0, 255, 255 };

// sound effect handle (for cancelling it later)
mm_sfxhand amb = 0;

//---------------------------------------------------------------------------
IWRAM_CODE int main(void)
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

		// vcount 0���C���̈ʒu���珈���������܂�
		while(*(vu16*)0x4000006 !=  0) {};

		// �p���b�g��ύX����cpu�g�p���̉��������܂�
		// mmVBlank�֐��͖{���Avblank���荞�ݒ��ɏ������s���܂�

		*(vu16*)0x5000000 = RGB5(31, 0, 0);
		mmVBlank();
		*(vu16*)0x5000000 = RGB5(0, 0, 31);
		mmFrame();
		*(vu16*)0x5000000 = RGB5( 0, 0, 0);

		KeyExec();
		u32 off = KeyGetOff();
		u32 trg = KeyGetTrg();

		if(trg & KEY_A)
		{
			amb = mmEffectEx(&ambulance);
		}

		if(trg & KEY_B)
		{
			mmEffectEx(&boom);
		}

		if(trg & KEY_L)
		{
			mmStop();
		}

		if(trg & KEY_R)
		{
			mmStart(MOD_FLATOUTLIES, MM_PLAY_LOOP);
		}


		if(off & KEY_A)
		{
			mmEffectCancel(amb);
		}


		vu32 i, ch = 0;
		for(i=0; i<8; i++)
		{
			if(mmMixerChannelActive(i) != 0)
			{
				ch++;
			}
		}
		BgDrawPrintf(1, 12, "Channel Active:%d", ch);
	}
}
