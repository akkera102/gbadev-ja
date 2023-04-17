#include "lib/gba.h"
#include "bg.h"
#include "irq.arm.h"
#include "key.h"
#include "spr.h"

//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
int main(void)
{
	REG_WSCNT = 0x4317;

	BgInit();
	IrqInit();
	KeyInit();

	SprInit();
	SpriteSetAlpha();


	char strX[32], strY[32], strM[32];
	u16 cnt;

	s16 x = ((240 / 2) - (8 / 2)) << 4;
	s16 y = ((160 / 2) - (8 / 2)) << 4;
	s16 m = 25;

	for(;;)
	{
	    VBlankIntrWait();

		KeyExec();
		cnt = KeyGetCnt();

		if(cnt & KEY_UP   ) y-=m;
		if(cnt & KEY_DOWN ) y+=m;
		if(cnt & KEY_LEFT ) x-=m;
		if(cnt & KEY_RIGHT) x+=m;
		if(cnt & KEY_R    ) m+=1;
		if(cnt & KEY_L    ) m-=1;

		if((x>>4) <      0) x = 0;
		if((x>>4) >= 240-8) x = (240-8) << 4;
		if((y>>4) <      0) y = 0;
		if((y>>4) >= 160-8) y = (160-8) << 4;

		if(m <=  0) m =  1;
		if(m >= 50) m = 50;

		SpriteMoveAlpha(x>>4, y>>4);

		_Sprintf(strX, "x:%3d %4d 0x%04x", x>>4, x, x);
		_Sprintf(strY, "y:%3d %4d 0x%04x", y>>4, y, y);
		_Sprintf(strM, "m:%3d", m);

		BgAsciiDrawStr(0, 17, strX);
		BgAsciiDrawStr(0, 18, strY);
		BgAsciiDrawStr(0, 19, strM);
	}
}
