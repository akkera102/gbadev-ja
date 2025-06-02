#ifndef FLASH_H
#define FLASH_H
#ifdef __cplusplus
extern "C" {
#endif

#include "lib/gba.h"

//---------------------------------------------------------------------------


//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
void FlashInit(void);
void FlashExec(void);

void FlashByte(u16 adr, u8 dat);
u8   FlashRead(u16 adr);
void FlashWrite(u16 adr, u8 cmd);

void FlashEraseChip(void);
void FlashEraseSector(u16 sec);

void FlashWait(u32 cnt);
void FlashWait2(u32 cnt);

u16  FlashGetId(void);
bool FlashIsExist(void);



#ifdef __cplusplus
}
#endif
#endif
