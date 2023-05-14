#ifndef __MAIN_H__
#define __MAIN_H__
#ifdef __cplusplus
extern "C" {
#endif

#include "lib/gba.h"

//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
typedef struct {
	u16  fps;
	s16  fpsTimer;
	s16  fpsCount;

	s16  gameTime;
	s16  gameFrame;
	s16  frameCount;

	u16  deg;
	u16  delay;
} ST_MAIN;

//---------------------------------------------------------------------------


#ifdef __cplusplus
}
#endif
#endif
