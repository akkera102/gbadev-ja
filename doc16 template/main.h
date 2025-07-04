#ifndef __MAIN_H__
#define __MAIN_H__
#ifdef __cplusplus
extern "C" {
#endif

#include "lib/gba.h"

//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
typedef struct {
	u32  fps;
	s32  fpsTimer;
	s32  fpsCount;

	s32  gameTime;
	s32  gameFrame;
	s32  frameCount;

	u32  deg;
	u32  delay;
} ST_MAIN;

//---------------------------------------------------------------------------


#ifdef __cplusplus
}
#endif
#endif
