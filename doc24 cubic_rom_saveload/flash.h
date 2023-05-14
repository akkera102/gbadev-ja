#ifndef FLASH_H
#define FLASH_H
#ifdef __cplusplus
extern "C" {
#endif

#include "lib/gba.h"

//---------------------------------------------------------------------------


//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
EWRAM_CODE void FlashInit(void);
EWRAM_CODE void FlashExec(void);

EWRAM_CODE void FlashByte(u16 adr, u8 dat);
EWRAM_CODE u8   FlashRead(u16 adr);
EWRAM_CODE void FlashWrite(u16 adr, u8 cmd);

EWRAM_CODE void FlashEraseChip(void);
EWRAM_CODE void FlashEraseSector(u16 sec);

EWRAM_CODE void FlashWait(u32 cnt);
EWRAM_CODE void FlashWait2(u32 cnt);

EWRAM_CODE u16  FlashGetId(void);
EWRAM_CODE bool FlashIsExist(void);



#ifdef __cplusplus
}
#endif
#endif
