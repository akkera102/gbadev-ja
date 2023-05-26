#include "snd.arm.h"


// BGM Timer0, DMA1
// SE  Timer1, DMA2

//---------------------------------------------------------------------------
ST_SND Snd[2];


//---------------------------------------------------------------------------
EWRAM_CODE void SndInit()
{
	_Memset(&Snd, 0x00, sizeof(ST_SND) * 2);

	REG_TM0CNT_L   = 0x10000 - SND_FRAQ;
	REG_TM1CNT_L   = 0x10000 - SND_FRAQ;

	REG_SOUNDCNT_X = SNDSTAT_ENABLE;
	REG_SOUNDCNT_L = 0;
	REG_SOUNDCNT_H = SNDA_RESET_FIFO | SNDB_RESET_FIFO | SNDA_VOL_100 | SNDB_VOL_100 | DSOUNDCTRL_ATIMER(0) | DSOUNDCTRL_BTIMER(1);
}
//---------------------------------------------------------------------------
IWRAM_CODE void SndPlay(u32 id, u8* data, u32 size, s32 adjust, bool isLoop)
{
	ST_SND* p = &Snd[id];

	p->act      = SND_ACT_START;
	p->cnt      = 0;

	p->data     = data;
	p->size     = size;
	p->frameCnt = (size * 60) / SND_AUDIO_RATE + adjust;
	p->isLoop   = isLoop;
}
//---------------------------------------------------------------------------
IWRAM_CODE void SndPlayBgm(u8* data, u32 size, s32 adjust, bool isLoop)
{
	SndPlay(SND_ID_BGM, data, size, adjust, isLoop);
}
//---------------------------------------------------------------------------
IWRAM_CODE void SndPlaySe(u8* data, u32 size, s32 adjust, bool isLoop)
{
	SndPlay(SND_ID_SE, data, size, adjust, isLoop);
}
//---------------------------------------------------------------------------
IWRAM_CODE void SndStopBgm(void)
{
	Snd[SND_ID_BGM].act = SND_ACT_STOP;
}
//---------------------------------------------------------------------------
IWRAM_CODE void SndStopSe(void)
{
	Snd[SND_ID_SE].act = SND_ACT_STOP;
}
//---------------------------------------------------------------------------
IWRAM_CODE bool SndIsPlayBgm(void)
{
	return (Snd[SND_ID_BGM].act == SND_ACT_PLAY) ? TRUE : FALSE;
}
//---------------------------------------------------------------------------
IWRAM_CODE bool SndIsPlaySe(void)
{
	return (Snd[SND_ID_SE].act == SND_ACT_PLAY) ? TRUE : FALSE;
}
//---------------------------------------------------------------------------
IWRAM_CODE void SndIntrBgm(void)
{
	ST_SND* p = &Snd[0];

	switch(p->act)
	{
	case SND_ACT_DONOTHING:
		return;

	case SND_ACT_START:
start:
		SndIntrBgmStart();
		p->act = SND_ACT_PLAY;
		return;

	case SND_ACT_STOP:
stop:
		SndIntrBgmStop();
		p->act = SND_ACT_DONOTHING;
		return;

	case SND_ACT_PLAY:
		p->cnt--;

		if(p->cnt <= 0)
		{
			if(p->isLoop == TRUE)
			{
				goto start;
			}
			else
			{
				goto stop;
			}
		}
		return;

	default:
		SystemError("[Err] SndIntrBgm");
		break;
	}
}
//---------------------------------------------------------------------------
IWRAM_CODE void SndIntrSe(void)
{
	ST_SND* p = &Snd[1];

	switch(p->act)
	{
	case SND_ACT_DONOTHING:
		return;

	case SND_ACT_START:
start:
		SndIntrSeStart();
		p->act = SND_ACT_PLAY;
		return;

	case SND_ACT_STOP:
stop:
		SndIntrSeStop();
		p->act = SND_ACT_DONOTHING;
		return;

	case SND_ACT_PLAY:
		p->cnt--;

		if(p->cnt <= 0)
		{
			if(p->isLoop == TRUE)
			{
				goto start;
			}
			else
			{
				goto stop;
			}
		}
		return;

	default:
		SystemError("[Err] SndIntrSe");
		break;
	}
}
//---------------------------------------------------------------------------
IWRAM_CODE void SndIntrBgmStart(void)
{
	REG_TM0CNT_H = 0;
	REG_DMA1CNT  = 0;

	DMA1COPY(Snd[0].data, &REG_FIFO_A, DMA_SPECIAL | DMA32 | DMA_REPEAT | DMA_SRC_INC | DMA_DST_FIXED);
	REG_TM0CNT_H    = TIMER_START;
	REG_SOUNDCNT_H |= (SNDA_R_ENABLE | SNDA_L_ENABLE | SNDA_RESET_FIFO);

	Snd[0].cnt = Snd[0].frameCnt;
}
//---------------------------------------------------------------------------
IWRAM_CODE void SndIntrBgmStop(void)
{
	REG_SOUNDCNT_H &= ~(SNDA_R_ENABLE | SNDA_L_ENABLE | SNDA_RESET_FIFO);
	REG_TM1CNT_H    = 0;
	REG_DMA1CNT     = 0;

	Snd[0].cnt = 0;
}
//---------------------------------------------------------------------------
IWRAM_CODE void SndIntrSeStart(void)
{
	REG_TM1CNT_H = 0;
	REG_DMA2CNT  = 0;

	DMA2COPY(Snd[1].data, &REG_FIFO_B, DMA_SPECIAL | DMA32 | DMA_REPEAT | DMA_SRC_INC | DMA_DST_FIXED);
	REG_TM1CNT_H = TIMER_START;
	REG_SOUNDCNT_H |= (SNDB_R_ENABLE | SNDB_L_ENABLE | SNDB_RESET_FIFO);

	Snd[1].cnt = Snd[1].frameCnt;
}
//---------------------------------------------------------------------------
IWRAM_CODE void SndIntrSeStop(void)
{
	REG_SOUNDCNT_H &= ~(SNDB_R_ENABLE | SNDB_L_ENABLE | SNDB_RESET_FIFO);
	REG_TM1CNT_H    = 0;
	REG_DMA2CNT     = 0;

	Snd[1].cnt = 0;	
}
