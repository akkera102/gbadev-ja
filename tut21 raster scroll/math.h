#ifndef MATH_H
#define MATH_H
#ifdef __cplusplus
extern "C" {
#endif


#include "lib/gba.h"

//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
EWRAM_CODE s32 MathSin(u32 theta);
EWRAM_CODE s32 MathCos(u32 theta);
EWRAM_CODE s32 MathAbs(s32 num);
EWRAM_CODE s32 MathClamp(s32 val, s32 min, s32 max);


#ifdef __cplusplus
}
#endif
#endif
