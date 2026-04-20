#ifndef __SND_H__
#define __SND_H__
#ifdef __cplusplus
extern "C" {
#endif

#include "lib/gba.h"

//---------------------------------------------------------------------------
#define SND_CPU_CLOCK			(16 * 1024 * 1024)
#define SND_AUDIO_RATE			16384
#define SND_FPS					60

enum {
	SND_ACT_STOP,
	SND_ACT_START,
	SND_ACT_PLAY,
};


//---------------------------------------------------------------------------
typedef struct {
	s32  act;
	u32  cnt;
	u32  size;
	u8*  pSnd;
	bool isLoop;

} ST_SND;


//---------------------------------------------------------------------------
void SndInit(void);

IWRAM_CODE void SndPlay(u8* pSnd, s32 size, s32 adjust, bool isLoop);
IWRAM_CODE void SndStop(void);

IWRAM_CODE u32  SndGetRem(void);
IWRAM_CODE bool SndIsPlay(void);

IWRAM_CODE void SndIntrVblank(void);


#ifdef __cplusplus
}
#endif
#endif
