#ifndef MALLOC_H
#define MALLOC_H
#ifdef __cplusplus
extern "C" {
#endif

#include "lib/gba.h"

//---------------------------------------------------------------------------


//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
EWRAM_CODE u32* MallocPatch(u32 size);


#ifdef __cplusplus
}
#endif
#endif
