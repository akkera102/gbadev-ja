#include "lib/gba.h"
#include "res.h"

//---------------------------------------------------------------------------
void WaitForVsync(void)
{
	while(*(vu16*)0x4000006 >= 160) {};
	while(*(vu16*)0x4000006 <  160) {};
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
	u32 i;
	for(i=0; i<128; i++)
	{
		SpriteMove(i, 240, 160);
	}
}
//---------------------------------------------------------------------------
int main(void)
{
	SetMode(MODE_0 | OBJ_ENABLE | OBJ_2D_MAP);

	u16* oam = OBJ_BASE_ADR;	// キャラクタデータ
	u16* pal = OBJ_COLORS;		// パレットデータ
	u32 i;

	for(i=0; i<spr1TilesLen/2; i++)
	{
		oam[i] = spr1Tiles[i];
	}

	for(i=0; i<16; i++)
	{
		pal[i] = spr1Pal[i];
	}

	SpriteInit();

	s16 x = 0;
	s16 y = 0;
	u16 s = 0;

	SpriteSetSize(0, OBJ_SIZE(s), OBJ_SQUARE, OBJ_16_COLOR);
	SpriteSetChr (0, 1);
	SpriteMove   (0, x, y);

	for(;;)
	{
		WaitForVsync();

		SpriteMove(0, x, y);

		u16 key = ~(REG_KEYINPUT);

		if(key & KEY_UP)    y--;
		if(key & KEY_DOWN)  y++;
		if(key & KEY_RIGHT) x++;
		if(key & KEY_LEFT)  x--;

		// フレーム単位で形状を変更
		SpriteSetSize(0, OBJ_SIZE(s>>4), OBJ_SQUARE, OBJ_16_COLOR);
		s++;

		if((s>>4) > 3)
		{
			s=0;
		}
	}
}
