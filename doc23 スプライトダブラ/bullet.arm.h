#ifndef BULLET_H
#define BULLET_H
#ifdef __cplusplus
extern "C" {
#endif

#include "lib/gba.h"

//---------------------------------------------------------------------------
#define BULLET_MAX_CHR_CNT			384
#define BULLET_MAX_IDX_CNT			21			// (縦画面160+非表示8) / 8

#define INT2FIX(A)					((A)<<7)
#define FIX2INT(A)					((A)>>7)

//---------------------------------------------------------------------------

typedef struct {
	bool is;
	s16  x;
	s16  y;
	s16  mx;
	s16  my;

} ST_BULLET_CHR;

typedef struct {
	s16  seek;

	s16  maxCnt;								// 最大数
	s16  idxCnt[BULLET_MAX_IDX_CNT];			// yラインを21分割したカウント数

	ST_BULLET_CHR chr[BULLET_MAX_CHR_CNT];		// 弾情報

} ST_BULLET;


//---------------------------------------------------------------------------
EWRAM_CODE void BulletInit(void);
IWRAM_CODE void BulletExec(void);
IWRAM_CODE void BulletReg(s32 x, s32 y);
IWRAM_CODE s16  BulletRnd(void);

IWRAM_CODE void BulletSeekInit(void);
IWRAM_CODE void BulletSeekNext(void);
IWRAM_CODE s16  BulletSeekX(void);
IWRAM_CODE s16  BulletSeekY(void);

IWRAM_CODE s16  BulletGetMaxCnt(void);
IWRAM_CODE s16  BulletGetIdxCnt(s32 i);


#ifdef __cplusplus
}
#endif
#endif
