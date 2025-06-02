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
	u16 cnt;					// ���݂̃L�[
	u16 trg;					// �����ꂽ�L�[
	u16 off;					// �����ꂽ�L�[
	u16 rep;					// ���s�[�g�L�[
	s16 repCnt;					// ���s�[�g�J�E���g
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
