#ifndef RTC_H
#define RTC_H
#ifdef __cplusplus
extern "C" {
#endif

#include "lib/gba.h"

// S3511 - 8pin RTC with 3-wire serial bus (used in Boktai)
// The chip is accessed via 4bit I/O port (only 3bits are used for RTC)

// M3 MiniSD で動作確認しました

//---------------------------------------------------------------------------
#define REG_RTC_DATA		*(vu16*)(0x080000C4)	// I/O Port Data（ビット配列　例： 0x3 : CS=0, SIO=1, SCK=1）
#define REG_RTC_RW			*(vu16*)(0x080000C6)	// I/O Port Direction
#define REG_RTC_ENABLE		*(vu16*)(0x080000C8)	// I/O Port Control (selectable W or R/W)
#define RTC_MAX_REG_CNT		7

//---------------------------------------------------------------------------
// BCD 形式（u8 * 7個）
// 年　（00～99）
// 月　（01～12）
// 日　（01～31）
// 曜日（00～06）　日曜日から数えます
// 時　（00～23）　最上位ビット：AM/PMフラグ
// 分　（00～59）
// 秒　（00～59）　最上位ビット：テストモード

typedef struct {
	bool isEnable;
	u8   reg[RTC_MAX_REG_CNT];

} ST_RTC;


//---------------------------------------------------------------------------
void RtcInit(void);
void RtcExec(void);

void RtcGetTime(void);
void RtcSetTime(void);
u32  RtcIn(void);
void RtcOutCmd(u32 cmd);
void RtcOutReg(u32 reg);


#ifdef __cplusplus
}
#endif
#endif
