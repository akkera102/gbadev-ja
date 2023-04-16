#ifndef __MT19937AR_H__
#define __MT19937AR_H__
#ifdef __cplusplus
extern "C" {
#endif

#include "gba.h"
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
IWRAM_CODE void  _Srand(u32 s);
IWRAM_CODE u32   _Rand(u32 num);




#ifdef __cplusplus
}
#endif
#endif

