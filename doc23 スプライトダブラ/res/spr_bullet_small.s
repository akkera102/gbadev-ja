
@{{BLOCK(spr_bullet_small)

@=======================================================================
@
@	spr_bullet_small, 8x32@4, 
@	+ palette 16 entries, not compressed
@	+ 4 tiles not compressed
@	Total size: 32 + 128 = 160
@
@	Time-stamp: 2023-05-12, 08:40:48
@	Exported by Cearn's GBA Image Transmogrifier, v0.9.2
@	( http://www.coranac.com/projects/#grit )
@
@=======================================================================

	.section .rodata
	.align	2
	.global spr_bullet_smallTiles		@ 128 unsigned chars
	.hidden spr_bullet_smallTiles
spr_bullet_smallTiles:
	.hword 0x0000,0x0000,0x0000,0x0000,0x3200,0x0023,0x6300,0x0039
	.hword 0x9300,0x0039,0x3200,0x0023,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x3200,0x0023,0x9300,0x0036
	.hword 0x9300,0x0039,0x3200,0x0023,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x3200,0x0023,0x9300,0x0039
	.hword 0x9300,0x0036,0x3200,0x0023,0x0000,0x0000,0x0000,0x0000
	.hword 0x0000,0x0000,0x0000,0x0000,0x3200,0x0023,0x9300,0x0039
	.hword 0x6300,0x0039,0x3200,0x0023,0x0000,0x0000,0x0000,0x0000

	.section .rodata
	.align	2
	.global spr_bullet_smallPal		@ 32 unsigned chars
	.hidden spr_bullet_smallPal
spr_bullet_smallPal:
	.hword 0x4010,0x0000,0x0140,0x02A0,0x03E0,0x1BE6,0x33EC,0x4FF3
	.hword 0x67F9,0x7FFF,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000

@}}BLOCK(spr_bullet_small)
