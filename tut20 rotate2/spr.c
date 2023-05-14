#include "spr.h"
#include "math.h"
#include "res.h"

//---------------------------------------------------------------------------
EWRAM_CODE void SprInit(void)
{
	REG_DISPCNT = (OBJ_ENABLE | OBJ_1D_MAP);

	u32 i;

	for(i=0; i<128; i++)
	{
		SprSetXy(i, 240, 160);
	}

	u16* oam = OBJ_BASE_ADR;
	u16* pal = OBJ_COLORS;

	for(i=0; i<metr0TilesLen/2; i++)
	{
		oam[i] = metr0Tiles[i];
	}

	for(i=0; i<metr0PalLen/2; i++)
	{
		pal[i] = metr0Pal[i];
	}
}
//---------------------------------------------------------------------------
EWRAM_CODE void SprSetSize(u32 num, u32 size, u32 form, u32 col)
{
	OBJATTR* sp = (OBJATTR*)OAM + num;

	sp->attr0 &= 0x1fff;
	sp->attr1 &= 0x3fff;
	sp->attr0 |= col | form;
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
EWRAM_CODE void SprSetScaleRot(u32 num, s16 pa, s16 pb, s16 pc, s16 pd)
{
	OBJAFFINE* rot = (OBJAFFINE*)OAM + num;

	rot->pa = pa;
	rot->pb = pb;
	rot->pc = pc;
	rot->pd = pd;
}
//---------------------------------------------------------------------------
EWRAM_CODE void SprSetPal(u32 num, u32 pal)
{
	OBJATTR* sp = (OBJATTR*)OAM + num;

	sp->attr2 &= 0x0fff;
	sp->attr2 |= (pal << 12);
}
//---------------------------------------------------------------------------
EWRAM_CODE void SprSetRotScale(u32 num, u32 no, u32 isFlag)
{
	OBJATTR* sp = (OBJATTR*)OAM + num;

	sp->attr0 &= 0xfeff;
	sp->attr1 &= 0xC1ff;

	if(isFlag == FALSE)
	{
		return;
	}

	sp->attr0 |= OBJ_ROT_SCALE_ON;
	sp->attr1 |= OBJ_ROT_SCALE(no);
}
//---------------------------------------------------------------------------
EWRAM_CODE void SprSetDubleFlag(u32 num, u32 no, u32 isFlag)
{
	OBJATTR* sp = (OBJATTR*)OAM + num;

	sp->attr0 &= 0xfdff;

	if(isFlag == FALSE)
	{
		return;
	}

	sp->attr0 |= OBJ_DOUBLE;
}
//---------------------------------------------------------------------------
EWRAM_CODE void SprSetRotate(u32 num, s32 angle)
{
	OBJAFFINE* rot = (OBJAFFINE*)OAM + num;

	rot->pa =  MathCos(angle);
	rot->pb =  MathSin(angle);
	rot->pc = -MathSin(angle);
	rot->pd =  MathCos(angle);
}
