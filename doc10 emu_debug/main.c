#include "lib/gba.h"

//---------------------------------------------------------------------------
void WaitForVsync(void)
{
	while(*(volatile u16*)0x4000006 >= 160) {};
	while(*(volatile u16*)0x4000006 <  160) {};
}
//---------------------------------------------------------------------------
int main(void)
{
	// mGBA or VBA1.8.0-beta3
	// Tools->Logging�Ŋm�F���Ă�������

	TRACE("����������\n����������\n����������\n\n");

	TRACE("%d\n", 123456);
	TRACE("%x\n", 0xbeef);
	TRACE("%x\n", 0xdeadbeef);

	for(;;)
	{
		WaitForVsync();
	}
}
