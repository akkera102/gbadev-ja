#ifndef __BG_H__
#define __BG_H__
#ifdef __cplusplus
extern "C" {
#endif

#include "lib/gba.h"

//---------------------------------------------------------------------------
#define BG_MAX_CNT				4

#define BG_FONT_SCX				20
#define BG_FONT_SCY				10
#define BG_FONT_DAT_SIZE		128
#define BG_FONT_INVALID_INDEX	5		// エラー時のインデックスコード "・"


//---------------------------------------------------------------------------
typedef struct {
	u32  mapBase;
	u16* mapBaseAdr;
	u32  tileBase;
	u16* tileBaseAdr;
} ST_BG;


typedef struct {
	u8 sig[2];
	u8 ver;
	u8 size;
	u8 index;
	u8 reserved[11];
} __PACKED ST_CCT_HEAD;


typedef struct {
	u8 count;
	u8 reserved[3];
} __PACKED ST_XCCTENT;


typedef struct {
	u8  start;
	u8  end;
	u16 offset;
} __PACKED ST_XCCT;


typedef struct {
	u16* pDat;			// フォントデータ
	u8*  pCct;			// フォントシート
} ST_BG_FONT;


//---------------------------------------------------------------------------
void BgInit(void);
void BgInitLcd(void);
void Bg0Init(void);
void Bg1Init(void);
void Bg2Init(void);
void Bg3Init(void);

void BgAsciiDrawStr(s32 x, s32 y, char* s);

void BgFontInit(void);
void BgFontDrawStr(s32 x, s32 y, char* str);
void BgFontDrawChr(s32 x, s32 y, u16 chr);
u16  BgFontGetIdx(u16 chr);


#ifdef __cplusplus
}
#endif
#endif
