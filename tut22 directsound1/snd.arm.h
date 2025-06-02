#ifndef __SND_H__
#define __SND_H__
#ifdef __cplusplus
extern "C" {
#endif

#include "lib/gba.h"

//---------------------------------------------------------------------------
#define SND_CPU_CLOCK			(16 * 1024 * 1024)
#define SND_AUDIO_RATE			16384
#define SND_FRAQ				(SND_CPU_CLOCK / SND_AUDIO_RATE)


enum {
	SND_ID_BGM = 0,
	SND_ID_SE,
};

enum {
	SND_ACT_DONOTHING = 0,
	SND_ACT_START,
	SND_ACT_STOP,
	SND_ACT_PLAY,
};


//---------------------------------------------------------------------------
typedef struct {
	u32  act;
	s32  cnt;

	u8*  data;
	u32  size;
	s32  frameCnt;
	bool isLoop;
} ST_SND;


//---------------------------------------------------------------------------
void SndInit(void);

IWRAM_CODE void SndPlay(u32 id, u8* data, u32 size, s32 adjust, bool isLoop);
IWRAM_CODE void SndPlayBgm(u8* data, u32 size, s32 adjust, bool isLoop);
IWRAM_CODE void SndPlaySe(u8* data, u32 size, s32 adjust, bool isLoop);

IWRAM_CODE void SndStopBgm(void);
IWRAM_CODE void SndStopSe(void);

IWRAM_CODE bool SndIsPlayBgm(void);
IWRAM_CODE bool SndIsPlaySe(void);

IWRAM_CODE void SndIntrBgm(void);
IWRAM_CODE void SndIntrSe(void);

IWRAM_CODE void SndIntrBgmStart(void);
IWRAM_CODE void SndIntrBgmStop(void);
IWRAM_CODE void SndIntrSeStart(void);
IWRAM_CODE void SndIntrSeStop(void);


#ifdef __cplusplus
}
#endif
#endif
