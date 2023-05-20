/*
	$Id: gba.h,v 1.1 2005/12/14 14:22:18 wntrmute Exp $

	Header file for libgba bios affine functions

	Copyright 2003-2005 by Dave Murphy.

	This library is free software; you can redistribute it and/or
	modify it under the terms of the GNU Library General Public
	License as published by the Free Software Foundation; either
	version 2 of the License, or (at your option) any later version.

	This library is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
	Library General Public License for more details.

	You should have received a copy of the GNU Library General Public
	License along with this library; if not, write to the Free Software
	Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307
	USA.

	Please report all bugs and problems through the bug tracker at
	"http://sourceforge.net/tracker/?group_id=114505&atid=668551".

	$Log: gba.h,v $
	Revision 1.1  2005/12/14 14:22:18  wntrmute
	added global gba header
	

*/
//---------------------------------------------------------------------------------
#ifndef	_gba_h_
#define	_gba_h_
//---------------------------------------------------------------------------------

#define _DEBUG					1


// gba_types.h
typedef	unsigned char			u8;		/**< Unsigned 8 bit value	*/
typedef	unsigned short int		u16;	/**< Unsigned 16 bit value	*/
typedef	unsigned int			u32;	/**< Unsigned 32 bit value	*/
typedef	signed char				s8;		/**< Signed 8 bit value	*/
typedef	signed short int		s16;	/**< Signed 16 bit value	*/
typedef	signed int				s32;	/**< Signed 32 bit value	*/
typedef	volatile u8				vu8;	/**< volatile Unsigned 8 bit value	*/
typedef	volatile u16			vu16;	/**< volatile Unigned 16 bit value	*/
typedef	volatile u32			vu32;	/**< volatile Unsigned 32 bit value	*/
typedef	volatile s8				vs8;	/**< volatile Signed 8 bit value	*/
typedef	volatile s16			vs16;	/**< volatile Signed 8 bit value	*/
typedef	volatile s32			vs32;	/**< volatile Signed 8 bit value	*/


// gba_base.h
#define	VRAM		0x06000000
#define	IWRAM		0x03000000
#define	EWRAM		0x02000000
#define	EWRAM_END	0x02040000
#define	SRAM		0x0E000000
#define	REG_BASE	0x04000000
#ifndef	NULL
#define	NULL	0
#endif
#if	defined	( __thumb__ )
#define	SystemCall(Number)	 __asm ("SWI	  "#Number"\n" :::  "r0", "r1", "r2", "r3")
#else
#define	SystemCall(Number)	 __asm ("SWI	  "#Number"	<< 16\n" :::"r0", "r1", "r2", "r3")
#endif
#define BIT(number) (1<<(number))
#define IWRAM_CODE	__attribute__((section(".iwram"), long_call))
#define EWRAM_CODE	__attribute__((section(".ewram"), long_call))
#define IWRAM_DATA	__attribute__((section(".iwram")))
#define EWRAM_DATA	__attribute__((section(".ewram")))
#define EWRAM_BSS	__attribute__((section(".sbss")))
#define ALIGN(m)	__attribute__((aligned (m)))


// gba_dma.h
#define REG_DMA0SAD	*(vu32*)(REG_BASE + 0x0b0)
#define REG_DMA0DAD	*(vu32*)(REG_BASE + 0x0b4)
#define REG_DMA0CNT	*(vu32*)(REG_BASE + 0x0b8)
#define REG_DMA1SAD	*(vu32*)(REG_BASE + 0x0bc)
#define REG_DMA1DAD	*(vu32*)(REG_BASE + 0x0c0)
#define REG_DMA1CNT	*(vu32*)(REG_BASE + 0x0c4)
#define REG_DMA2SAD	*(vu32*)(REG_BASE + 0x0c8)
#define REG_DMA2DAD	*(vu32*)(REG_BASE + 0x0cc)
#define REG_DMA2CNT	*(vu32*)(REG_BASE + 0x0d0)
#define REG_DMA3SAD	*(vu32*)(REG_BASE + 0x0d4)
#define REG_DMA3DAD	*(vu32*)(REG_BASE + 0x0d8)
#define REG_DMA3CNT	*(vu32*)(REG_BASE + 0x0dc)
#define DMA_DST_INC		(0<<21)
#define DMA_DST_DEC		(1<<21)
#define DMA_DST_FIXED	(2<<21)
#define DMA_DST_RELOAD	(3<<21)
#define DMA_SRC_INC		(0<<23)
#define DMA_SRC_DEC		(1<<23)
#define DMA_SRC_FIXED	(2<<23)
#define DMA_REPEAT		(1<<25)
#define DMA16			(0<<26)
#define DMA32			(1<<26)
#define	GAMEPAK_DRQ		(1<<27)
#define DMA_IMMEDIATE	(0<<28)
#define DMA_VBLANK		(1<<28)
#define DMA_HBLANK		(2<<28)
#define DMA_SPECIAL		(3<<28)
#define DMA_IRQ			(1<<30)
#define DMA_ENABLE		(1<<31)
#define DMA_Copy(channel, source, dest, mode) {\
	REG_DMA##channel##SAD = (u32)(source);\
	REG_DMA##channel##DAD = (u32)(dest);\
	REG_DMA##channel##CNT = DMA_ENABLE | (mode); \
}

static inline void dmaCopy(const void * source, void * dest, u32 size) {
	DMA_Copy(3, source, dest, DMA16 | size>>1);
}

#define	DMA0COPY( source, dest, mode) DMA_Copy(0,(source),(dest),(mode))
#define	DMA1COPY( source, dest, mode) DMA_Copy(1,(source),(dest),(mode))
#define	DMA2COPY( source, dest, mode) DMA_Copy(2,(source),(dest),(mode))
#define	DMA3COPY( source, dest, mode) DMA_Copy(3,(source),(dest),(mode))


// gba_input.h
#define REG_KEYINPUT	*(vu16*)(REG_BASE + 0x130)  // Key Input
#define REG_KEYCNT		*(vu16*)(REG_BASE + 0x132)  // Key Control
typedef enum KEYPAD_BITS {
	KEY_A		=	(1<<0),	/*!< keypad A button */
	KEY_B		=	(1<<1),	/*!< keypad B button */
	KEY_SELECT	=	(1<<2),	/*!< keypad SELECT button */
	KEY_START	=	(1<<3),	/*!< keypad START button */
	KEY_RIGHT	=	(1<<4),	/*!< dpad RIGHT */
	KEY_LEFT	=	(1<<5),	/*!< dpad LEFT */
	KEY_UP		=	(1<<6),	/*!< dpad UP */
	KEY_DOWN	=	(1<<7),	/*!< dpad DOWN */
	KEY_R		=	(1<<8),	/*!< Right shoulder button */
	KEY_L		=	(1<<9),	/*!< Left shoulder button */

	KEYIRQ_ENABLE	=	(1<<14),	/*!< Enable keypad interrupt */
	KEYIRQ_OR		=	(0<<15),	/*!< interrupt logical OR mode */
	KEYIRQ_AND		=	(1<<15),	/*!< interrupt logical AND mode */
	DPAD 		=	(KEY_UP | KEY_DOWN | KEY_LEFT | KEY_RIGHT) /*!< mask all dpad buttons */
} KEYPAD_BITS;


// gba_interrupt.h
#define MAX_INTS	15
#define INT_VECTOR	*(vu32 *)(0x03007ffc)
#define	REG_IME		*(vu16 *)(REG_BASE + 0x208)	// Interrupt Master Enable
#define	REG_IE		*(vu16 *)(REG_BASE + 0x200)	// Interrupt Enable
#define	REG_IF		*(vu16 *)(REG_BASE + 0x202)	// Interrupt Request

typedef enum irqMASKS {
	IRQ_VBLANK	=	(1<<0),		/*!< vertical blank interrupt mask */
	IRQ_HBLANK	=	(1<<1),		/*!< horizontal blank interrupt mask */
	IRQ_VCOUNT	=	(1<<2),		/*!< vcount match interrupt mask */
	IRQ_TIMER0	=	(1<<3),		/*!< timer 0 interrupt mask */
	IRQ_TIMER1	=	(1<<4),		/*!< timer 1 interrupt mask */
	IRQ_TIMER2	=	(1<<5),		/*!< timer 2 interrupt mask */
	IRQ_TIMER3	=	(1<<6),		/*!< timer 3 interrupt mask */
	IRQ_SERIAL	=	(1<<7),		/*!< serial interrupt mask */
	IRQ_DMA0	=	(1<<8),		/*!< DMA 0 interrupt mask */
	IRQ_DMA1	=	(1<<9),		/*!< DMA 1 interrupt mask */
	IRQ_DMA2	=	(1<<10),	/*!< DMA 2 interrupt mask */
	IRQ_DMA3	=	(1<<11),	/*!< DMA 3 interrupt mask */
	IRQ_KEYPAD	=	(1<<12),	/*!< Keypad interrupt mask */
	IRQ_GAMEPAK	=	(1<<13)		/*!< horizontal blank interrupt mask */
} irqMASK;


// gba_sprites.h
typedef struct {
	u16 attr0;
	u16 attr1;
	u16 attr2;
	u16 dummy;
} OBJATTR;

typedef struct {
	u16 attribute[3];
	u16 dummy;
} SpriteEntry;

typedef struct {
	u16 dummy0[3];
	s16 pa;
	u16 dummy1[3];
	s16 pb;
	u16 dummy2[3];
	s16 pc;
	u16 dummy3[3];
	s16 pd;
} OBJAFFINE;

#define	OAM					((OBJATTR *)0x07000000)
#define OBJ_BASE_ADR		((void *)(VRAM + 0x10000))
#define SPRITE_GFX			((u16 *)(VRAM + 0x10000))
#define BITMAP_OBJ_BASE_ADR	((void *)(VRAM + 0x14000))

enum SPRITE_SHAPES {
	SQUARE,
	WIDE,
	TALL
};
#define OBJ_SHAPE(m)		((m)<<14)


// Sprite Attribute 0
#define OBJ_Y(m)			((m)&0x00ff)
#define OBJ_ROT_SCALE_ON	(1<<8)
#define OBJ_DISABLE			(1<<9)
#define OBJ_DOUBLE			(1<<9)
#define OBJ_MODE(m)			((m)<<10)
#define OBJ_MOSAIC			(1<<12)
#define	OBJ_256_COLOR		(1<<13)
#define	OBJ_16_COLOR		(0<<13)

#define ATTR0_MOSAIC			(1<<12)
#define ATTR0_COLOR_256			(1<<13)
#define ATTR0_COLOR_16			(0<<13)
#define ATTR0_NORMAL			(0<<8)
#define ATTR0_ROTSCALE			(1<<8)
#define ATTR0_DISABLED			(2<<8)
#define ATTR0_ROTSCALE_DOUBLE	(3<<8)

#define ATTR0_SQUARE	OBJ_SHAPE(SQUARE)
#define ATTR0_WIDE		OBJ_SHAPE(WIDE)
#define ATTR0_TALL		OBJ_SHAPE(TALL)
// Sprite Attribute 1
#define OBJ_X(m)			((m)&0x01ff)
#define OBJ_ROT_SCALE(m)	((m)<<9)
#define OBJ_HFLIP			(1<<12)
#define OBJ_VFLIP			(1<<13)

#define ATTR1_ROTDATA(n)      ((n)<<9)  // note: overlaps with flip flags
#define ATTR1_FLIP_X          (1<<12)
#define ATTR1_FLIP_Y          (1<<13)
#define ATTR1_SIZE_8          (0<<14)
#define ATTR1_SIZE_16         (1<<14)
#define ATTR1_SIZE_32         (2<<14)
#define ATTR1_SIZE_64         (3<<14)

#define OBJ_SIZE(m)		((m)<<14)

// Sprite Attribute 2
#define OBJ_CHAR(m)		((m)&0x03ff)
#define OBJ_PRIORITY(m)	((m)<<10)
#define OBJ_PALETTE(m)	((m)<<12)

#define ATTR2_PRIORITY(n)     ((n)<<10)
#define ATTR2_PALETTE(n)      ((n)<<12)

#define OBJ_TRANSLUCENT	OBJ_MODE(1)
#define OBJ_OBJWINDOW	OBJ_MODE(2)
#define OBJ_SQUARE		OBJ_SHAPE(0)
#define OBJ_WIDE		OBJ_SHAPE(1)
#define OBJ_TALL		OBJ_SHAPE(2)

enum SPRITE_SIZECODE {
		Sprite_8x8,
		Sprite_16x16,
		Sprite_32x32,
		Sprite_64x64,
		Sprite_16x8,
		Sprite_32x8,
		Sprite_32x16,
		Sprite_64x32,
		Sprite_8x16,
		Sprite_8x32,
		Sprite_16x32,
		Sprite_32x64
};


// gba_systemcalls.h
typedef enum RESTART_FLAG {
	ROM_RESTART,	/*!< Restart from RAM entry point. */
	RAM_RESTART		/*!< restart from ROM entry point */
} RESTART_FLAG;

enum RESET_FLAG {
	RESET_EWRAM		=	(1<<0),	/*!< Clear 256K on-board WRAM			*/
	RESET_IWRAM		=	(1<<1),	/*!< Clear 32K in-chip WRAM				*/
	RESET_PALETTE	=	(1<<2),	/*!< Clear Palette						*/
	RESET_VRAM		=	(1<<3),	/*!< Clear VRAM							*/
	RESET_OAM		=	(1<<4),	/*!< Clear OAM							*/
	RESET_SIO		=	(1<<5),	/*!< Switches to general purpose mode	*/
	RESET_SOUND		=	(1<<6),	/*!< Reset Sound registers				*/
	RESET_OTHER		=	(1<<7)	/*!< all other registers				*/
};

static inline void Halt()	{ SystemCall(2); }
static inline void Stop()	{ SystemCall(3); }
static inline u32 BiosCheckSum()
{
	register u32 result;
	#if	defined	( __thumb__ )
		__asm ("SWI	0x0d\nmov %0,r0\n" :  "=r"(result) :: "r1", "r2", "r3");
	#else
		__asm ("SWI	0x0d<<16\nmov %0,r0\n" : "=r"(result) :: "r1", "r2", "r3");
	#endif
	return result;
}

static inline void VBlankIntrWait()	{ SystemCall(5); }


// gba_timers.h
#define REG_TM0CNT		*(vu32*)(REG_BASE + 0x100)
#define REG_TM0CNT_L	*(vu16*)(REG_BASE + 0x100)
#define REG_TM0CNT_H	*(vu16*)(REG_BASE + 0x102)
#define REG_TM1CNT		*(vu32*)(REG_BASE + 0x104)
#define REG_TM1CNT_L	*(vu16*)(REG_BASE + 0x104)
#define REG_TM1CNT_H	*(vu16*)(REG_BASE + 0x106)
#define REG_TM2CNT		*(vu32*)(REG_BASE + 0x108)
#define REG_TM2CNT_L	*(vu16*)(REG_BASE + 0x108)
#define REG_TM2CNT_H	*(vu16*)(REG_BASE + 0x10a)
#define REG_TM3CNT		*(vu32*)(REG_BASE + 0x10c)
#define REG_TM3CNT_L	*(vu16*)(REG_BASE + 0x10c)
#define REG_TM3CNT_H	*(vu16*)(REG_BASE + 0x10e)
#define	TIMER_COUNT	BIT(2)
#define	TIMER_IRQ	BIT(6)
#define	TIMER_START	BIT(7)


// gba_video.h
#define BG_COLORS		((u16 *)0x05000000)	// Background color table
#define BG_PALETTE		((u16 *)0x05000000)	// Background color table
#define	OBJ_COLORS		((u16 *)0x05000200)	// Sprite color table
#define	SPRITE_PALETTE	((u16 *)0x05000200)	// Sprite color table
#define	REG_DISPCNT		*((vu16 *)(REG_BASE + 0x00))

typedef enum LCDC_BITS {
	MODE_0	=	0,	/*!< BG Mode 0 */
	MODE_1	=	1,	/*!< BG Mode 1 */
	MODE_2	=	2,	/*!< BG Mode 2 */
	MODE_3	=	3,	/*!< BG Mode 3 */
	MODE_4	=	4,	/*!< BG Mode 4 */
	MODE_5	=	5,	/*!< BG Mode 5 */

	BACKBUFFER	=	BIT(4),		/*!< buffer display select			*/
	OBJ_1D_MAP	=	BIT(6),		/*!< sprite 1 dimensional mapping	*/
	LCDC_OFF	=	BIT(7),		/*!< LCDC OFF						*/
	BG0_ON		=	BIT(8),		/*!< enable background 0			*/
	BG1_ON		=	BIT(9),		/*!< enable background 1			*/
	BG2_ON		=	BIT(10),	/*!< enable background 2			*/
	BG3_ON		=	BIT(11),	/*!< enable background 3			*/
	OBJ_ON		=	BIT(12),	/*!< enable sprites					*/
	WIN0_ON		=	BIT(13),	/*!< enable window 0				*/
	WIN1_ON		=	BIT(14),	/*!< enable window 1				*/
	OBJ_WIN_ON	=	BIT(15),	/*!< enable obj window				*/

	BG0_ENABLE		=	BG0_ON,		/*!< enable background 0	*/
	BG1_ENABLE		=	BG1_ON, 	/*!< enable background 1	*/
	BG2_ENABLE		=	BG2_ON, 	/*!< enable background 2	*/
	BG3_ENABLE		=	BG3_ON,		/*!< enable background 3	*/
	OBJ_ENABLE		=	OBJ_ON, 	/*!< enable sprites			*/
	WIN0_ENABLE		=	WIN0_ON,	/*!< enable window 0		*/
	WIN1_ENABLE		=	WIN1_ON,	/*!< enable window 1		*/
	OBJ_WIN_ENABLE	=	BG0_ON, 	/*!< enable obj window		*/

	BG_ALL_ON		=	BG0_ON | BG1_ON | BG2_ON | BG3_ON, 	    /*!< All Backgrounds on.		*/
	BG_ALL_ENABLE	=	BG0_ON | BG1_ON | BG2_ON | BG3_ON	    /*!< All Backgrounds enabled.	*/

} LCDC_BITS;

#define	REG_DISPSTAT	*((vu16 *)(REG_BASE + 0x04))

enum LCDC_IRQ {
	LCDC_VBL_FLAG	=	(1<<0),
	LCDC_HBL_FLAG	=	(1<<1),
	LCDC_VCNT_FLAG	=	(1<<2),
	LCDC_VBL		=	(1<<3),
	LCDC_HBL		=	(1<<4),
	LCDC_VCNT		=	(1<<5)
};

static inline u32 VCOUNT( int m) { return m<<8; }
#define	REG_VCOUNT		*((vu16 *)(REG_BASE + 0x06))
#define BGCTRL		((vu16 *)(REG_BASE + 0x08))
#define REG_BG0CNT	*((vu16 *)(REG_BASE + 0x08))
#define REG_BG1CNT	*((vu16 *)(REG_BASE + 0x0a))
#define REG_BG2CNT	*((vu16 *)(REG_BASE + 0x0c))
#define REG_BG3CNT	*((vu16 *)(REG_BASE + 0x0e))

typedef struct {
	vu16 x;
	vu16 y;
} bg_scroll;

#define BG_OFFSET ((bg_scroll *)(REG_BASE + 0x10))
#define	REG_BG0HOFS		*((vu16 *)(REG_BASE + 0x10))	// BG 0 H Offset
#define	REG_BG0VOFS		*((vu16 *)(REG_BASE + 0x12))	// BG 0 V Offset
#define	REG_BG1HOFS		*((vu16 *)(REG_BASE + 0x14))	// BG 1 H Offset
#define	REG_BG1VOFS		*((vu16 *)(REG_BASE + 0x16))	// BG 1 V Offset
#define	REG_BG2HOFS		*((vu16 *)(REG_BASE + 0x18))	// BG 2 H Offset
#define	REG_BG2VOFS		*((vu16 *)(REG_BASE + 0x1a))	// BG 2 V Offset
#define	REG_BG3HOFS		*((vu16 *)(REG_BASE + 0x1c))	// BG 3 H Offset
#define	REG_BG3VOFS		*((vu16 *)(REG_BASE + 0x1e))	// BG 3 V Offset
#define	REG_BG2PA	*((vu16 *)(REG_BASE + 0x20))
#define	REG_BG2PB	*((vu16 *)(REG_BASE + 0x22))
#define	REG_BG2PC	*((vu16 *)(REG_BASE + 0x24))
#define	REG_BG2PD	*((vu16 *)(REG_BASE + 0x26))
#define	REG_BG2X	*((vu32 *)(REG_BASE + 0x28))
#define	REG_BG2Y	*((vu32 *)(REG_BASE + 0x2c))
#define	REG_BG3PA	*((vu16 *)(REG_BASE + 0x30))
#define	REG_BG3PB	*((vu16 *)(REG_BASE + 0x32))
#define	REG_BG3PC	*((vu16 *)(REG_BASE + 0x34))
#define	REG_BG3PD	*((vu16 *)(REG_BASE + 0x36))
#define	REG_BG3X	*((vu32 *)(REG_BASE + 0x38))
#define	REG_BG3Y	*((vu32 *)(REG_BASE + 0x3c))
#define BG_SIZE(m)		((m<<14))

enum BG_CTRL_BITS {
	BG_MOSAIC		=	BIT(6),		/*!< enable background mosaic			*/
	BG_16_COLOR		=	(0<<7),		/*!< background uses 16 color tiles		*/
	BG_256_COLOR	=	BIT(7),		/*!< background uses 256 color tiles	*/
	BG_WRAP			=	BIT(13),	/*!< background wraps when scrolling	*/
	BG_SIZE_0		=	BG_SIZE(0),	/*!< Map Size 256x256	*/
	BG_SIZE_1		=	BG_SIZE(1),	/*!< Map Size 512x256	*/
	BG_SIZE_2		=	BG_SIZE(2),	/*!< Map Size 256x512	*/
	BG_SIZE_3		=	BG_SIZE(3),	/*!< Map Size 512x512	*/
};

#define	CHAR_BASE(m)		((m) << 2)
#define BG_TILE_BASE(m)		((m) << 2)
#define CHAR_BASE_ADR(m)	((void *)(VRAM + ((m) << 14)))
#define CHAR_BASE_BLOCK(m)	((void *)(VRAM + ((m) << 14)))
#define MAP_BASE_ADR(m)		((void *)(VRAM + ((m) << 11)))
#define SCREEN_BASE_BLOCK(m)((void *)(VRAM + ((m) << 11)))
#define SCREEN_BASE(m)		((m) << 8)
#define BG_MAP_BASE(m)		((m) << 8)

#define	TILE_BASE(m)		((m) << 2)
#define TILE_BASE_ADR(m)	((void *)(VRAM + ((m) << 14)))

#define MAP_BASE_ADR(m)		((void *)(VRAM + ((m) << 11)))
#define MAP_BASE(m)			((m) << 8)

#define BG_PRIORITY(m)		((m))
#define CHAR_PALETTE(m)		((m)<<12)

#define PATRAM4(x, tn) ((u32 *)(VRAM | (((x) << 14) + ((tn) << 5)) ))
#define PATRAM8(x, tn) ((u32 *)(VRAM | (((x) << 14) + ((tn) << 6)) ))
#define SPR_VRAM(tn) ((u32 *)(VRAM | 0x10000 | ((tn) << 5)))

typedef u16 NAMETABLE[32][32];
#define MAP ((NAMETABLE *)0x06000000)

#define BG_WID_32 BG_SIZE_0
#define BG_WID_64 BG_SIZE_1
#define BG_HT_32  BG_SIZE_0
#define BG_HT_64  BG_SIZE_2

#define ROTBG_SIZE_16  BG_SIZE_0
#define ROTBG_SIZE_32  BG_SIZE_1
#define ROTBG_SIZE_64  BG_SIZE_2
#define ROTBG_SIZE_128 BG_SIZE_3

#define TEXTBG_SIZE_256x256    BG_SIZE_0
#define TEXTBG_SIZE_512x256    BG_SIZE_1
#define TEXTBG_SIZE_256x512    BG_SIZE_2
#define TEXTBG_SIZE_512x512    BG_SIZE_3

#define ROTBG_SIZE_128x128    BG_SIZE_0
#define ROTBG_SIZE_256x256    BG_SIZE_1
#define ROTBG_SIZE_512x512    BG_SIZE_2
#define ROTBG_SIZE_1024x1024  BG_SIZE_3

typedef u16 MODE3_LINE[240];
typedef u16 MODE5_LINE[160];

#define MODE3_FB ((MODE3_LINE *)0x06000000)
#define MODE5_FB ((MODE5_LINE *)0x06000000)
#define MODE5_BB ((MODE5_LINE *)0x0600A000)

#define	REG_WIN0H	*((vu16 *)(REG_BASE + 0x40))
#define	REG_WIN1H	*((vu16 *)(REG_BASE + 0x42))
#define	REG_WIN0V	*((vu16 *)(REG_BASE + 0x44))
#define	REG_WIN1V	*((vu16 *)(REG_BASE + 0x46))
#define	REG_WININ	*((vu16 *)(REG_BASE + 0x48))
#define	REG_WINOUT	*((vu16 *)(REG_BASE + 0x4A))

#define	REG_MOSAIC	*(vu16 *)(REG_BASE + 0x4c)

#define	REG_BLDCNT		*((vu16 *)(REG_BASE + 0x50))
#define	REG_BLDALPHA	*((vu16 *)(REG_BASE + 0x52))
#define	REG_BLDY		*((vu16 *)(REG_BASE + 0x54))

static inline void SetMode(int mode)	{REG_DISPCNT = mode;}

#define RGB5(r,g,b)	((r)|((g)<<5)|((b)<<10))
#define RGB8(r,g,b)	( (((b)>>3)<<10) | (((g)>>3)<<5) | ((r)>>3) )

#define SCREEN_WIDTH 240
#define SCREEN_HEIGHT 160


//---------------------------------------------------------------------------
// Reg
#define REG_IRQ_WAITFLAGS		*(volatile u16*)0x3007FF8
#define REG_WSCNT				*(volatile u16*)0x4000204


//---------------------------------------------------------------------------
// KeyMask
#define KEY_NONE				0x0000
#define STAT_MASK				0x00ff


//---------------------------------------------------------------------------
// SetMode
#define OBJ_2D_MAP				0x0


//---------------------------------------------------------------------------
// Timer
#define TIMER_FREQ_PER_1		0
#define TIMER_FREQ_PER_64		1
#define TIMER_FREQ_PER_256		2
#define TIMER_FREQ_PER_1024		3
#define TIMER_CASCADE			(1<<2)


//---------------------------------------------------------------------------
// Mosaic
#define MOSAIC_BG_H(x)			((x)<<0)
#define MOSAIC_BG_V(x)			((x)<<4)
#define MOSAIC_OBJ_H(x)			((x)<<8)
#define MOSAIC_OBJ_V(x)			((x)<<12)


//---------------------------------------------------------------------------
// Window
#define WIN_RIGHT(x)			((x)<<0)		// REG_WIN0H, WIN1H
#define WIN_LEFT(x)				((x)<<8)

#define WIN_DOWN(x)				((x)<<0)		// REG_WIN0V, WIN1V
#define WIN_TOP(x)				((x)<<8)

#define WIN_0_BG0				(1<<0)			// REG_WININ, WINOUT
#define WIN_0_BG1				(1<<1)
#define WIN_0_BG2				(1<<2)
#define WIN_0_BG3				(1<<3)
#define WIN_0_OBJ				(1<<4)
#define WIN_0_SPE				(1<<5)
#define WIN_1_BG0				(1<<8)
#define WIN_1_BG1				(1<<9)
#define WIN_1_BG2				(1<<10)
#define WIN_1_BG3				(1<<11)
#define WIN_1_OBJ				(1<<12)
#define WIN_1_SPE				(1<<13)


//---------------------------------------------------------------------------
// Blend
#define BLEND_TOP_BG0			(1<<0)			// REG_BLDCNT
#define BLEND_TOP_BG1			(1<<1)
#define BLEND_TOP_BG2			(1<<2)
#define BLEND_TOP_BG3			(1<<3)
#define BLEND_TOP_OBJ			(1<<4)
#define BLEND_TOP_BD			(1<<5)
#define BLEND_LOW_BG0			(1<<8)
#define BLEND_LOW_BG1			(1<<9)
#define BLEND_LOW_BG2			(1<<10)
#define BLEND_LOW_BG3			(1<<11)
#define BLEND_LOW_OBJ			(1<<12)
#define BLEND_LOW_BD			(1<<13)
                     
#define BLEND_MODE_OFF			(0<<6)			// REG_BLDALPHA
#define BLEND_MODE_ALPHA		(1<<6)
#define BLEND_MODE_LIGHT		(2<<6)
#define BLEND_MODE_DARK			(3<<6)
#define BLEND_LOW(n)			((n)<<0)
#define BLEND_HIGH(n)			((n)<<8)
#define BLEND_LEVEL(n)			(BLEND_LOW(n) | BLEND_HIGH(n))
#define BLEND_BALANCE(n)		(BLEND_LOW(n) | BLEND_HIGH(16-n))

#define BLEND_DEPTH(n)			((n)<<0)		// REG_BLDY


// �C�����A�ǉ���
//---------------------------------------------------------------------------
// Snd
#define	REG_SOUNDCNT_L	(*((u16 volatile *) (REG_BASE + 0x080)))
#define	REG_SOUNDCNT_H	(*((u16 volatile *) (REG_BASE + 0x082)))
#define	REG_SOUNDCNT_X	(*((u16 volatile *) (REG_BASE + 0x084)))

#define	REG_SOUND1CNT_L	(*((u16 volatile *) (REG_BASE + 0x060)))
#define	REG_SOUND1CNT_H	(*((u16 volatile *) (REG_BASE + 0x062)))
#define	REG_SOUND1CNT_X	(*((u16 volatile *) (REG_BASE + 0x064)))

// REG_SOUNDCNT_L
#define DMG_LEFT_VOLUME(x)		((x)<<0)		// 0-7
#define DMG_RIGHT_VOLUME(x)		((x)<<4)		// 0-7
#define SOUND1_LEFT_OUTPUT		(1<<8)
#define SOUND2_LEFT_OUTPUT		(1<<9)
#define SOUND3_LEFT_OUTPUT		(1<<10)
#define SOUND4_LEFT_OUTPUT		(1<<11)
#define SOUND1_RIGHT_OUTPUT		(1<<12)
#define SOUND2_RIGHT_OUTPUT		(1<<13)
#define SOUND3_RIGHT_OUTPUT		(1<<14)
#define SOUND4_RIGHT_OUTPUT		(1<<15)

// SOUNDCNT_H
#define SOUND_OUTPUT_RATIO(x)	((x)<<0)		// �T�E���h�o�̓��V�I 0-2 (0=25%,1=50%,2=100%)

// REG_SOUNDCNT_X
#define SOUND1_STATUS			(1<<0)			// �T�E���h�̏��
#define SOUND2_STATUS			(1<<1)			// �T�E���h�̏��
#define SOUND3_STATUS			(1<<2)			// �T�E���h�̏��
#define SOUND4_STATUS			(1<<3)			// �T�E���h�̏��
#define ALL_SOUND_ENABLE		(1<<7)			// �S�T�E���h�g�p

// REG_SOUND1CNT_L
#define SOUND1_SWEEP_SHIFT(x)	((x)<<0)		// �X�B�[�v�V�t�g 0-7
#define SOUND1_SWEEP_DIR(x)		((x)<<3)		// �X�B�[�v���� 0-1
#define SOUND1_SWEEP_TIME(x)	((x)<<4)		// �X�B�[�v���� 0-7

// REG_SOUND1CNT_H
#define SOUND1_LENGTH(x)		((x)<<0)		// �T�E���h�̒��� 0-63
#define SOUND1_DUTY_CYCLE(x)	((x)<<6)		// �f���[�e�B�T�C�N�� 0-3
#define SOUND1_ENVELOP_STEP(x)	((x)<<8)		// �G���x���[�v�X�e�b�v���� 0-7
#define SOUND1_ENVELOP_DEC		((0)<<11)		// �G���x���[�v����
#define SOUND1_ENVELOP_INC		((1)<<11)		// �G���x���[�v����
#define SOUND1_ENVELOP_DIR(x)	((x)<<11)		// �G���x���[�v���� 0-1
#define SOUND1_ENVELOP_VALUE(x)	((x)<<12)		// �G���x���[�v�����l 0-15

// REG_SOUND1CNT_X
#define SOUND1_FREQ(x)			((x)<<0)		// ���� 0-2048
#define SOUND1_CONTINUE			(0<<14)			// �p��
#define SOUND1_TIMED			(1<<14)			// ���Ԑ���
#define SOUND1_RESET			(1<<15)			// �T�E���h1���Z�b�g

// REG_SOUND2CNT_L
#define SOUND2_LENGTH(x)		((x)<<0)		// �T�E���h�̒��� 0-63
#define SOUND2_DUTY_CYCLE(x)	((x)<<6)		// �f���[�e�B�T�C�N�� 0-3
#define SOUND2_ENVELOP_STEP(x)	((x)<<8)		// �G���x���[�v�X�e�b�v���� 0-7
#define SOUND2_ENVELOP_DEC		((0)<<11)		// �G���x���[�v����
#define SOUND2_ENVELOP_INC		((1)<<11)		// �G���x���[�v����
#define SOUND2_ENVELOP_DIR(x)	((x)<<11)		// �G���x���[�v���� 0-1
#define SOUND2_ENVELOP_VALUE(x)	((x)<<12)		// �G���x���[�v�����l 0-15

// REG_SOUND2CNT_H
#define SOUND2_FREQ(x)			((x)<<0)		// ���� 0-2048
#define SOUND2_CONTINUE			(0<<14)			// �p��
#define SOUND2_TIMED			(1<<14)			// ���Ԑ���
#define SOUND2_RESET			(1<<15)			// �T�E���h2���Z�b�g

// REG_SOUND3CNT_L
#define SOUND3_BANK_2x32		(0<<5)			// 32bit�̃o���N���
#define SOUND3_BANK_1x64		(1<<5)			// 64bit�̃o���N���
#define SOUND3_BANK_SELECT(x)	((x)<<6) 		// �o���N��I�� �I�����Ă��Ȃ��ق����������߂� 0-1
#define SOUND3_OUTPUT_ENABLE	(1<<7) 			// �T�E���h3�o��
#define SOUND3_OUTPUT_DISABLE	(0<<7)			// �T�E���h3�o�͂��Ȃ�

// REG_SOUND3CNT_H
#define SOUND3_LENGTH(x)		((x)<<0)		// �T�E���h�̒��� 0-255
#define SOUND3_VOLUME_RATIO(x)	((x)<<13)		// �{�����[���o�̓��V�I 0-4 1��100%


// REG_SOUND3CNT_X
#define SOUND3_FREQ(x)			((x)<<0)		// ���� 0-2048
#define SOUND3_CONTINUE			(0<<14)			// �p��
#define SOUND3_TIMED			(1<<14)			// ���Ԑ���
#define SOUND3_RESET			(1<<15)			// �T�E���h1���Z�b�g

#define REG_SGWR0				*(volatile u32*)0x4000090
#define REG_SGWR1				*(volatile u32*)0x4000094
#define REG_SGWR2				*(volatile u32*)0x4000098
#define REG_SGWR3				*(volatile u32*)0x400009C


// REG_SOUND4CNT_L
#define SOUND4_LENGTH(x)		((x)<<0)		// �T�E���h�̒��� 0-63
#define SOUND4_ENVELOP_STEP(x)	((x)<<8)		// �G���x���[�v�X�e�b�v���� 0-7
#define SOUND4_ENVELOP_DEC		((0)<<11)		// �G���x���[�v����
#define SOUND4_ENVELOP_INC		((1)<<11)		// �G���x���[�v����
#define SOUND4_ENVELOP_DIR(x)	((x)<<11)		// �G���x���[�v���� 0-1
#define SOUND4_ENVELOP_VALUE(x)	((x)<<12)		// �G���x���[�v�����l 0-15

// REG_SOUND4CNT_H
#define SOUND4_DIVIDE_FREQ(x)	((x)<<0)		// ���� 0-7
#define SOUND4_STAGE_15			(0<<3)			// 15Bit �J�E���^�X�e�[�W
#define SOUND4_STAGE_7			(1<<3)			// 7Bit  �J�E���^�X�e�[�W
#define SOUND4_STAGE_FREQ(x)	((x)<<4)		// �X�e�b�v���Ƃ̎��� 0-13
#define SOUND4_CONTINUE			(0<<14)			// �p��
#define SOUND4_TIMED			(1<<14)			// ���Ԑ���
#define SOUND4_RESET			(1<<15)			// �T�E���h3���Z�b�g


// A, B
#define SNDA_TIMER0				(0 << 10)
#define SNDB_TIMER1				(1 << 14)

//---------------------------------------------------------------------------
// Sprite
#define SP_PAL(pal)				((pal) << 12)
#define SP_NOFLIP				((0x4000))
#define SP_HFLIP				((0x1000) | (0x4000))
#define SP_VFLIP				((0x2000) | (0x4000))
#define SP_HVFLIP				(SP_HFLIP | SP_VFLIP)


//---------------------------------------------------------------------------
// Bios
#define CPUSET_SRC_FIX		(1<<24)
#define CPUSET_16BIT		(0<<26)
#define CPUSET_32BIT		(1<<26)


//---------------------------------------------------------------------------
// Etc
#if _DEBUG
#define TRACE					_Printf
#define _ASSERT(x)				if(!(x)) SystemError("[Assert] %s(%d): "#x"\n", __FILE__, __LINE__)
#else
#define TRACE(...)				((void)0)
#define _ASSERT(x)				((void)0)
#endif

#define __PACKED				__attribute__((__packed__))
#define HIBYTE(x)				((u8)(((x) >> 8) & 0xff))
#define LOBYTE(x)				((u8)((x) & 0xff))
#define MAKEWORD(l, h)			(((l) & 0xff) | (((h) << 8) & 0xff00))

#define ROM_CODE				__attribute__((section (".text"),long_call))
#define ROM_DATA				__attribute__((section (".roda")))

#define SCREEN_CX				240
#define SCREEN_CY				160

typedef enum { FALSE, TRUE } bool;


#include "common.h"
#include "div.h"
#include "sys_arm.h"
#include "gbfs.h"

//---------------------------------------------------------------------------------
#endif //_gba_h
//---------------------------------------------------------------------------------
