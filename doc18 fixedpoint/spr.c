#include "spr.h"
#include "res.h"

//---------------------------------------------------------------------------
u32 dummy ALIGN(4);


//---------------------------------------------------------------------------
EWRAM_CODE void SprInit(void)
{
	SprInitOam();
	SprSetDatChr();

	REG_DISPCNT |= (OBJ_ON | OBJ_2D_MAP);
}
//---------------------------------------------------------------------------
EWRAM_CODE void SprInitOam(void)
{
	REG_DMA3SAD = (u32)&dummy;
	REG_DMA3DAD = (u32)OAM;
	REG_DMA3CNT = (u32)(0x400/4) | (DMA_SRC_FIXED | DMA_DST_INC | DMA32 | DMA_ENABLE);
}
//---------------------------------------------------------------------------
EWRAM_CODE void SprSetDat(u16* pTile, u32 tileSize, u16* pPal, u32 palSize)
{
	u32 i;

	for(i=0; i<tileSize/2; i++)
	{
		((u16*)OBJ_BASE_ADR)[i] = pTile[i];
	}

	for(i=0; i<palSize/2; i++)
	{
		((u16*)OBJ_COLORS)[i] = pPal[i];
	}
}
//---------------------------------------------------------------------------
EWRAM_CODE void SprSetDatChr(void)
{
	SprSetDat((u16*)spr_testTiles, spr_testTilesLen, (u16*)spr_testPal, spr_testPalLen);
}
//---------------------------------------------------------------------------
EWRAM_CODE void SpriteMove(u32 num, s32 x, s32 y)
{
	OBJATTR* sp = (OBJATTR*)OAM + num;

	sp->attr1 &= 0xfe00;
	sp->attr0 &= 0xff00;
	sp->attr1 |= (x & 0x01ff);
	sp->attr0 |= (y & 0x00ff);
}
//---------------------------------------------------------------------------
EWRAM_CODE void SpriteSetSize(u32 num, u32 size, u32 form, u32 col)
{
	OBJATTR* sp = (OBJATTR*)OAM + num;

	sp->attr0 &= 0x1fff;
	sp->attr1 &= 0x3fff;
	sp->attr0 |= col  | form | (160);
	sp->attr1 |= size | (240);
}
//---------------------------------------------------------------------------
EWRAM_CODE void SpriteSetChr(u32 num, u32 chr)
{
	OBJATTR* sp = (OBJATTR*)OAM + num;

	sp->attr2 &= 0xfc00;
	sp->attr2 |= chr;
}
//---------------------------------------------------------------------------
EWRAM_CODE void SpriteSetAlpha(void)
{
	SpriteSetSize(0, OBJ_SIZE(Sprite_8x8), OBJ_SQUARE, OBJ_16_COLOR);
	SpriteSetChr (0, 33);
	SpriteMove   (0, 240, 160);
}
//---------------------------------------------------------------------------
EWRAM_CODE void SpriteMoveAlpha(s32 x, s32 y)
{
	SpriteMove(0, x, y);
}
