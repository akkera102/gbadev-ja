#include "malloc.h"

//---------------------------------------------------------------------------
u8 MallocMem[2000];

//---------------------------------------------------------------------------
u32* MallocPatch(u32 size)
{
	TRACE("MallocPatch: size=%d\n", size);

	return (u32*)MallocMem;
}
