#include "rtc.h"
#include "bg.h"
#include "key.h"
#include "res.h"

//---------------------------------------------------------------------------
ST_RTC Rtc;
const char week[7][4] = {"sun", "mon", "tue", "wed", "thu", "fri", "sat"};


//---------------------------------------------------------------------------
void RtcInit(void)
{
	_Memset(&Rtc, 0x00, sizeof(ST_RTC));

	// ステータスレジスタの24時間表示フラグをチェックします
	// Bit6 0:12時間、1:24時間

	REG_RTC_ENABLE = 0x1;

	RtcOutCmd(0x63);
	Rtc.isEnable = (RtcIn() & 0x40) ? true : false;
}
//---------------------------------------------------------------------------
void RtcExec(void)
{
	if(Rtc.isEnable == false)
	{
		BgDrawPrintf(0, 0, "RTC NOT FOUND");
		return;
	}

	if(KeyGetTrg() & KEY_R)
	{
		RtcSetTime();
		BgDrawPrintf(0, 3, "15/12/31 wed 12:34:56 write");
	}

	RtcGetTime();
	BgDrawPrintf(0, 0, "RTC TEST");
	BgDrawPrintf(0, 2, "                              ");
	BgDrawPrintf(0, 2, "%02x/%02x/%02x %s %02x:%02x:%02x", Rtc.reg[0], Rtc.reg[1], Rtc.reg[2], week[Rtc.reg[3]], Rtc.reg[4] & 0x7f, Rtc.reg[5], Rtc.reg[6]);
}
//---------------------------------------------------------------------------
void RtcGetTime(void)
{
	RtcOutCmd(0x65);

	s32 i;

	for(i=0; i<RTC_MAX_REG_CNT; i++)
	{
		Rtc.reg[i] = RtcIn();
	}
}
//---------------------------------------------------------------------------
void RtcSetTime(void)
{
	RtcOutCmd(0x64);

	// TODO 入力操作、入力チェック
	// TODO ソースコードに直書き 2015/12/31 wed 12:34:56

	s32 i;
	u8  r[RTC_MAX_REG_CNT];

	r[0] = 0x15;
	r[1] = 0x12;
	r[2] = 0x31;
	r[3] = 0x3;
	r[4] = 0x12;
	r[5] = 0x34;
	r[6] = 0x56;

	for(i=0; i<RTC_MAX_REG_CNT; i++)
	{
		RtcOutReg(r[i]);
	}
}
//---------------------------------------------------------------------------
u32 RtcIn(void)
{
	REG_RTC_RW = 0x5;

	s32 i;
	u32 ret = 0;

	for(i=0; i<8; i++)
	{
		REG_RTC_DATA = 0x4;
		REG_RTC_DATA = 0x5;

		ret |= ((REG_RTC_DATA & 0x2) >> 1) << i;
	}

	return ret;
}
//---------------------------------------------------------------------------
void RtcOutCmd(u32 cmd)
{
	REG_RTC_RW   = 0x7;
	REG_RTC_DATA = 0x1;
	REG_RTC_DATA = 0x5;

	s32 i;
	cmd <<= 1;

	for(i=7; i>=0; i--)
	{
		REG_RTC_DATA = ((cmd >> i) & 0x2) | 0x4;
		REG_RTC_DATA = ((cmd >> i) & 0x2) | 0x5;
	}
}
//---------------------------------------------------------------------------
void RtcOutReg(u32 reg)
{
	REG_RTC_RW = 0x7;

	s32 i;
	reg <<= 1;

	for(i=0; i<8; i++)
	{
		REG_RTC_DATA = ((reg >> i) & 0x2) | 0x4;
		REG_RTC_DATA = ((reg >> i) & 0x2) | 0x5;
	}
}
