#ifndef SPR_H
#define SPR_H
#ifdef __cplusplus
extern "C" {
#endif


#include "lib/gba.h"

//---------------------------------------------------------------------------

//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
void SprInit(void);
void SprInitOam(void);
void SprSetDat(u16* pTile, u32 tileSize, u16* pPal, u32 palSize);
void SprSetDatChr(void);

void SpriteMove(u32 num, s32 x, s32 y);
void SpriteSetSize(u32 num, u32 size, u32 form, u32 col);
void SpriteSetChr(u32 num, u32 chr);

void SpriteSetAlpha(void);
void SpriteMoveAlpha(s32 x, s32 y);


#ifdef __cplusplus
}
#endif
#endif
