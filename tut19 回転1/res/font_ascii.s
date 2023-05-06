
@{{BLOCK(font_ascii)

@=======================================================================
@
@	font_ascii, 256x24@4, 
@	+ palette 16 entries, not compressed
@	+ 96 tiles not compressed
@	Total size: 32 + 3072 = 3104
@
@	Time-stamp: 2023-05-05, 11:53:08
@	Exported by Cearn's GBA Image Transmogrifier, v0.9.2
@	( http://www.coranac.com/projects/#grit )
@
@=======================================================================

	.section .rodata
	.align	2
	.global font_asciiTiles		@ 3072 unsigned chars
	.hidden font_asciiTiles
font_asciiTiles:
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x2000,0x0002,0x2000,0x0002,0x2000,0x0002,0x2000,0x0002
	.hword 0x1000,0x0002,0x0000,0x0001,0x2000,0x0002,0x1000,0x0001
	.hword 0x2200,0x0220,0x2200,0x0220,0x2200,0x0220,0x2100,0x0210
	.hword 0x1000,0x0100,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x2200,0x0220,0x2220,0x2222,0x2210,0x1221
	.hword 0x2200,0x0220,0x2220,0x2222,0x2210,0x1221,0x1100,0x0110

	.hword 0x0000,0x0002,0x2200,0x2222,0x1120,0x1112,0x2220,0x0222
	.hword 0x1110,0x2112,0x2220,0x2222,0x1110,0x1112,0x0000,0x0001
	.hword 0x2220,0x2000,0x2120,0x1200,0x1220,0x0120,0x0110,0x0012
	.hword 0x2000,0x2201,0x1200,0x2120,0x0120,0x2220,0x0010,0x1110
	.hword 0x2200,0x0000,0x1120,0x0002,0x0020,0x0002,0x0210,0x0202
	.hword 0x2120,0x0201,0x1020,0x0122,0x2210,0x2211,0x1100,0x1100
	.hword 0x2000,0x0002,0x2000,0x0002,0x2000,0x0002,0x1000,0x0002
	.hword 0x0000,0x0001,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000

	.hword 0x0000,0x0022,0x2000,0x0012,0x2200,0x0001,0x2200,0x0000
	.hword 0x2200,0x0000,0x2100,0x0002,0x1000,0x0022,0x0000,0x0011
	.hword 0x2200,0x0000,0x2100,0x0002,0x1000,0x0022,0x0000,0x0022
	.hword 0x0000,0x0022,0x2000,0x0012,0x2200,0x0001,0x1100,0x0000
	.hword 0x2000,0x0002,0x2020,0x0202,0x2210,0x0122,0x2100,0x0012
	.hword 0x2200,0x0022,0x2120,0x0212,0x2010,0x0102,0x1000,0x0001
	.hword 0x0000,0x0000,0x2000,0x0002,0x2000,0x0002,0x2220,0x0222
	.hword 0x2220,0x0222,0x2110,0x0112,0x2000,0x0002,0x1000,0x0001

	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0022,0x0000,0x0022,0x2000,0x0012,0x1000,0x0001
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x2220,0x0222
	.hword 0x2220,0x0222,0x1110,0x0111,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x2000,0x0002,0x2000,0x0002,0x1000,0x0001
	.hword 0x0000,0x0000,0x0000,0x0200,0x0000,0x0120,0x0000,0x0012
	.hword 0x2000,0x0001,0x1200,0x0000,0x0120,0x0000,0x0010,0x0000

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
	.hword 0x2000,0x0002,0x2000,0x0002,0x1000,0x0001,0x0000,0x0000
	.hword 0x2000,0x0002,0x2000,0x0002,0x1000,0x0001,0x0000,0x0000
	.hword 0x2000,0x0002,0x2000,0x0002,0x1000,0x0001,0x0000,0x0000
	.hword 0x2000,0x0002,0x1000,0x0002,0x0000,0x0002,0x0000,0x0001

	.hword 0x0000,0x0000,0x0000,0x0022,0x2000,0x0012,0x2200,0x0001
	.hword 0x2100,0x0002,0x1000,0x0022,0x0000,0x0011,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x2200,0x0022,0x1100,0x0011
	.hword 0x0000,0x0000,0x2200,0x0022,0x1100,0x0011,0x0000,0x0000
	.hword 0x0000,0x0000,0x2000,0x0002,0x1000,0x0022,0x0000,0x0221
	.hword 0x0000,0x0122,0x2000,0x0012,0x1000,0x0001,0x0000,0x0000
	.hword 0x2200,0x0222,0x1220,0x2211,0x0220,0x2200,0x0110,0x1220
	.hword 0x0000,0x0122,0x0000,0x0011,0x0000,0x0022,0x0000,0x0011

	.hword 0x2200,0x0222,0x1120,0x0211,0x2020,0x0202,0x2020,0x0202
	.hword 0x2020,0x0122,0x1020,0x0011,0x2210,0x2222,0x1100,0x1111
	.hword 0x2000,0x2222,0x2200,0x2211,0x1220,0x2200,0x0220,0x2200
	.hword 0x2220,0x2202,0x1220,0x2201,0x0220,0x2200,0x0110,0x1100
	.hword 0x2220,0x0222,0x1220,0x2211,0x0220,0x2200,0x2220,0x1222
	.hword 0x1220,0x2211,0x0220,0x2200,0x0220,0x2222,0x0110,0x1111
	.hword 0x2200,0x0222,0x1220,0x2211,0x0220,0x1100,0x0220,0x0000
	.hword 0x0220,0x0000,0x0220,0x2200,0x2210,0x1222,0x1100,0x0111

	.hword 0x2220,0x0022,0x1220,0x0221,0x0220,0x2210,0x0220,0x2200
	.hword 0x0220,0x2200,0x0220,0x2200,0x0220,0x1222,0x0110,0x0111
	.hword 0x2220,0x2222,0x1220,0x1111,0x0220,0x0000,0x2220,0x0022
	.hword 0x1220,0x0011,0x0220,0x0000,0x2220,0x2222,0x1110,0x1111
	.hword 0x2220,0x2222,0x1220,0x1111,0x0220,0x0000,0x2220,0x0022
	.hword 0x1220,0x0011,0x0220,0x0000,0x0220,0x0000,0x0110,0x0000
	.hword 0x2200,0x2222,0x1220,0x1111,0x0220,0x0000,0x0220,0x2222
	.hword 0x0220,0x2211,0x0220,0x2200,0x2210,0x2222,0x1100,0x1111

	.hword 0x0220,0x2200,0x0220,0x2200,0x0220,0x2200,0x2220,0x2222
	.hword 0x1220,0x2211,0x0220,0x2200,0x0220,0x2200,0x0110,0x1100
	.hword 0x2200,0x0022,0x2100,0x0012,0x2000,0x0002,0x2000,0x0002
	.hword 0x2000,0x0002,0x2000,0x0002,0x2200,0x0022,0x1100,0x0011
	.hword 0x2220,0x2222,0x1110,0x1122,0x0000,0x0022,0x0000,0x0022
	.hword 0x0000,0x0022,0x2220,0x0022,0x2210,0x0012,0x1100,0x0001
	.hword 0x0220,0x0200,0x0220,0x2220,0x2220,0x1122,0x2220,0x0012
	.hword 0x1220,0x0022,0x0220,0x0221,0x0220,0x2210,0x0110,0x1100

	.hword 0x0220,0x0000,0x0220,0x0000,0x0220,0x0000,0x0220,0x0000
	.hword 0x0220,0x0000,0x0220,0x0000,0x2220,0x2222,0x1110,0x1111
	.hword 0x0220,0x2200,0x0220,0x2200,0x2220,0x2220,0x2220,0x2222
	.hword 0x1220,0x2212,0x0220,0x2201,0x0220,0x2200,0x0110,0x1100
	.hword 0x0220,0x2200,0x0220,0x2200,0x2220,0x2200,0x1220,0x2202
	.hword 0x0220,0x2221,0x0220,0x2210,0x0220,0x2200,0x0110,0x1100
	.hword 0x2200,0x0222,0x1220,0x2211,0x0220,0x2200,0x0220,0x2200
	.hword 0x0220,0x2200,0x0220,0x2200,0x2210,0x1222,0x1100,0x0111

	.hword 0x2220,0x0222,0x1220,0x2211,0x0220,0x2200,0x0220,0x2200
	.hword 0x2220,0x1222,0x1220,0x0111,0x0220,0x0000,0x0110,0x0000
	.hword 0x2200,0x0222,0x1220,0x2211,0x0220,0x2200,0x0220,0x2200
	.hword 0x0220,0x2202,0x0220,0x1221,0x2210,0x2212,0x1100,0x1101
	.hword 0x2220,0x0222,0x1220,0x2211,0x0220,0x2200,0x2220,0x1222
	.hword 0x1220,0x0121,0x0220,0x0210,0x0220,0x2100,0x0110,0x1000
	.hword 0x2200,0x0222,0x1220,0x2211,0x0220,0x1100,0x2210,0x0222
	.hword 0x1100,0x2211,0x0220,0x2200,0x2210,0x1222,0x1100,0x0111

	.hword 0x2220,0x0222,0x2110,0x0112,0x2000,0x0002,0x2000,0x0002
	.hword 0x2000,0x0002,0x2000,0x0002,0x2000,0x0002,0x1000,0x0001
	.hword 0x0220,0x2200,0x0220,0x2200,0x0220,0x2200,0x0220,0x2200
	.hword 0x0220,0x2200,0x0220,0x2200,0x2210,0x1222,0x1100,0x0111
	.hword 0x0220,0x2200,0x0220,0x2200,0x0220,0x2200,0x0220,0x2200
	.hword 0x2210,0x1220,0x2100,0x0122,0x1000,0x0012,0x0000,0x0001
	.hword 0x0220,0x2200,0x0220,0x2200,0x0220,0x2200,0x0220,0x2202
	.hword 0x0220,0x2202,0x0220,0x2202,0x2210,0x1221,0x1100,0x0110

	.hword 0x0220,0x2200,0x0220,0x2200,0x2210,0x1220,0x1100,0x0112
	.hword 0x2200,0x0221,0x1220,0x2210,0x0220,0x2200,0x0110,0x1100
	.hword 0x0220,0x2200,0x0220,0x2200,0x0220,0x2200,0x0220,0x2200
	.hword 0x2210,0x2222,0x1100,0x2211,0x2200,0x1222,0x1100,0x0111
	.hword 0x2220,0x2222,0x1110,0x2211,0x0000,0x1220,0x0000,0x0122
	.hword 0x2000,0x0012,0x2200,0x0001,0x2220,0x2222,0x1110,0x1111
	.hword 0x2000,0x0022,0x2000,0x0011,0x2000,0x0000,0x2000,0x0000
	.hword 0x2000,0x0000,0x2000,0x0000,0x2000,0x0022,0x1000,0x0011

	.hword 0x0200,0x0200,0x2100,0x0120,0x2200,0x0222,0x1100,0x0112
	.hword 0x2200,0x0222,0x1100,0x0112,0x0000,0x0002,0x0000,0x0001
	.hword 0x2000,0x0022,0x1000,0x0021,0x0000,0x0020,0x0000,0x0020
	.hword 0x0000,0x0020,0x0000,0x0020,0x2000,0x0022,0x1000,0x0011
	.hword 0x0000,0x0002,0x2000,0x0021,0x1000,0x0010,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x2220,0x2222,0x1110,0x1111

	.hword 0x2000,0x0000,0x1000,0x0002,0x0000,0x0021,0x0000,0x0010
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x2200,0x0022,0x1220,0x0221
	.hword 0x0220,0x0220,0x0220,0x0120,0x2210,0x2212,0x1100,0x1101
	.hword 0x0220,0x0000,0x0220,0x0000,0x2220,0x0022,0x1220,0x0221
	.hword 0x0220,0x0220,0x0220,0x0220,0x2220,0x0122,0x1110,0x0011
	.hword 0x0000,0x0000,0x0000,0x0000,0x2200,0x0022,0x1220,0x0221
	.hword 0x0220,0x0110,0x0220,0x0220,0x2210,0x0122,0x1100,0x0011

	.hword 0x0000,0x0220,0x0000,0x0220,0x2200,0x0222,0x1220,0x0221
	.hword 0x0220,0x0220,0x0220,0x0220,0x2210,0x0222,0x1100,0x0111
	.hword 0x0000,0x0000,0x0000,0x0000,0x2200,0x0022,0x1220,0x0221
	.hword 0x2220,0x0222,0x1220,0x0111,0x2210,0x0222,0x1100,0x0111
	.hword 0x0000,0x0000,0x0000,0x0022,0x2000,0x0012,0x2000,0x0002
	.hword 0x2200,0x0022,0x2100,0x0012,0x2000,0x0002,0x1000,0x0001
	.hword 0x0000,0x0000,0x0000,0x0000,0x2200,0x0222,0x1220,0x0221
	.hword 0x2220,0x0222,0x1110,0x0221,0x2200,0x0122,0x1100,0x0011

	.hword 0x2200,0x0000,0x2200,0x0000,0x2200,0x0000,0x2200,0x0022
	.hword 0x2200,0x0221,0x2200,0x0220,0x2200,0x0220,0x1100,0x0110
	.hword 0x0000,0x0000,0x2000,0x0002,0x1000,0x0001,0x2000,0x0002
	.hword 0x2000,0x0002,0x2000,0x0002,0x2000,0x0022,0x1000,0x0011
	.hword 0x0000,0x0000,0x2000,0x0002,0x1000,0x0001,0x2000,0x0002
	.hword 0x2000,0x0002,0x2000,0x0002,0x2200,0x0002,0x1100,0x0001
	.hword 0x2200,0x0000,0x2200,0x0000,0x2200,0x0200,0x2200,0x0120
	.hword 0x2200,0x0012,0x2200,0x0021,0x2200,0x0210,0x1100,0x0100

	.hword 0x0000,0x0000,0x2200,0x0002,0x2100,0x0002,0x2000,0x0002
	.hword 0x2000,0x0002,0x2000,0x0002,0x2000,0x0022,0x1000,0x0011
	.hword 0x0000,0x0000,0x0000,0x0000,0x2220,0x0022,0x1220,0x0212
	.hword 0x0220,0x0202,0x0220,0x0202,0x0220,0x0202,0x0110,0x0101
	.hword 0x0000,0x0000,0x0000,0x0000,0x2220,0x0022,0x1220,0x0221
	.hword 0x0220,0x0220,0x0220,0x0220,0x0220,0x0220,0x0110,0x0110
	.hword 0x0000,0x0000,0x0000,0x0000,0x2200,0x0022,0x1220,0x0221
	.hword 0x0220,0x0220,0x0220,0x0220,0x2210,0x0122,0x1100,0x0011

	.hword 0x0000,0x0000,0x0000,0x0000,0x2220,0x0022,0x1220,0x0221
	.hword 0x0220,0x0220,0x2220,0x0122,0x1220,0x0011,0x0110,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x2200,0x0222,0x1220,0x0221
	.hword 0x0220,0x0220,0x2210,0x0222,0x1100,0x0221,0x0000,0x0110
	.hword 0x0000,0x0000,0x0000,0x0000,0x2200,0x0020,0x2200,0x0012
	.hword 0x2200,0x0001,0x2200,0x0000,0x2200,0x0000,0x1100,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x2200,0x0222,0x1220,0x0111
	.hword 0x2220,0x0222,0x1110,0x0221,0x2220,0x0222,0x1110,0x0111

	.hword 0x0000,0x0000,0x2000,0x0002,0x2220,0x0222,0x2110,0x0112
	.hword 0x2000,0x0002,0x2000,0x0002,0x2000,0x0022,0x1000,0x0011
	.hword 0x0000,0x0000,0x0000,0x0000,0x0220,0x0220,0x0220,0x0220
	.hword 0x0220,0x0220,0x0220,0x0220,0x2210,0x2212,0x1100,0x1101
	.hword 0x0000,0x0000,0x0000,0x0000,0x0220,0x0200,0x0220,0x0200
	.hword 0x2210,0x0120,0x2200,0x0020,0x2100,0x0012,0x1000,0x0001
	.hword 0x0000,0x0000,0x0000,0x0000,0x0220,0x0202,0x0220,0x0202
	.hword 0x0220,0x0202,0x0220,0x0202,0x2210,0x0121,0x1100,0x0010

	.hword 0x0000,0x0000,0x0000,0x0000,0x0220,0x0220,0x2110,0x0112
	.hword 0x2000,0x0002,0x2000,0x0002,0x1220,0x0221,0x0110,0x0110
	.hword 0x0000,0x0000,0x0000,0x0000,0x0220,0x0220,0x0220,0x0220
	.hword 0x2220,0x0222,0x1110,0x0221,0x2220,0x0122,0x1110,0x0011
	.hword 0x0000,0x0000,0x0000,0x0000,0x2220,0x0222,0x1110,0x0121
	.hword 0x2000,0x0012,0x1200,0x0001,0x2220,0x0222,0x1110,0x0111
	.hword 0x0000,0x0002,0x2000,0x0001,0x2000,0x0000,0x1200,0x0000
	.hword 0x2100,0x0000,0x2000,0x0000,0x1000,0x0002,0x0000,0x0001

	.hword 0x0000,0x0002,0x0000,0x0002,0x0000,0x0002,0x0000,0x0002
	.hword 0x0000,0x0002,0x0000,0x0002,0x0000,0x0002,0x0000,0x0001
	.hword 0x2000,0x0000,0x1000,0x0002,0x0000,0x0002,0x0000,0x0021
	.hword 0x0000,0x0012,0x0000,0x0002,0x2000,0x0001,0x1000,0x0000
	.hword 0x2220,0x0222,0x1110,0x0111,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000

	.section .rodata
	.align	2
	.global font_asciiPal		@ 32 unsigned chars
	.hidden font_asciiPal
font_asciiPal:
	.hword 0x0000,0x292A,0x7FFF,0x0000,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000

@}}BLOCK(font_ascii)
