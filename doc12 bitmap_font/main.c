#include "lib/gba.h"
#include "res.h"

//---------------------------------------------------------------------------
typedef struct {
	u8*  pDat;
	s32  imgCx;
	s32  cx;
	s32  cy;
} ST_FONT;

//---------------------------------------------------------------------------
void WaitForVsync()
{
	while(*(volatile u16*)0x4000006 >= 160) {};
	while(*(volatile u16*)0x4000006 <  160) {};
}
//---------------------------------------------------------------------------
void Mode3DrawFontChr(ST_FONT* p, s32 sx, s32 sy, u16 chr, u16 col)
{
	// �������ދN�_�ʒu�����߂܂�
	u16* pScreen = (u16*)VRAM + (sy * 240) + sx;

	// �������ރt�H���g�f�[�^�̈ʒu�����߂܂�
	u8*  pDat = p->pDat + (chr - 0x20) * p->cx;

	s32 x, y;
	for(y=0; y<p->cy; y++)
	{
		for(x=0; x<p->cx; x++)
		{
			if(pDat[y*p->imgCx + x] == 0x00)
			{
				continue;
			}

			pScreen[y*240 + x] = col;
		}
	}
}
//---------------------------------------------------------------------------
void Mode3DrawFontStr(ST_FONT* p, s32 sx, s32 sy, char* str, u16 col)
{
	u16 chr;
	s32 i=0, x=0, y=0;

	for(;;)
	{
		chr = str[i++];

		if(chr == '\0') return;
		if(chr ==   CR) return;
		if(chr ==   LF) return;

		// ���s����
		if(sx + x >= 240)
		{
			x  = 0;
			y += p->cy;

			if(sy + y + p->cy >= 160)
			{
				return;
			}
		}

		Mode3DrawFontChr(p, sx + x, sy + y, chr, col);
		x += p->cx;
	}
}
//---------------------------------------------------------------------------
int main(void)
{
	SetMode(MODE_3 | BG2_ENABLE);

	ST_FONT f;

	f.pDat  = (u8*) &k6x10Bitmap;		// �f�[�^�̃|�C���^
	f.imgCx = 960;						// �f�[�^�̉��T�C�Y
	f.cx    = 6;						// 1�����̉��T�C�Y
	f.cy    = 10;						// 1�����̏c�T�C�Y

	Mode3DrawFontChr(&f,  0,  0, '!', RGB5(31,31,31));

	Mode3DrawFontStr(&f, 16, 16, "ABCDEF #$%&", RGB5(31,31,31));
	Mode3DrawFontStr(&f, 16, 32, "123456 +-*/", RGB5(31,31, 0));

	for(;;)
	{
	    WaitForVsync();
	}
}
