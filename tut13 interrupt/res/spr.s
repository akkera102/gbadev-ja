
@{{BLOCK(spr)

@=======================================================================
@
@	spr, 80x8@4, 
@	+ palette 16 entries, not compressed
@	+ 10 tiles not compressed
@	Total size: 32 + 320 = 352
@
@	Time-stamp: 2023-04-30, 00:12:55
@	Exported by Cearn's GBA Image Transmogrifier, v0.9.2
@	( http://www.coranac.com/projects/#grit )
@
@=======================================================================

	.section .rodata
	.align	2
	.global sprTiles		@ 320 unsigned chars
	.hidden sprTiles
sprTiles:
	.hword 0x2200,0x0222,0x1220,0x2211,0x0220,0x2220,0x0220,0x2212
	.hword 0x2220,0x2201,0x1220,0x2200,0x2210,0x1222,0x1100,0x0111
	.hword 0x0000,0x0022,0x2200,0x0022,0x1100,0x0022,0x0000,0x0022
	.hword 0x0000,0x0022,0x0000,0x0022,0x2220,0x2222,0x1110,0x1111
	.hword 0x2200,0x0222,0x1220,0x2211,0x0220,0x2200,0x0110,0x1220
	.hword 0x2000,0x0112,0x1200,0x0001,0x2220,0x2222,0x1110,0x1111
	.hword 0x2220,0x0222,0x1110,0x2211,0x0000,0x2200,0x2200,0x1222
	.hword 0x1100,0x2211,0x0000,0x2200,0x2220,0x1222,0x1110,0x0111

	.hword 0x0000,0x0220,0x0000,0x0222,0x2000,0x0221,0x1200,0x0220
	.hword 0x0120,0x0220,0x2220,0x2222,0x1100,0x1221,0x0000,0x0110
	.hword 0x2220,0x0222,0x1220,0x0111,0x0220,0x0000,0x2220,0x0222
	.hword 0x1110,0x2211,0x0000,0x2200,0x2220,0x1222,0x1110,0x0111
	.hword 0x2200,0x0222,0x1220,0x0111,0x0220,0x0000,0x2220,0x0222
	.hword 0x1220,0x2211,0x0220,0x2200,0x2210,0x1222,0x1100,0x0111
	.hword 0x2220,0x2222,0x1220,0x2211,0x0110,0x1220,0x0000,0x0122
	.hword 0x0000,0x0022,0x2000,0x0012,0x2000,0x0002,0x1000,0x0001

	.hword 0x2200,0x0222,0x1220,0x2211,0x0220,0x2200,0x2210,0x1222
	.hword 0x1220,0x2211,0x0220,0x2200,0x2210,0x1222,0x1100,0x0111
	.hword 0x2200,0x0222,0x1220,0x2211,0x0220,0x2200,0x2210,0x2222
	.hword 0x1100,0x2211,0x0000,0x2200,0x2200,0x1222,0x1100,0x0111

	.section .rodata
	.align	2
	.global sprPal		@ 32 unsigned chars
	.hidden sprPal
sprPal:
	.hword 0x0180,0x292A,0x7FFF,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000

@}}BLOCK(spr)