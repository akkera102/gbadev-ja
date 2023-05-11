#include "spr.arm.h"
#include "res.h"
#include "bg.h"


//---------------------------------------------------------------------------
ST_SPR Spr;

// VCOUNT割り込みライン
const s32 SprVmap[SPR_MAX_IDX_CNT] = 
{
	218, //  0
	226, //  1
	  6, //  2
	 14, //  3
	 22, //  4
	 30, //  5
	 38, //  6
	 46, //  7
	 54, //  8
	 62, //  9
	 70, // 10
	 78, // 11
	 86, // 12
	 94, // 13
	102, // 14
	110, // 15
	118, // 16
	126, // 17
	134, // 18
	142, // 19
	150, // 20
};

//---------------------------------------------------------------------------
EWRAM_CODE void SprInit(void)
{
	u16* oam = OBJ_BASE_ADR;
	u16* pal = OBJ_COLORS;
	u32 i;

	for(i=0; i<spr_bullet_smallTilesLen/2; i++)
	{
		oam[16+i] = spr_bullet_smallTiles[i];
	}

	for(i=0; i<spr_bullet_smallPalLen/2; i++)
	{
		pal[i] = spr_bullet_smallPal[i];
	}

	_Memset(&Spr, 0x00, sizeof(ST_SPR));
}
//---------------------------------------------------------------------------
EWRAM_CODE void SprInitItem(void)
{
	// OAM buffer zero clear

	REG_DMA0SAD = (u32)&Spr.zero;
	REG_DMA0DAD = (u32)&Spr.item;
	REG_DMA0CNT = (u32)sizeof(Spr.item)/4 | (DMA_SRC_FIXED | DMA_DST_INC | DMA32 | DMA_ENABLE);
}
//---------------------------------------------------------------------------
IWRAM_CODE void SprExec(void)
{
	s32 i, max, cnt = 0; 
	ST_SPR_ITEM* pW[SPR_MAX_IDX_CNT];

	for(i=0; i<SPR_MAX_IDX_CNT; i++)
	{
		// y8ラインの弾数を取得
		Spr.idxCnt[i] = BulletGetIdxCnt(i);

		// VCOUNT用のバッファ位置を格納、ワークポインタを格納
		Spr.idx[i] = cnt;
		pW[i] = &Spr.item[cnt];

		cnt += Spr.idxCnt[i];
	}

	// ソート
	max = BulletGetMaxCnt();

	BulletSeekInit();

	for(i=0; i<max; i++)
	{
		s32 x  = BulletSeekX();
		s32 y  = BulletSeekY();
		u32 y8 = (y + 8) / 8;

		pW[y8]->attr0 = OBJ_16_COLOR | OBJ_SQUARE | (y & 0x00ff);
		pW[y8]->attr1 = OBJ_SIZE(0)  | (x & 0x01ff);
		pW[y8]->attr2 = (1+Spr.pat);
		pW[y8]++;

		BulletSeekNext();
	}

	// スプライトアニメーション
	Spr.pat++;
	Spr.pat &= 0x03;
}
//---------------------------------------------------------------------------
IWRAM_CODE void SprVBlank(void)
{
	Spr.vCnt = 0;
	Spr.sprCnt = 0;

	// OAM zero clear
	REG_DMA0SAD = (u32)&Spr.zero;
	REG_DMA0DAD = (u32)OAM;
	REG_DMA0CNT = (u32)128*2 | (DMA_SRC_FIXED | DMA_DST_INC | DMA32 | DMA_ENABLE);


	REG_DISPSTAT = (REG_DISPSTAT & STAT_MASK) | LCDC_VCNT | VCOUNT(SprVmap[Spr.vCnt]);
}
//---------------------------------------------------------------------------
IWRAM_CODE void SprVCount(void)
{
	s32 idxCnt = Spr.idxCnt[Spr.vCnt];
	s32 allCnt = Spr.sprCnt + idxCnt;

	OBJATTR* pM = (OBJATTR*)&Spr.item;;
	OBJATTR* pO = (OBJATTR*)OAM;

	s32 sad1 = Spr.idx[Spr.vCnt];
	s32 dad1 = Spr.sprCnt;
	s32 cnt1 = (allCnt >= SPR_MAX_RASTER_CNT) ? (SPR_MAX_RASTER_CNT - 1) - idxCnt : idxCnt;

	s32 sad2 = allCnt & (SPR_MAX_RASTER_CNT - 1);
	s32 dad2 = 0;
	s32 cnt2 = (allCnt >= SPR_MAX_RASTER_CNT) ? allCnt - SPR_MAX_RASTER_CNT : 0;

	if(cnt1 != 0)
	{
		REG_DMA0SAD = (u32)&pM[sad1];
		REG_DMA0DAD = (u32)&pO[dad1];
		REG_DMA0CNT = (u32)cnt1*2 | (DMA_SRC_INC | DMA_DST_INC | DMA32 | DMA_ENABLE);
	}

	if(cnt2 != 0)
	{
		REG_DMA1SAD = (u32)&pM[sad2];
		REG_DMA1DAD = (u32)&pO[dad2];
		REG_DMA1CNT = (u32)cnt2*2 | (DMA_SRC_INC | DMA_DST_INC | DMA32 | DMA_ENABLE);
	}

	Spr.sprCnt += idxCnt;
	Spr.sprCnt &= (SPR_MAX_RASTER_CNT - 1);


	if(Spr.vCnt < SPR_MAX_IDX_CNT)
	{
		Spr.vCnt++;
	}

	REG_DISPSTAT = (REG_DISPSTAT & STAT_MASK) | LCDC_VCNT | VCOUNT(SprVmap[Spr.vCnt]);
}
