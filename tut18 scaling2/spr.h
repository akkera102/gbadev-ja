#ifndef SPR_H
#define SPR_H
#ifdef __cplusplus
extern "C" {
#endif


#include "lib/gba.h"

//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
void SprInit(void);
void SprSetSize(u32 num, u32 size, u32 form, u32 col);
void SprSetXy(u32 num, s32 x, s32 y);
void SprSetChr(u32 num, u32 ch);
void SprSetScale(u32 num, u32 xsc, u32 ysc);
void SprSetPalNo(u32 num, u32 palNo);
void SprSetRotateFlag(u32 num, u32 no, u32 double_flag);

#ifdef __cplusplus
}
#endif
#endif
