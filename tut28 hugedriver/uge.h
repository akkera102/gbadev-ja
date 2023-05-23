#ifndef UGE_H
#define UGE_H
#ifdef __cplusplus
extern "C" {
#endif

#include "lib/gba.h"

//---------------------------------------------------------------------------
#define DN(A, B, C) (u8)(A | ((B & 0x10) << 3)),(u8)(((B << 4) & 0xFF) | (C >> 8)),(u8)(C & 0xFF)

#define C_3 0
#define Cs3 1
#define D_3 2
#define Ds3 3
#define E_3 4
#define F_3 5
#define Fs3 6
#define G_3 7
#define Gs3 8
#define A_3 9
#define As3 10
#define B_3 11
#define C_4 12
#define Cs4 13
#define D_4 14
#define Ds4 15
#define E_4 16
#define F_4 17
#define Fs4 18
#define G_4 19
#define Gs4 20
#define A_4 21
#define As4 22
#define B_4 23
#define C_5 24
#define Cs5 25
#define D_5 26
#define Ds5 27
#define E_5 28
#define F_5 29
#define Fs5 30
#define G_5 31
#define Gs5 32
#define A_5 33
#define As5 34
#define B_5 35
#define C_6 36
#define Cs6 37
#define D_6 38
#define Ds6 39
#define E_6 40
#define F_6 41
#define Fs6 42
#define G_6 43
#define Gs6 44
#define A_6 45
#define As6 46
#define B_6 47
#define C_7 48
#define Cs7 49
#define D_7 50
#define Ds7 51
#define E_7 52
#define F_7 53
#define Fs7 54
#define G_7 55
#define Gs7 56
#define A_7 57
#define As7 58
#define B_7 59
#define C_8 60
#define Cs8 61
#define D_8 62
#define Ds8 63
#define E_8 64
#define F_8 65
#define Fs8 66
#define G_8 67
#define Gs8 68
#define A_8 69
#define As8 70
#define B_8 71
#define LAST_NOTE 72
#define ___ 90

//---------------------------------------------------------------------------

typedef struct {
	u8  sweep;
	u8  len_duty;
	u8  envelope;
	u8* subpattern;
	u8  highmask;
} ST_UGE_DUTY;

typedef struct {
	u8  length;
	u8  volume;
	u8  waveform;
	u8* subpattern;
	u8  highmask;
} ST_UGE_WAVE;

typedef struct {
	u8  envelope;
	u8* subpattern;
	u8  highmask;
	u8  unused1;
	u8  unused2;
} ST_UGE_NOISE;

typedef struct {
	u8   tempo;
	u8   order_cnt;
	u8** order1;
	u8** order2;
	u8** order3;
	u8** order4;

	ST_UGE_DUTY*  duty_instruments;
	ST_UGE_WAVE*  wave_instruments;
	ST_UGE_NOISE* noise_instruments;

	void** routines;
	u8*    waves;

} ST_UGE_SONG;

enum UGE_ID_CHANNEL {
	HT_CH1 = 0,
	HT_CH2,
	HT_CH3,
	HT_CH4
};

enum UGE_ID_MUTE {
	HT_CH_PLAY = 0,
	HT_CH_MUTE
};


//---------------------------------------------------------------------------

EWRAM_CODE void UgeInit(ST_UGE_SONG* song);
IWRAM_CODE void UgeDoSound(void);

EWRAM_CODE void UgeSetMuteChannel(enum UGE_ID_CHANNEL ch, enum UGE_ID_MUTE mute);
EWRAM_CODE void UgeSetPosition(u8 pattern);


#ifdef __cplusplus
}
#endif
#endif

