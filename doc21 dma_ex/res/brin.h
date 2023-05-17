
//{{BLOCK(brin)

//======================================================================
//
//	brin, 512x256@4, 
//	+ palette 16 entries, not compressed
//	+ 32 tiles (t|f|p reduced) not compressed
//	+ regular map (in SBBs), not compressed, 64x32 
//	Total size: 32 + 1024 + 4096 = 5152
//
//	Time-stamp: 2023-05-17, 20:34:38
//	Exported by Cearn's GBA Image Transmogrifier, v0.9.2
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_BRIN_H
#define GRIT_BRIN_H

#define brinTilesLen 1024
extern const unsigned short brinTiles[512];

#define brinMapLen 4096
extern const unsigned short brinMap[2048];

#define brinPalLen 32
extern const unsigned short brinPal[16];

#endif // GRIT_BRIN_H

//}}BLOCK(brin)
