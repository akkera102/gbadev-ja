#include "spr.arm.h"
#include "res.h"
#include "bg.h"


//---------------------------------------------------------------------------
ST_SPR Spr;

// VCOUNT割り込みライン
const s32 SprVmap[SPR_MAX_IDX_CNT+1] = 
{
	218, //  0   218 = 228 - 8 - 2
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
	  0, // 21		// SprVBlank待ち用
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
IWRAM_CODE void SprInitItem(void)
{
	// 0クリア OAM buffer 
	REG_DMA0SAD = (u32)&Spr.zero;
	REG_DMA0DAD = (u32)&Spr.item;
	REG_DMA0CNT = (u32)sizeof(Spr.item)/4 | (DMA_SRC_FIXED | DMA_DST_INC | DMA32 | DMA_ENABLE);
}
//---------------------------------------------------------------------------
IWRAM_CODE void SprExec(void)
{
	SprInitItem();

	s32 i, cnt = 0; 
	ST_SPR_ITEM* pW[SPR_MAX_IDX_CNT];

	for(i=0; i<SPR_MAX_IDX_CNT; i++)
	{
		// 8ラインごとの弾数を取得
		Spr.idxCnt[i] = BulletGetIdxCnt(i);

		// 各VCOUNTでDMA転送するバッファ位置を格納
		Spr.idx[i] = cnt;

		// ソートで使うワークポインタを格納
		pW[i] = &Spr.item[cnt];

		cnt += Spr.idxCnt[i];
	}

	// 弾情報ポインタを取得（高速化の為、モジュール化度外視）
	ST_BULLET_CHR* pS = BulletGetChrPointer();

	// 最初の弾情報を取得
	while(pS->is == FALSE)
	{
		pS++;
	}

	// ソート開始
	s32 max = BulletGetMaxCnt();

	for(i=0; i<max; i++)
	{
		s32 x  = FIX2INT(pS->x);
		s32 y  = FIX2INT(pS->y);
		u32 y8 = (y + 8) / 8;

		pW[y8]->attr0 = OBJ_16_COLOR | OBJ_SQUARE | (y & 0x00ff);
		pW[y8]->attr1 = OBJ_SIZE(0)  | (x & 0x01ff);
		pW[y8]->attr2 = (1+Spr.chrNo);
		pW[y8]++;

		// 次の弾情報を取得
		do {
			pS++;

		} while(pS->is == FALSE);
	}

	// スプライトアニメーション
	Spr.chrNo++;
	Spr.chrNo &= 0x03;
}
//---------------------------------------------------------------------------
IWRAM_CODE void SprVBlank(void)
{
	// 0クリア OAM 
	REG_DMA0SAD = (u32)&Spr.zero;
	REG_DMA0DAD = (u32)OAM;
	REG_DMA0CNT = (u32)128*2 | (DMA_SRC_FIXED | DMA_DST_INC | DMA32 | DMA_ENABLE);


	Spr.oamCnt = 0;
	Spr.vCnt = 0;

	REG_DISPSTAT = (REG_DISPSTAT & STAT_MASK) | LCDC_VCNT | VCOUNT(SprVmap[Spr.vCnt]);
}
//---------------------------------------------------------------------------
IWRAM_CODE void SprVCount(void)
{
	s32 idx = Spr.idx[Spr.vCnt];		// 転送するSpr.itemのインデックス
	s32 cnt = Spr.idxCnt[Spr.vCnt];		// 転送する数
	s32 all = Spr.oamCnt + cnt;			// OAMインデックス + 転送する数

	s32 sad0 = idx;
	s32 dad0 = Spr.oamCnt;
	s32 cnt0 = cnt;

	s32 sad1 = 0;
	s32 dad1 = 0;
	s32 cnt1 = 0;

	if(all >= SPR_MAX_OAM_CNT)
	{
		cnt0  = all - SPR_MAX_OAM_CNT;
		cnt1  = cnt - cnt0;
		sad1  = idx + cnt0;
	}


	OBJATTR* pS = (OBJATTR*)&Spr.item;
	OBJATTR* pD = (OBJATTR*)OAM;

	if(cnt0 != 0)
	{
		REG_DMA0SAD = (u32)&pS[sad0];
		REG_DMA0DAD = (u32)&pD[dad0];
		REG_DMA0CNT = (u32)cnt0*2 | (DMA_SRC_INC | DMA_DST_INC | DMA32 | DMA_ENABLE);
	}

	if(cnt1 != 0)
	{
		REG_DMA1SAD = (u32)&pS[sad1];
		REG_DMA1DAD = (u32)&pD[dad1];
		REG_DMA1CNT = (u32)cnt1*2 | (DMA_SRC_INC | DMA_DST_INC | DMA32 | DMA_ENABLE);
	}


	Spr.oamCnt += cnt;
	Spr.oamCnt &= (SPR_MAX_OAM_CNT - 1);

	Spr.vCnt++;
	REG_DISPSTAT = (REG_DISPSTAT & STAT_MASK) | LCDC_VCNT | VCOUNT(SprVmap[Spr.vCnt]);
}
