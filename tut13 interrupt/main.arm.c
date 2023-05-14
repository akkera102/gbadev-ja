#include "lib/gba.h"
#include "res.h"

vs32 frame;

//---------------------------------------------------------------------------
void WaitForVsync(void)
{
	while(*(vu16*)0x4000006 >= 160) {};
	while(*(vu16*)0x4000006 <  160) {};
}
//---------------------------------------------------------------------------
void SpriteSetPalNo(u32 num, u32 palNo)
{
	OBJATTR* sp = (OBJATTR*)OAM + num;

	sp->attr2 &= 0x0fff;
	sp->attr2 |= (palNo << 12);
}
//---------------------------------------------------------------------------
void SpriteMove(u32 num, s32 x, s32 y)
{
	OBJATTR* sp = (OBJATTR*)OAM + num;

	sp->attr1 &= 0xfe00;
	sp->attr0 &= 0xff00;
	sp->attr1 |= (x & 0x01ff);
	sp->attr0 |= (y & 0x00ff);
}
//---------------------------------------------------------------------------
void SpriteSetSize(u32 num, u32 size, u32 form, u32 col)
{
	OBJATTR* sp = (OBJATTR*)OAM + num;

	sp->attr0 &= 0x1fff;
	sp->attr1 &= 0x3fff;
	sp->attr0 |= col | form;
	sp->attr1 |= size;
}
//---------------------------------------------------------------------------
void SpriteSetChr(u32 num, u32 ch)
{
	OBJATTR* sp = (OBJATTR*)OAM + num;

	sp->attr2 &= 0xfc00;
	sp->attr2 |= ch;
}
//---------------------------------------------------------------------------
void SpriteInit(void)
{
	vs32 i;

	for(i=0; i<128; i++)
	{
		SpriteMove(i, 240, 160);
	}
}
//---------------------------------------------------------------------------
void SpriteShowNumber(u32 base, s32 num)
{
	vs32 i;

	for(i=5-1; i>=0; i--)
	{
		SpriteSetChr(base + i, num % 10);
		num /= 10;
	}
}
//---------------------------------------------------------------------------
void SpriteSetDatChr(u16* dat, u32 size)
{
	u16* p = OBJ_BASE_ADR;
	vu32 i;

	for(i=0; i<size/2; i++)
	{
		p[i] = dat[i];
	}
}
//---------------------------------------------------------------------------
void SpriteSetDatPal(u16* pal)
{
	u16* p = OBJ_COLORS;
	vs32 i;

	for(i=0; i<16; i++)
	{
		p[i] = pal[i];
	}
}
//---------------------------------------------------------------------------
void IrqHandler(void)
{
	REG_IME  = 0;
	u16 flag = REG_IF;

	if(flag & IRQ_VBLANK)
	{
		frame++;
	}

	REG_IF  = flag;
	REG_IME = 1;
}
//---------------------------------------------------------------------------
void IrqInit(void)
{
	REG_IME = 0;

	INT_VECTOR   = (u32)IrqHandler;
	REG_DISPSTAT = LCDC_VBL;
	REG_IE       = IRQ_VBLANK;

	REG_IME = 1;
}
//---------------------------------------------------------------------------
int main(void)
{
	SetMode(MODE_0 | OBJ_ENABLE | OBJ_1D_MAP);

	SpriteInit();
	SpriteSetDatChr((u16*)&sprTiles, sprTilesLen);
	SpriteSetDatPal((u16*)&sprPal);

	u32 i;

	for(i=0; i<5; i++)
	{
		SpriteSetSize (i, OBJ_SIZE(Sprite_8x8), OBJ_SQUARE, OBJ_16_COLOR);
		SpriteSetChr  (i, 0);
		SpriteMove    (i, 20+i*8, 20);
		SpriteSetPalNo(i, 0);
	}

	frame = 0;
	IrqInit();

	for(;;)
	{
		WaitForVsync();

		SpriteShowNumber(0, frame);
	}
}
