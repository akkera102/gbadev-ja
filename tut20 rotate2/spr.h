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
void SprSetScaleRot(u32 num, s16 pa, s16 pb, s16 pc, s16 pd);
void SprSetPal(u32 num, u32 pal);
void SprSetRotScale(u32 num, u32 no, u32 isFlag);
void SprSetDubleFlag(u32 num, u32 no, u32 isFlag);
void SprSetRotate(u32 num, s32 angle);

#ifdef __cplusplus
}
#endif
#endif
