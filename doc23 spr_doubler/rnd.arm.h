#ifndef __RND_H__
#define __RND_H__
#ifdef __cplusplus
extern "C" {
#endif

#include "lib/gba.h"
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
void RndInit(void);
void RndInit2(u32 s);
IWRAM_CODE u32  RndU32(void);


#ifdef __cplusplus
}
#endif
#endif