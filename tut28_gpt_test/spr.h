#ifndef SPR_H
#define SPR_H
#ifdef __cplusplus
extern "C" {
#endif


#include "lib/gba.h"

//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
EWRAM_CODE void SprInit(void);

EWRAM_CODE void SprSetSize(u32 num, u32 size, u32 form, u32 col);
EWRAM_CODE void SprSetXy(u32 num, s32 x, s32 y);
EWRAM_CODE void SprSetChr(u32 num, u32 ch);
EWRAM_CODE void SprSetScaleRot(u32 num, s16 pa, s16 pb, s16 pc, s16 pd);
EWRAM_CODE void SprSetPal(u32 num, u32 pal);
EWRAM_CODE void SprSetRotScale(u32 num, u32 no, u32 isFlag);
EWRAM_CODE void SprSetDubleFlag(u32 num, u32 no, u32 isFlag);

#ifdef __cplusplus
}
#endif
#endif
