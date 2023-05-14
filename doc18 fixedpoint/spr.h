#ifndef SPR_H
#define SPR_H
#ifdef __cplusplus
extern "C" {
#endif


#include "lib/gba.h"

//---------------------------------------------------------------------------

//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
EWRAM_CODE void SprInit(void);
EWRAM_CODE void SprInitOam(void);
EWRAM_CODE void SprSetDat(u16* pTile, u32 tileSize, u16* pPal, u32 palSize);
EWRAM_CODE void SprSetDatChr(void);

EWRAM_CODE void SpriteMove(u32 num, s32 x, s32 y);
EWRAM_CODE void SpriteSetSize(u32 num, u32 size, u32 form, u32 col);
EWRAM_CODE void SpriteSetChr(u32 num, u32 chr);

EWRAM_CODE void SpriteSetAlpha(void);
EWRAM_CODE void SpriteMoveAlpha(s32 x, s32 y);


#ifdef __cplusplus
}
#endif
#endif
