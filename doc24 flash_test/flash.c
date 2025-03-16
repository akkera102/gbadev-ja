#include "flash.h"
#include "bg.h"

// cardridge 256Mbit + Flash SST39VF040
// https://cubic-style.jp/

//---------------------------------------------------------------------------
EWRAM_CODE void FlashInit(void)
{
	BgDrawPrintf(0, 0, "MemoryBackup Cubic Test");
}
//---------------------------------------------------------------------------
EWRAM_CODE void FlashExec(void)
{
	if(FlashIsExist() == FALSE)
	{
		BgDrawPrintf(0, 2, "Flash not found");
		for(;;){}
	}

	BgDrawPrintf(2, 1, "Type : Flash");
	BgDrawPrintf(2, 2, "Id   : %x", FlashGetId());

	BgDrawPrintf(2, 4, "Erase 0, 1, 2");
	FlashEraseSector(0);
	FlashEraseSector(1);
	FlashEraseSector(2);

	FlashByte(0x0000, 1);
	FlashByte(0x0001, 2);
	FlashByte(0x0002, 3);

	FlashByte(0x1000, 4);
	FlashByte(0x1001, 5);
	FlashByte(0x1002, 6);

	FlashByte(0x2000, 7);
	FlashByte(0x2001, 8);
	FlashByte(0x2002, 9);

	BgDrawPrintf(3,  5, "%x %x %x", FlashRead(0x0000), FlashRead(0x0001), FlashRead(0x0002));
	BgDrawPrintf(3,  6, "%x %x %x", FlashRead(0x1000), FlashRead(0x1001), FlashRead(0x1002));
	BgDrawPrintf(3,  7, "%x %x %x", FlashRead(0x2000), FlashRead(0x2001), FlashRead(0x2002));

	BgDrawPrintf(2,  8, "Erase 1");
	FlashEraseSector(1);

	BgDrawPrintf(3,  9, "%x %x %x", FlashRead(0x0000), FlashRead(0x0001), FlashRead(0x0002));
	BgDrawPrintf(3, 10, "%x %x %x", FlashRead(0x1000), FlashRead(0x1001), FlashRead(0x1002));
	BgDrawPrintf(3, 11, "%x %x %x", FlashRead(0x2000), FlashRead(0x2001), FlashRead(0x2002));

	BgDrawPrintf(2, 12, "Erase Chip");
	FlashEraseChip();

	BgDrawPrintf(3, 13, "%x %x %x", FlashRead(0x0000), FlashRead(0x0001), FlashRead(0x0002));
	BgDrawPrintf(3, 14, "%x %x %x", FlashRead(0x1000), FlashRead(0x1001), FlashRead(0x1002));
	BgDrawPrintf(3, 15, "%x %x %x", FlashRead(0x2000), FlashRead(0x2001), FlashRead(0x2002));

	BgDrawPrintf(2, 16, "Done");
}
//---------------------------------------------------------------------------
EWRAM_CODE void FlashByte(u16 adr, u8 dat)
{
	// Byte-Program
	FlashWrite(0x5555, 0xAA);
	FlashWrite(0x2AAA, 0x55);
	FlashWrite(0x5555, 0xA0);
	FlashWrite(adr, dat);

	// 20us
	FlashWait(400);
}
//---------------------------------------------------------------------------
EWRAM_CODE u8 FlashRead(u16 adr)
{
	u8* p = (u8*)SRAM + adr;

	u8 ret = *p;

	return ret;
}
//---------------------------------------------------------------------------
EWRAM_CODE void FlashWrite(u16 adr, u8 cmd)
{
	u8* p = (u8*)SRAM + adr;

	*p = cmd;

	__asm("NOP");
}
//---------------------------------------------------------------------------
EWRAM_CODE void FlashEraseChip(void)
{
	// Chip-Erase
	FlashWrite(0x5555, 0xAA);
	FlashWrite(0x2AAA, 0x55);
	FlashWrite(0x5555, 0x80);
	FlashWrite(0x5555, 0xAA);
	FlashWrite(0x2AAA, 0x55);
	FlashWrite(0x5555, 0x10);

	// 100ms
	FlashWait2(10);
}
//---------------------------------------------------------------------------
EWRAM_CODE void FlashEraseSector(u16 sec)
{
	_ASSERT(sec < 0x10);


	// Sector-Erase
	FlashWrite(0x5555, 0xAA);
	FlashWrite(0x2AAA, 0x55);
	FlashWrite(0x5555, 0x80);
	FlashWrite(0x5555, 0xAA);
	FlashWrite(0x2AAA, 0x55);
	FlashWrite(sec * 0x1000, 0x30);

	// 25ms
	FlashWait2(3);
}
//---------------------------------------------------------------------------
EWRAM_CODE void FlashWait(u32 cnt)
{
	for(vu32 i=0; i<cnt; i++)
	{
		// 1T 0.0625usi‘åŽG”c‚Éj
		__asm("NOP");
	}
}
//---------------------------------------------------------------------------
EWRAM_CODE void FlashWait2(u32 cnt)
{
	for(vu32 i=0; i<cnt; i++)
	{
		// 1T 16.743ms
		while(REG_VCOUNT >= 160) {};
		while(REG_VCOUNT <  160) {};
	}
}
//---------------------------------------------------------------------------
// SST39VF010 : 0xD5BF
// SST39VF020 : 0xD6BF
// SST39VF040 : 0xD7BF
EWRAM_CODE u16 FlashGetId(void)
{
	// ID Entry
	FlashWrite(0x5555, 0xAA);
	FlashWrite(0x2AAA, 0x55);
	FlashWrite(0x5555, 0x90);

	// Read ID
	u8 id0 = FlashRead(0x0000);
	u8 id1 = FlashRead(0x0001);

	// ID Exit
	FlashWrite(0x5555, 0xAA);
	FlashWrite(0x2AAA, 0x55);
	FlashWrite(0x5555, 0xF0);

	return id0 | (id1 << 8);
}
//---------------------------------------------------------------------------
EWRAM_CODE bool FlashIsExist(void)
{
	u8 t1 = FlashRead(0);
	u8 t2 = ~t1;

	FlashWrite(0, t2);

	if(FlashRead(0) == t2)
	{
		// SRAM
		FlashWrite(0, t1);
		return FALSE;
	}

	return TRUE;
}
