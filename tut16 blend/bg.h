#ifndef __BG_H__
#define __BG_H__
#ifdef __cplusplus
extern "C" {
#endif

#include "lib/gba.h"

//---------------------------------------------------------------------------
#define BG_MAX_CNT				4


//---------------------------------------------------------------------------
typedef struct {
	u32  mapBase;
	u16* mapBaseAdr;
	u32  tileBase;
	u16* tileBaseAdr;
} ST_BG;


//---------------------------------------------------------------------------
void BgInit(void);
void BgInitLcd(void);
void Bg0Init(void);
void Bg1Init(void);
void Bg2Init(void);
void Bg3Init(void);


#ifdef __cplusplus
}
#endif
#endif
