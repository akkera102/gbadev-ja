#ifndef __CODE_H__
#define __CODE_H__
#ifdef __cplusplus
extern "C" {
#endif

#include "lib/gba.h"

//---------------------------------------------------------------------------


//---------------------------------------------------------------------------



//---------------------------------------------------------------------------
s32 CodeRom(void);
EWRAM_CODE s32 CodeEwram(void);
IWRAM_CODE s32 CodeIwram(void);



#ifdef __cplusplus
}
#endif
#endif
