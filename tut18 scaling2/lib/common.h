#ifndef __COMMON_H__
#define __COMMON_H__
#ifdef __cplusplus
extern "C" {
#endif

#include "gba.h"


//---------------------------------------------------------------------------
typedef char* va_list;

#define _Max(a,b)				(((a)>(b))?(a):(b))
#define _Min(a,b)				(((a)>(b))?(b):(a))
#define _Toupper(c)				((c >= 'a' && c <= 'z') ? c - ('a' - 'A') : c)
#define _IsAlpha(c)				((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') ? true : false)
#define _IsDigit(c)				((c >= '0') && (c <= '9') ? true : false)
#define _IsXDigit(c)			((_IsDigit(c) == true) || (c >= 'a' && c <= 'f') ? true : false)
#define _IsSpace(c)				((c == ' ') ? true : false)
#define _IsSJIS(c)				(((c)>=0x81 && (c)<=0x9f) || ((c)>=0xe0 && (c)<=0xef))

#define __vasz(x)				((sizeof(x)+sizeof(int)-1) & ~(sizeof(int) -1))
#define va_start(ap, n)			((ap) = (va_list)&n + __vasz(n))
#define va_arg(ap, type)		(*((type *)((va_list)((ap) = (void *)((va_list)(ap) + __vasz(type))) - __vasz(type))))
#define va_end(ap)				

#define CR						0x0d
#define LF						0x0a

#define COMMON_SPRINT_BUF_CNT	0x200

//---------------------------------------------------------------------------
s32   _Strlen(char* s1);
char* _Strncpy(char* ret, char* s2, s32 size);
s32   _Strncmp(char* s1, char* s2, s32 size);
char* _Strcat(char* ret, char* s2);
char* _Strchr(char* str, char chr);
s32   _Atoi(char* s);

char* _Memcpy(void* s1, void* s2, s32 size);
s32   _Memcmp(void* s1, void* s2, s32 size);
char* _Memset(void* s, u8 c, s32 size);

void  _Printf(char* format, ...);
char* _Sprintf(char* buf, char* format, ...);
void  _DoSprintf(char* str, char* fmt, char* ap);
char* _SprintfNum(s32 val, s32 base, char* s);
char* _SprintfNumCol(s32 val, s32 base, char* s, s32 col, char colChr, bool isTop);
char* _SprintfHex(u32 val, char* s, char hex);
char* _SprintfHexCol(u32 val, char* s, s32 col, char colChr, bool isTop, char hex);
char* _SprintfString(char* val, char* s);

void  MgbaLog(char* buf);
void  MappyLog(char* buf);
void  SystemError(char* format, ...);

#ifdef __cplusplus
}
#endif
#endif

