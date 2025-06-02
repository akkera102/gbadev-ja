#ifndef FONT_H
#define FONT_H
#ifdef __cplusplus
extern "C" {
#endif


#include "lib/gba.h"

//---------------------------------------------------------------------------

typedef struct {
	u8*  pDat;
	u16  imgCx;
	u16  cx;
	u16  cy;
} ST_FONT;

//---------------------------------------------------------------------------
void FontInit(void);
IWRAM_CODE void FontDrawChr(s32 sx, s32 sy, u16 col, u16 chr);
IWRAM_CODE void FontDrawStr(s32 sx, s32 sy, u16 col, char* str);
IWRAM_CODE void FontDrawPrintf(s32 sx, s32 sy, u16 col, char* format, ...);
IWRAM_CODE void FontDrawFillBox(s32 sx, s32 sy, s32 cx, s32 cy, u16 col);


#ifdef __cplusplus
}
#endif
#endif
