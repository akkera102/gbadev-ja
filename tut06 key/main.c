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

		if( !(REG_KEYINPUT & KEY_UP)   ) TRACE("上　ボタン\n");
		if( !(REG_KEYINPUT & KEY_DOWN) ) TRACE("下　ボタン\n");
		if( !(REG_KEYINPUT & KEY_RIGHT)) TRACE("右　ボタン\n");
		if( !(REG_KEYINPUT & KEY_LEFT) ) TRACE("左　ボタン\n");

		if( !(REG_KEYINPUT & KEY_A)    ) TRACE("10進=%d 16進=0x%x 16進4桁=0x%04x \n", x, x, x);
		if( !(REG_KEYINPUT & KEY_B)    ) TRACE("変数x++ \n", x++);
	}
}
