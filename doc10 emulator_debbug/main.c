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
	// Tools->Loggingで確認してください。

	TRACE("あいうえお\nかきくけこ\nさしすせそ\n\n");

	TRACE("10進数：%d\n", 123456);
	TRACE("16進数：%x\n", 0xbeef);
	TRACE("32進数：%x\n", 0xdeadbeef);

	for(;;)
	{
		WaitForVsync();
	}
}
