#ifndef RTC_H
#define RTC_H
#ifdef __cplusplus
extern "C" {
#endif

#include "lib/gba.h"

// S3511 - 8pin RTC with 3-wire serial bus (used in Boktai)
// The chip is accessed via 4bit I/O port (only 3bits are used for RTC)

// M3 MiniSD �œ���m�F���܂���

//---------------------------------------------------------------------------
#define REG_RTC_DATA		*(vu16*)(0x080000C4)	// I/O Port Data�i�r�b�g�z��@��F 0x3 : CS=0, SIO=1, SCK=1�j
#define REG_RTC_RW			*(vu16*)(0x080000C6)	// I/O Port Direction
#define REG_RTC_ENABLE		*(vu16*)(0x080000C8)	// I/O Port Control (selectable W or R/W)
#define RTC_MAX_REG_CNT		7

//---------------------------------------------------------------------------
// BCD �`���iu8 * 7�j
// �N�@�i00�`99�j
// ���@�i01�`12�j
// ���@�i01�`31�j
// �j���i00�`06�j�@���j�����琔���܂�
// ���@�i00�`23�j�@�ŏ�ʃr�b�g�FAM/PM�t���O
// ���@�i00�`59�j
// �b�@�i00�`59�j�@�ŏ�ʃr�b�g�F�e�X�g���[�h

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
