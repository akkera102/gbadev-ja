#include "bullet.arm.h"
#include "rnd.arm.h"

//---------------------------------------------------------------------------
ST_BULLET Bullet;


//---------------------------------------------------------------------------
EWRAM_CODE void BulletInit(void)
{
	_Memset(&Bullet, 0x00, sizeof(ST_BULLET));
}
//---------------------------------------------------------------------------
IWRAM_CODE void BulletExec(void)
{
	_Memset(&Bullet.idxCnt, 0x00, sizeof(Bullet.idxCnt));

	s32 i;

	for(i=0; i<BULLET_MAX_CHR_CNT; i++)
	{
		if(Bullet.chr[i].is == FALSE)
		{
			continue;
		}

		Bullet.chr[i].x += Bullet.chr[i].mx;
		Bullet.chr[i].y += Bullet.chr[i].my;

		s32 xx = FIX2INT(Bullet.chr[i].x);
		s32 yy = FIX2INT(Bullet.chr[i].y);

		if(xx <= -8 || xx >= 240 || yy <= -8 || yy >= 160)
		{
			Bullet.chr[i].is = FALSE;
			Bullet.maxCnt--;

			continue;
		}

		s32 idx = (yy + 8) / 4;
		Bullet.idxCnt[idx]++;
	}
}
//---------------------------------------------------------------------------
IWRAM_CODE void BulletReg(s32 x, s32 y)
{
	s32 i;

	for(i=0; i<BULLET_MAX_CHR_CNT; i++)
	{
		if(Bullet.chr[i].is == TRUE)
		{
			continue;
		}

		Bullet.chr[i].is = TRUE;
		Bullet.chr[i].x  = INT2FIX(x - (8/2));
		Bullet.chr[i].y  = INT2FIX(y - (8/2));
		Bullet.chr[i].mx = BulletRnd();
		Bullet.chr[i].my = BulletRnd();
		Bullet.maxCnt++;

		return;
	}
}
//---------------------------------------------------------------------------
IWRAM_CODE s16 BulletRnd(void)
{
	s16 r = (s16)RndU32();

	// Å’áŒÀ‚ÌˆÚ“®—Ê‚ð’²®
	if(r < 0)
	{
		r -= 256;
	}
	else
	{
		r += 256;
	}

	return FIX2INT(r);
}
//---------------------------------------------------------------------------
IWRAM_CODE s16 BulletGetMaxCnt(void)
{
	return Bullet.maxCnt;
}
//---------------------------------------------------------------------------
IWRAM_CODE s16 BulletGetIdxCnt(s32 i)
{
	return Bullet.idxCnt[i];
}
