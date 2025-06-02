#ifndef BG_H
#define BG_H
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

void BgDrawStr(s32 x, s32 y, char* s);
void BgDrawPrintf(s32 x, s32 y, char* format, ...);


#ifdef __cplusplus
}
#endif
#endif
