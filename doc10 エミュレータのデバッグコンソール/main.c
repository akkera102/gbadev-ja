#include "lib/gba.h"

//---------------------------------------------------------------------------
void WaitForVsync(void)
{
	while (*(volatile u16*)0x4000006 >= 160) {};
	while (*(volatile u16*)0x4000006 <  160) {};
}
//---------------------------------------------------------------------------
int main(void)
{
	// Tools->Logging�Ŋm�F���Ă��������B

	TRACE("����������\n����������\n����������\n\n");

	TRACE("10�i���F%d\n", 123456);
	TRACE("16�i���F%x\n", 0xbeef);
	TRACE("32�i���F%x\n", 0xdeadbeef);

	for(;;)
	{
		WaitForVsync();
	}
}
