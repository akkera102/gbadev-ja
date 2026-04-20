#ifndef __IRQ_H__
#define __IRQ_H__
#ifdef __cplusplus
extern "C" {
#endif


#include "lib/gba.h"

//---------------------------------------------------------------------------


//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
void IrqInit(void);
void IrqInitAd(void);
void IrqInitSnd(void);

IWRAM_CODE void IrqHandler(void);
IWRAM_CODE void IrqHandlerAd(void);
IWRAM_CODE void IrqHandlerSnd(void);


#ifdef __cplusplus
}
#endif
#endif
