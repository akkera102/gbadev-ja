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


#ifdef __cplusplus
}
#endif
#endif
