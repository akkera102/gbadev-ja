#ifndef KEY_H
#define KEY_H
#ifdef __cplusplus
extern "C" {
#endif

#include "lib/gba.h"

//---------------------------------------------------------------------------
#define KEY_REPEAT_CNT		10


//---------------------------------------------------------------------------
typedef struct {
	u32 cnt;					// 現在のキー
	u32 trg;					// 押されたキー
	u32 off;					// 離されたキー
	u32 rep;					// リピートキー
	s32 repCnt;					// リピートカウント
} ST_KEY;


//---------------------------------------------------------------------------
void KeyInit(void);
void KeyExec(void);

u32  KeyGetCnt(void);
u32  KeyGetTrg(void);
u32  KeyGetOff(void);
u32  KeyGetRep(void);


#ifdef __cplusplus
}
#endif
#endif
