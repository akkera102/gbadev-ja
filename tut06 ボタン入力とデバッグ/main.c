#include "lib/gba.h"

//---------------------------------------------------------------------------
void WaitForVsync(void)
{
	while(*(vu16*)0x4000006 >= 160) {};
	while(*(vu16*)0x4000006 <  160) {};
}
//---------------------------------------------------------------------------
int main(void)
{
	SetMode(MODE_3 | BG2_ENABLE);

	u32 x = 0;

	for(;;)
	{
		WaitForVsync();

		if( !(REG_KEYINPUT & KEY_UP)   ) TRACE("��@�{�^��\n");
		if( !(REG_KEYINPUT & KEY_DOWN) ) TRACE("���@�{�^��\n");
		if( !(REG_KEYINPUT & KEY_RIGHT)) TRACE("�E�@�{�^��\n");
		if( !(REG_KEYINPUT & KEY_LEFT) ) TRACE("���@�{�^��\n");

		if( !(REG_KEYINPUT & KEY_A)    ) TRACE("10�i=%d 16�i=0x%x 16�i4��=0x%04x \n", x, x, x);
		if( !(REG_KEYINPUT & KEY_B)    ) TRACE("�ϐ�x++ \n", x++);
	}
}
