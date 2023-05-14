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
EWRAM_CODE void SprSetScale(u32 num, u32 xsc, u32 ysc);
EWRAM_CODE void SprSetPalNo(u32 num, u32 palNo);
EWRAM_CODE void SprSetRotateFlag(u32 num, u32 no, u32 double_flag);

#ifdef __cplusplus
}
#endif
#endif
