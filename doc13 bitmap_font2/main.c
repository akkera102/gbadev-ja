#include "lib/gba.h"
#include "res.h"

//---------------------------------------------------------------------------
typedef struct {
	u8*  pDat;
	u32  imgCx;
	u16  cx;
	u16  cy;

	u16* pSheet;
	u16  cnt;
} ST_FONT;

//---------------------------------------------------------------------------
void WaitForVsync(void)
{
	while (*(volatile u16*)0x4000006 >= 160) {};
	while (*(volatile u16*)0x4000006 <  160) {};
}
//---------------------------------------------------------------------------
void Mode3DrawSJISChr(ST_FONT* p, s32 sx, s32 sy, u16 chr, u16 col)
{
	u8* pDat = p->pDat;
	s32 i;

	for(i=0; i<p->cnt; i++)
	{
		if(chr == p->pSheet[i])
		{
			pDat += i * p->cx;
			break;
		}
	}

	u16* pScreen = (u16*)VRAM + (sy * 240) + sx;
	s32  x, y;

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
void Mode3DrawSJISStr(ST_FONT* p, s32 sx, s32 sy, char* str, u16 col)
{
	u16 chr;
	s32 i=0, x=0, y=0;

	for(;;)
	{
		chr = str[i] | (str[i+1] << 8);
		i += 2;

		if(chr == '\0')
		{
			return;
		}

		// 改行処理
		if(sx + x >= 240)
		{
			x  = 0;
			y += p->cy;

			if(sy + y + p->cy >= 160)
			{
				return;
			}
		}

		Mode3DrawSJISChr(p, sx + x, sy + y, chr, col);
		x += p->cx;
	}
}
//---------------------------------------------------------------------------
int main(void)
{
	SetMode(MODE_3 | BG2_ENABLE);

	ST_FONT f;

	f.pDat   = (u8*)&mplus_j10rBitmap;
	f.imgCx  = 69630 + 2;				// +2は、gritのサイズ調整分
	f.cx     = 10;
	f.cy     = 11;

	f.pSheet = (u16*)&mplus_jfnt_txt;
	f.cnt    = 6963;

	Mode3DrawSJISStr(&f, 0, 0, "猫まんま", RGB5(31,31,31));

	char* p = "吾輩は猫である。名前はまだ無い。　どこで生れたかとんと見当がつかぬ。何でも薄暗いじめじめした所でニャーニャー泣いていた事だけは記憶している。吾輩はここで始めて人間というものを見た。しかもあとで聞くとそれは書生という人間中で一番獰悪な種族であったそうだ。この書生というのは時々我々を捕えて煮て食うという話である。しかしその当時は何という考もなかったから別段恐しいとも思わなかった。ただ彼の掌に載せられてスーと持ち上げられた時何だかフワフワした感じがあったばかりである。掌の上で少し落ちついて書生の顔を見たのがいわゆる人間というものの見始であろう。この時妙なものだと思った感じが今でも残っている。第一毛をもって装飾されべきはずの顔がつるつるしてまるで薬缶だ。その後猫にもだいぶ逢ったがこんな片輪には一度も出会わした事がない。のみならず顔の真中があまりに突起している。そうしてその穴の中から時々ぷうぷうと煙を吹く。どうも咽せぽくて実に弱った。これが人間の飲む煙草というものである事はようやくこの頃知った。";

	Mode3DrawSJISStr(&f, 0, 11, p, RGB5(31,31,31));

	for(;;)
	{
	    WaitForVsync();
	}
}
