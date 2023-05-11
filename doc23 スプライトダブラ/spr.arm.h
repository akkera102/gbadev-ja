#ifndef SPR_H
#define SPR_H
#ifdef __cplusplus
extern "C" {
#endif


#include "lib/gba.h"
#include "bullet.arm.h"

//---------------------------------------------------------------------------
#define SPR_MAX_OAM_CNT					128
#define SPR_MAX_ITEM_CNT				BULLET_MAX_CHR_CNT		// bullet.h
#define SPR_MAX_IDX_CNT					BULLET_MAX_IDX_CNT

typedef struct {
	u16 attr0;
	u16 attr1;
	u16 attr2;
	u16 attr3;

} ST_SPR_ITEM;


typedef struct {
	s16 vCnt;						// VCOUNT�p�C���f�b�N�X
	s16 oamCnt;						// VCOUNT�pOAM�̓]���J�n�ʒu

	u16 chrNo;						// �L�����N�^�[�i���o�[

	s16 idx[SPR_MAX_IDX_CNT];		// 8���C������item�o�b�t�@�J�n�ʒu�C���f�b�N�X
	s16 idxCnt[SPR_MAX_IDX_CNT];	// 8���C�����̒e��

	u32 zero ALIGN(4);				// �[���N���A�p

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
