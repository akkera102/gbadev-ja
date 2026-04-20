#include "snd.arm.h"

// Timer0, DMA1

//---------------------------------------------------------------------------
ST_SND Snd;


//---------------------------------------------------------------------------
void SndInit(void)
{
	_Memset(&Snd, 0x00, sizeof(ST_SND));

//	REG_SOUNDCNT_X = SNDSTAT_ENABLE;
//	REG_SOUNDCNT_H = SNDA_L_ENABLE | SNDA_R_ENABLE | SNDB_L_ENABLE | SNDB_R_ENABLE | SNDA_RESET_FIFO | SNDB_RESET_FIFO | DSOUNDCTRL_ATIMER(0) | DSOUNDCTRL_BTIMER(1) | SNDA_VOL_100 | SNDB_VOL_100 | 0x2;
//	REG_SOUNDCNT_L = 0;

	REG_FIFO_A  = 0;
	REG_DMA1CNT = 0;
	REG_DMA1DAD = (u32)&REG_FIFO_A;

	REG_TM0CNT_H = 0;
	REG_TM0CNT_L = 0x10000 - (SND_CPU_CLOCK / SND_AUDIO_RATE);

	while(REG_VCOUNT == 159) {};
	while(REG_VCOUNT != 159) {};

	REG_TM0CNT_H = TIMER_START;

	Snd.act = SND_ACT_STOP;
}
//---------------------------------------------------------------------------
IWRAM_CODE void SndPlay(u8* pSnd, s32 size, s32 adjust, bool isLoop)
{
	Snd.pSnd   = pSnd;
	Snd.isLoop = isLoop;
	Snd.size   = (size * SND_FPS) / SND_AUDIO_RATE - adjust;
	Snd.act    = SND_ACT_START;
}
//---------------------------------------------------------------------------
IWRAM_CODE void SndStop(void)
{
	*(vu8*)(REG_BASE + 0x83) &= 0xF0;
	REG_DMA1CNT = 0;
	*(vu8*)(REG_BASE + 0x83) |= 0x0B;
	REG_FIFO_A = 0;

	Snd.act = SND_ACT_STOP;
}
//---------------------------------------------------------------------------
IWRAM_CODE u32 SndGetRem(void)
{
	return Snd.size - Snd.cnt;
}
//---------------------------------------------------------------------------
IWRAM_CODE bool SndIsPlay(void)
{
	return (Snd.act == SND_ACT_PLAY) ? true : false;
}
//---------------------------------------------------------------------------
IWRAM_CODE void SndIntrVblank(void)
{
	if(Snd.act == SND_ACT_PLAY)
	{
		Snd.cnt++;

		if(Snd.cnt < Snd.size)
		{
			return;
		}

		if(Snd.isLoop == true)
		{
			goto Start;
		}
		else
		{
			SndStop();
		}
	}
	else if(Snd.act == SND_ACT_START)
	{
Start:
		REG_DMA1CNT = 0;
		REG_DMA1SAD = (u32)Snd.pSnd;
		REG_DMA1CNT = DMA_SRC_INC | DMA_DST_FIXED | DMA_REPEAT | DMA32 | DMA_SPECIAL | DMA_ENABLE;

		Snd.cnt = 0;
		Snd.act = SND_ACT_PLAY;
	}
}
