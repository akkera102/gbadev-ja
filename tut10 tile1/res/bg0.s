
@{{BLOCK(bg0)

@=======================================================================
@
@	bg0, 64x16@8, 
@	+ palette 256 entries, not compressed
@	+ 16 tiles not compressed
@	Total size: 512 + 1024 = 1536
@
@	Time-stamp: 2023-04-26, 17:16:53
@	Exported by Cearn's GBA Image Transmogrifier, v0.9.2
@	( http://www.coranac.com/projects/#grit )
@
@=======================================================================

	.section .rodata
	.align	2
	.global bg0Tiles		@ 1024 unsigned chars
	.hidden bg0Tiles
bg0Tiles:
	.hword 0x3315,0x3613,0x3636,0x3647,0x3615,0x3633,0x2C36,0x3633
	.hword 0x3633,0x3313,0x471A,0x3336,0x4733,0x1315,0x3611,0x3347
	.hword 0x3345,0x3636,0x3615,0x4533,0x1A47,0x1536,0x3333,0x1513
	.hword 0x3636,0x1315,0x3315,0x1545,0x1533,0x1533,0x4536,0x0215
	.hword 0x1536,0x361A,0x3613,0x4713,0x3628,0x343F,0x1036,0x1515
	.hword 0x4B16,0x3647,0x1333,0x1A11,0x3333,0x3612,0x1628,0x3615
	.hword 0x4715,0x1328,0x3345,0x134B,0x4513,0x334B,0x3313,0x3633
	.hword 0x4512,0x3315,0x1947,0x1113,0x3313,0x5333,0x101A,0x3615

	.hword 0xBEBE,0xBEBE,0xBEBE,0xBEBE,0xBEBE,0xBEBE,0x0905,0xBEBE
	.hword 0xBEBE,0xBEBE,0x02BF,0xBEBE,0xBEBE,0xBE02,0xBEBE,0xBEBE
	.hword 0xBEBE,0x0109,0xBEBE,0xBEBE,0xBEBE,0xBEBE,0xBEBE,0x0602
	.hword 0xBEBE,0xBEBE,0xBEBE,0x0DB8,0xBEBE,0xBEBE,0xBEBE,0xB8C1
	.hword 0xBEBE,0xBEBE,0xBEBE,0xBEBE,0xBEBE,0xBEBE,0xBEBE,0xBEBE
	.hword 0x05BE,0xBEBF,0x08BE,0xBE09,0x0C01,0xBE03,0x02BE,0xBE01
	.hword 0xBEBE,0xBEBE,0xBEBE,0xBEBE,0xBE03,0xBEBE,0xBEBE,0xBEBE
	.hword 0xBE05,0xBEBE,0xBEBE,0xBEBE,0xBEC1,0xBEBE,0xBEBE,0xBEBE

	.hword 0x8B91,0x8B91,0xA78B,0x8B8B,0x8B8B,0xB5A6,0x8EA7,0x8BA7
	.hword 0x918B,0xA78B,0x91A7,0xA68B,0xA68B,0x91A7,0x918B,0x8B91
	.hword 0x8B8B,0x8B8E,0x8BA7,0x8B8B,0xA791,0xB78B,0xA78E,0x91A6
	.hword 0x918B,0x8B8B,0xA78B,0x91A7,0x8B8B,0x8E8B,0x8BA6,0xB58E
	.hword 0x8B8B,0x8BA6,0x8BA6,0x8EB5,0xA7A6,0xA68B,0x8BA7,0xA6A6
	.hword 0x8B8B,0x8B8B,0xB58B,0xA78B,0xA7A6,0x9191,0x8BA7,0xA68B
	.hword 0x8DA7,0x8B8B,0xA7A7,0x8B8B,0xB78B,0xB88D,0xA7A7,0x8B8D
	.hword 0x8BA7,0x8B8B,0x8E8B,0x8B8B,0xB78B,0x8B8B,0x8B8B,0x8B91

	.hword 0x1F1F,0x1F1F,0x1F1F,0x1F1F,0x3F34,0x3F3F,0x3636,0x1F2D
	.hword 0x3633,0x3633,0x362C,0x1F36,0x3719,0x3733,0x3737,0x1F1A
	.hword 0x1F1F,0x1F1F,0x1F1F,0x1F1E,0x3F1A,0x1F36,0x3636,0x3D36
	.hword 0x3333,0x1F2C,0x3D34,0x3333,0x332D,0x1F1A,0x3336,0x333D
	.hword 0x1F1F,0x1F1F,0x1F1F,0x1F1F,0x2D3E,0x3336,0x3733,0x1F2C
	.hword 0x2C2C,0x2D36,0x3D3D,0x1F1A,0x3715,0x3316,0x3733,0x1F37
	.hword 0x1F1F,0x1F1F,0x1F1F,0x1F1F,0x3F3F,0x1F33,0x3F2C,0x2C3F
	.hword 0x3636,0x1F36,0x1A34,0x362C,0x3316,0x1F2D,0x2D33,0x3337

	.hword 0x1536,0x1336,0x3345,0x3615,0x1533,0x1316,0x4715,0x1336
	.hword 0x3428,0x3347,0x3633,0x1612,0x1236,0x2833,0x3316,0x3615
	.hword 0x1333,0x121A,0x3633,0x3633,0x1136,0x3619,0x3636,0x1633
	.hword 0x3613,0x3636,0x3633,0x3633,0x3613,0x4547,0x3333,0x4748
	.hword 0x361A,0x1519,0x1328,0x3634,0x3633,0x3634,0x3636,0x3612
	.hword 0x3613,0x1647,0x3336,0x3315,0x1515,0x3633,0x0E33,0x3413
	.hword 0x3615,0x3415,0x3315,0x2833,0x3613,0x3636,0x3645,0x0E36
	.hword 0x3311,0x3615,0x1136,0x3616,0x4736,0x3633,0x1636,0x1933

	.hword 0xBEBE,0xBEBE,0xBEBE,0xBEBE,0xBEBE,0xBEBE,0xBEBE,0xBEBE
	.hword 0xBEBE,0xBEBE,0x02BE,0xBEBF,0xBEBE,0x02C1,0x0ABE,0xBEB8
	.hword 0xB8BE,0xB50A,0xBEBF,0xBEBE,0xB8BE,0xB50A,0xBEBF,0xBEBE
	.hword 0x02BE,0x03B8,0xBEBE,0xBEBE,0xBEBE,0xBFBF,0xBEBE,0xBEBE
	.hword 0xBEBE,0x0901,0xBEBE,0xBEBE,0xBEBE,0xB5BF,0xBEBE,0xBEBE
	.hword 0xBEBE,0xBEBE,0xBEBE,0xBEBE,0xBEBE,0xBEBE,0xBEBE,0xBEBE
	.hword 0xBEBE,0x02BE,0xBE02,0xBEBE,0xBEBE,0x0902,0xBE06,0xBEBE
	.hword 0xBEBE,0xB502,0xBE05,0xBEBE,0xBEBE,0x02BE,0xBEBF,0xBEBE

	.hword 0x8BA6,0x8B8B,0x8B91,0xA78B,0xB796,0x8B8E,0x8BA7,0x8BA7
	.hword 0xA68B,0x91B7,0xA6A7,0x8BA7,0x8B91,0x91A6,0x918B,0x8B8B
	.hword 0x8B8B,0x8B91,0x8BA7,0x8B8B,0x8B8E,0x8BA7,0x8B8E,0x918B
	.hword 0x8B8B,0x8BB7,0x0C8B,0x8B8B,0x0D8B,0xB78B,0xA68B,0xA78B
	.hword 0x0D8B,0x8B8B,0xA78B,0x8B91,0xA70C,0x918B,0x8DA7,0x918B
	.hword 0x8B91,0x8B8B,0x8BA6,0xB7A7,0xA78B,0x8B8B,0x8B8D,0xA78B
	.hword 0xA78B,0xA68B,0x8B0A,0xA78B,0x8B8B,0x8B8B,0xB78B,0x918B
	.hword 0xA7A7,0x8B8B,0x8BA7,0x8B8B,0x8B8B,0xA791,0xA7B7,0xA68B

	.hword 0x1F1E,0x1F1F,0x1F1F,0x1F1F,0x3F2C,0x3636,0x2D3F,0x1E36
	.hword 0x3730,0x2D36,0x3636,0x1F2C,0x3336,0x3733,0x3333,0x1F33
	.hword 0x1F1F,0x1F1F,0x1F1F,0x1F1F,0x3F1A,0x1F36,0x3630,0x3336
	.hword 0x3333,0x1E2C,0x3D34,0x2C33,0x332D,0x1F1A,0x3336,0x3333
	.hword 0x1F1F,0x1F1F,0x1E1F,0x1F1F,0x3F3E,0x2D33,0x3636,0x1F2C
	.hword 0x2C34,0x2D36,0x3636,0x1F3F,0x2D36,0x2D33,0x3333,0x1F33
	.hword 0x1E1F,0x1F1F,0x1F1F,0x1F1F,0x3F3F,0x1F33,0x3F2C,0x2C3F
	.hword 0x3619,0x1F3F,0x1A34,0x362C,0x3337,0x1F1A,0x2D33,0x3337

	.section .rodata
	.align	2
	.global bg0Pal		@ 512 unsigned chars
	.hidden bg0Pal
bg0Pal:
	.hword 0x7C1F,0x0842,0x1084,0x18C6,0x18C6,0x294A,0x318C,0x318C
	.hword 0x39CE,0x4631,0x4E73,0x4E73,0x56B5,0x5EF7,0x6739,0x6739
	.hword 0x6F7B,0x77BD,0x7FFF,0x3193,0x3193,0x4E79,0x18CC,0x18CC
	.hword 0x4E79,0x3199,0x18D3,0x3199,0x18D3,0x18D9,0x0004,0x0006
	.hword 0x0006,0x000C,0x0013,0x0019,0x001F,0x18DF,0x319F,0x4E7F
	.hword 0x673F,0x00DF,0x00D9,0x199F,0x1999,0x00D3,0x1999,0x00D3
	.hword 0x327F,0x327F,0x019F,0x1993,0x4F3F,0x1993,0x3279,0x00CC
	.hword 0x00CC,0x0199,0x1A7F,0x3279,0x027F,0x0193,0x333F,0x1A79

	.hword 0x1A79,0x0193,0x0279,0x1B3F,0x033F,0x3273,0x3273,0x4F39
	.hword 0x198C,0x198C,0x4F39,0x1A73,0x3339,0x1A73,0x1B39,0x00C6
	.hword 0x018C,0x0273,0x0339,0x67FF,0x03F9,0x0333,0x1BF9,0x1B33
	.hword 0x026C,0x33F9,0x03F3,0x1A6C,0x3333,0x0186,0x032C,0x1BF3
	.hword 0x4FF9,0x03EC,0x1B2C,0x0266,0x33F3,0x0326,0x1BEC,0x03E6
	.hword 0x326C,0x1986,0x4F33,0x1A66,0x332C,0x1B26,0x00C0,0x0180
	.hword 0x0260,0x0320,0x03E0,0x1BE6,0x33EC,0x4FF3,0x67F9,0x1BE0
	.hword 0x1B20,0x33E6,0x3326,0x1A60,0x4FEC,0x33E0,0x3266,0x4F2C

	.hword 0x1980,0x3320,0x4FE6,0x67F3,0x4FE0,0x4F26,0x3260,0x67EC
	.hword 0x4F20,0x67E6,0x67E0,0x4E6C,0x4E6C,0x6733,0x3186,0x3186
	.hword 0x6733,0x4E66,0x672C,0x4E66,0x6726,0x18C0,0x3180,0x3180
	.hword 0x4E60,0x6720,0x7FE0,0x7FE6,0x7FEC,0x7FF3,0x7FF9,0x7F20
	.hword 0x6660,0x7F26,0x6666,0x4D80,0x7F2C,0x7E60,0x666C,0x4D86
	.hword 0x666C,0x30C0,0x6580,0x7E66,0x7F33,0x4D86,0x7D80,0x6586
	.hword 0x4CC0,0x7E6C,0x64C0,0x7D86,0x7CC0,0x4D8C,0x4D8C,0x6673
	.hword 0x30C6,0x30C6,0x6673,0x4CC6,0x658C,0x64C6,0x1000,0x1800

	.hword 0x1800,0x2000,0x3000,0x4C00,0x6400,0x7C00,0x7CC6,0x7D8C
	.hword 0x7E73,0x7F39,0x7C06,0x6406,0x7CCC,0x64CC,0x4C06,0x7D93
	.hword 0x7C0C,0x4CCC,0x6593,0x3006,0x640C,0x7CD3,0x7E79,0x7C13
	.hword 0x64D3,0x4C0C,0x7D99,0x6413,0x7CD9,0x7C19,0x4D93,0x30CC
	.hword 0x6679,0x4CD3,0x6599,0x64D9,0x1806,0x300C,0x4C13,0x6419
	.hword 0x7C1F,0x7CDF,0x7D9F,0x7E7F,0x641F,0x4C19,0x64DF,0x4CD9
	.hword 0x3013,0x659F,0x4C1F,0x30D3,0x4D99,0x180C,0x3019,0x4CDF
	.hword 0x667F,0x301F,0x30D9,0x1813,0x4D9F,0x1819,0x30DF,0x181F

@}}BLOCK(bg0)
