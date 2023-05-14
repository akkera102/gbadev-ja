#include "lib/gba.h"
#include "res.h"

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
	u32 i;
	for(i=0; i<128; i++)
	{
		SpriteMove(i, 240, 160);
	}
}
//---------------------------------------------------------------------------
int main(void)
{
	SetMode(MODE_0 | OBJ_ENABLE | OBJ_1D_MAP);

	u16* oam = OBJ_BASE_ADR;	// �L�����N�^�f�[�^
	u16* pal = OBJ_COLORS;		// �p���b�g�f�[�^
	u32 i;


	// �L�����N�^�̊i�[
	for(i=0; i<sprTilesLen/2; i++)
	{
		oam[i] = sprTiles[i];
	}

	// �p���b�g�̊i�[
	for(i=0; i<16; i++)
	{
		pal[i]    = sprPal[i];
		pal[i+16] = sprPal[i];
		pal[i+32] = sprPal[i];
	}

	// �ꕔ�̐F�����������܂�
	pal[16*1 + 2] = RGB5(0,31,0);
	pal[16*2 + 2] = RGB5(0,0,31);

	SpriteInit();

	// �X�v���C�g0�i�p���b�g0�j
	SpriteSetSize (0, OBJ_SIZE(Sprite_16x16), OBJ_SQUARE, OBJ_16_COLOR);
	SpriteSetChr  (0, 0);
	SpriteMove    (0, 20, 20);

	// �X�v���C�g1�i�p���b�g1�j
	SpriteSetSize (1, OBJ_SIZE(Sprite_16x16), OBJ_SQUARE, OBJ_16_COLOR);
	SpriteSetChr  (1, 0);
	SpriteMove    (1, 40, 20);
	SpriteSetPalNo(1, 1);

	// �X�v���C�g2�i�p���b�g2�j
	SpriteSetSize (2, OBJ_SIZE(Sprite_16x16), OBJ_SQUARE, OBJ_16_COLOR);
	SpriteSetChr  (2, 0);
	SpriteMove    (2, 60, 20);
	SpriteSetPalNo(2, 2);

	for(;;)
	{
		WaitForVsync();
	}
}
