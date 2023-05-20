#ifndef __MODE3_H__
#define __MODE3_H__
#ifdef __cplusplus
extern "C" {
#endif

#include "lib/gba.h"

//---------------------------------------------------------------------------


//---------------------------------------------------------------------------

typedef struct {
	u8*  pDat;
	u16  imgCx;
	u16  cx;
	u16  cy;
} ST_MODE3;


//---------------------------------------------------------------------------
EWRAM_CODE void Mode3Init(void);

IWRAM_CODE void Mode3DrawChr(s32 sx, s32 sy, u16 chr);
IWRAM_CODE void Mode3DrawStr(s32 sx, s32 sy, char* str);
IWRAM_CODE void Mode3DrawPrintf(s32 sx, s32 sy, char* format, ...);


#ifdef __cplusplus
}
#endif
#endif
