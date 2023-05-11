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


		if(FIX2INT(Bullet.chr[i].x) <= -8 || FIX2INT(Bullet.chr[i].x) >= 240)
		{
			Bullet.chr[i].is = FALSE;
			Bullet.maxCnt--;

			continue;
		}

		if(FIX2INT(Bullet.chr[i].y) <= -8 || FIX2INT(Bullet.chr[i].y) >= 160)
		{
			Bullet.chr[i].is = FALSE;
			Bullet.maxCnt--;

			continue;
		}

		s32 idx = (FIX2INT(Bullet.chr[i].y) + 8) / 8;
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
Re:
	s16 r = (s16)RndU32();

	if(r >= 0 && r <  128)
	{
		goto Re;
	}

	if(r <= 0 && r > -128)
	{
		goto Re;
	}

	return FIX2INT(r);
}
//---------------------------------------------------------------------------
IWRAM_CODE void BulletSeekInit(void)
{
	Bullet.seek = 0;

	if(Bullet.chr[Bullet.seek].is == TRUE)
	{
		return;
	}

	BulletSeekNext();
}
//---------------------------------------------------------------------------
IWRAM_CODE void BulletSeekNext(void)
{
	Bullet.seek++;

	while(Bullet.chr[Bullet.seek].is == FALSE)
	{
		Bullet.seek++;
	}
}
//---------------------------------------------------------------------------
IWRAM_CODE s16 BulletSeekX(void)
{
	return FIX2INT(Bullet.chr[Bullet.seek].x);
}
//---------------------------------------------------------------------------
IWRAM_CODE s16 BulletSeekY(void)
{
	return FIX2INT(Bullet.chr[Bullet.seek].y);
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
