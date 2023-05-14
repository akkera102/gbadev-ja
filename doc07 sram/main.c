#include "lib/gba.h"

#define ADR_SRAM     (u8*)0xe000000

//---------------------------------------------------------------------------
u8 SRAMRead8(u32 offset)
{
	u8* sram = (u8*)ADR_SRAM + offset;
	return (u8)sram[0];
}
//---------------------------------------------------------------------------
u16 SRAMRead16(u32 offset)
{
	u16 ret;

	ret  = SRAMRead8(offset++);
	ret |= SRAMRead8(offset) << 8;

	return ret;
}
//---------------------------------------------------------------------------
u32 SRAMRead32(u32 offset)
{
	u32 ret;

	ret  = SRAMRead8(offset++);
	ret |= SRAMRead8(offset++) <<  8;
	ret |= SRAMRead8(offset++) << 16;
	ret |= SRAMRead8(offset)   << 24;

	return ret;
}
//---------------------------------------------------------------------------
void SRAMWrite8(u32 offset, u8 data)
{
	u8* sram = (u8*)ADR_SRAM + offset;
	*sram = (u8)(data & 0xff);
}
//---------------------------------------------------------------------------
void SRAMWrite16(u32 offset, u16 data)
{
	SRAMWrite8(offset++, (u8)((data   ) & 0xff));
	SRAMWrite8(offset++, (u8)((data>>8) & 0xff));
}
//---------------------------------------------------------------------------
void SRAMWrite32(u32 offset, u32 data)
{
	SRAMWrite8(offset++, (u8)((data    ) & 0xff));
	SRAMWrite8(offset++, (u8)((data>>8 ) & 0xff));
	SRAMWrite8(offset++, (u8)((data>>16) & 0xff));
	SRAMWrite8(offset++, (u8)((data>>24) & 0xff));
}
//---------------------------------------------------------------------------
u8* SRAMGetPointer()
{
	return ADR_SRAM;
}
//---------------------------------------------------------------------------
void WaitForVsync(void)
{
	while (*(volatile u16*)0x4000006 >= 160) {};
	while (*(volatile u16*)0x4000006 <  160) {};
}
//---------------------------------------------------------------------------
int main(void)
{
	// エミュレータのTools->Memory viewerで書き込まれた値を確認してください
	// SRAMのアドレス：E000000
	SRAMWrite8(0x00, 1);
	SRAMWrite16(0x04, 2);
	SRAMWrite32(0x08, 0xdeadbeef);

	// エミュレータのTools->Loggingで読み込まれた値を確認してください
	TRACE("0x%x\n", SRAMRead8(0x00));
	TRACE("0x%x\n", SRAMRead16(0x04));
	TRACE("0x%x\n", SRAMRead32(0x08));

	for(;;)
	{
		WaitForVsync();
	}
}
