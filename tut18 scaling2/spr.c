#include "spr.h"
#include "res.h"

//---------------------------------------------------------------------------
EWRAM_CODE void SprInit(void)
{
	u32 i;

	for(i=0; i<128; i++)
	{
		SprSetXy(i, 240, 160);
	}

	// mode3
	u16* oam = BITMAP_OBJ_BASE_ADR;
	u16* pal = OBJ_COLORS;

	for(i=0; i<spr_slimeTilesLen/2; i++)
	{
		oam[i] = spr_slimeTiles[i];
	}

	for(i=0; i<spr_slimePalLen/2; i++)
	{
		pal[i] = spr_slimePal[i];
	}
}
//---------------------------------------------------------------------------
EWRAM_CODE void SprSetSize(u32 num, u32 size, u32 form, u32 col)
{
	OBJATTR* sp = (OBJATTR*)OAM + num;

	sp->attr0 &= 0x1fff;
	sp->attr1 &= 0x3fff;
	sp->attr0 |= col  | form;
	sp->attr1 |= size;
}
//---------------------------------------------------------------------------
EWRAM_CODE void SprSetXy(u32 num, s32 x, s32 y)
{
	OBJATTR* sp = (OBJATTR*)OAM + num;

	if(x<0) x += 512;
	if(y<0) y += 256;

	sp->attr1 &= 0xfe00;
	sp->attr0 &= 0xff00;
	sp->attr1 |= (x & 0x01ff);
	sp->attr0 |= (y & 0x00ff);
}
//---------------------------------------------------------------------------
EWRAM_CODE void SprSetChr(u32 num, u32 ch)
{
	OBJATTR* sp = (OBJATTR*)OAM + num;

	sp->attr2 &= 0xfc00;
	sp->attr2 |= ch;
}
//---------------------------------------------------------------------------
EWRAM_CODE void SprSetScale(u32 num, u32 xsc, u32 ysc)
{
	OBJAFFINE* rot = (OBJAFFINE*)OAM + num;

	rot->pa = Div(256 * 100, xsc);
	rot->pb = 0;
	rot->pc = 0;
	rot->pd = Div(256 * 100, ysc);
}
//---------------------------------------------------------------------------
EWRAM_CODE void SprSetPalNo(u32 num, u32 palNo)
{
	OBJATTR* sp = (OBJATTR*)OAM + num;

	sp->attr2 &= 0x0fff;
	sp->attr2 |= (palNo << 12);
}
//---------------------------------------------------------------------------
/*
	SprSetRotateFlag
	�X�v���C�g�̊g��k����]�@�\�Ɋւ���ݒ�
	no �@�@�@�@�@�E�E�E�@�g�p����X�v���C�gRotate�p�����[�^�̔ԍ�
	double_flag�@�E�E�E�@�`��̈���Q�{�g�p�ł���悤�ɂ��邩
	                     0�Ȃ�ʏ�̕`��̈�ASP_SIZE_DOUBLE�Ȃ�Q�{
*/
EWRAM_CODE void SprSetRotateFlag(u32 num, u32 no, u32 double_flag)
{
	OBJATTR* sp = (OBJATTR*)OAM + num;

	sp->attr0 |= OBJ_ROT_SCALE_ON;

	sp->attr1 &= 0xC1ff;
	sp->attr1 |= OBJ_ROT_SCALE(no);
	sp->attr0 &= 0xfdff;
	sp->attr0 |= double_flag;
}
