#include "lib/gba.h"

//---------------------------------------------------------------------------
void WaitForVsync(void)
{
	while(*(volatile u16*)0x4000006 >= 160) {};
	while(*(volatile u16*)0x4000006 <  160) {};
}
//---------------------------------------------------------------------------
void WaitForVCount(u32 c)
{
	while(*(volatile u16*)0x4000006 != c) {};
}
//---------------------------------------------------------------------------
u32 GetVCount(void)
{
	return *(volatile u16*)0x4000006;
}
//---------------------------------------------------------------------------
#define LOOP	100

int main(void)
{
	volatile s32 i, r1, r2, c1, c2;
	volatile s32 m;


	// libc --------------------------------
	m = 1234567;

	c1 = 0;
	WaitForVCount(0);

	for(i=0; i<LOOP; i++)
	{
		r1 = m % 13;
	}
	c1 = GetVCount();

	// bios --------------------------------
	m = 1234567;

	c2 = 0;
	WaitForVCount(0);

	for(i=0; i<LOOP; i++)
	{
		r2 = Mod(m, 13);
	}
	c2 = GetVCount();

	// result ------------------------------
	TRACE("result: %d %d\n", r1, r2);
	TRACE("libc: %d\n", c1);
	TRACE("bios: %d\n", c2);

	for(;;)
	{
		WaitForVsync();
	}
}
