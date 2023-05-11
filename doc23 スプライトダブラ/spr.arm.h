#ifndef SPR_H
#define SPR_H
#ifdef __cplusplus
extern "C" {
#endif


#include "lib/gba.h"
#include "bullet.arm.h"

//---------------------------------------------------------------------------
#define SPR_MAX_RASTER_CNT				128
#define SPR_MAX_ITEM_CNT				BULLET_MAX_CHR_CNT		// bullet.h
#define SPR_MAX_IDX_CNT					BULLET_MAX_IDX_CNT

typedef struct {
	u16 attr0;
	u16 attr1;
	u16 attr2;
	u16 attr3;

} ST_SPR_ITEM;


typedef struct {
	s16 vCnt;
	s16 sprCnt;
	u16 pat;
	u32 zero;

	s16 idx[SPR_MAX_IDX_CNT];
	s16 idxCnt[SPR_MAX_IDX_CNT];

	ST_SPR_ITEM item[SPR_MAX_ITEM_CNT] ALIGN(4);

} ST_SPR;

//---------------------------------------------------------------------------
EWRAM_CODE void SprInit(void);
EWRAM_CODE void SprInitItem(void);
IWRAM_CODE void SprExec(void);
EWRAM_CODE void SprSetXy(u32 num, s32 x, s32 y);

IWRAM_CODE void SprVBlank(void);
IWRAM_CODE void SprVCount(void);


#ifdef __cplusplus
}
#endif
#endif
