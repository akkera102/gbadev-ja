#include "lib/gba.h"
#include "main.h"
#include "bg.h"
#include "irq.arm.h"

//---------------------------------------------------------------------------
ST_MAIN Main;

//---------------------------------------------------------------------------
int main(void)
{
	REG_WSCNT = 0x4317;

	BgInit();
	IrqInit();

	_Memset(&Main,  0x00, sizeof(ST_MAIN));


	ST_MAIN* p = &Main;
	char str[32];

	for(;;)
	{
	    VBlankIntrWait();

		p->fpsCount++;
		p->gameTime++;
		p->gameFrame++;

		if(p->gameFrame < p->frameCount)
		{
			p->delay     = p->frameCount - p->gameFrame;
			p->gameFrame = p->frameCount;
		}
		else
		{
			p->delay = 0;
		}

		_Sprintf(str, "FREAME:%d", p->frameCount);
		BgAsciiDrawStr(0, 1, str);

		_Sprintf(str, "DELAY :%d", p->delay);
		BgAsciiDrawStr(0, 2, str);

		_Sprintf(str, "FPS   :%d", p->fps);
		BgAsciiDrawStr(0, 3, str);
	}
}
