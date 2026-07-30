/**
 * --------------------------------------
 *
 * Hexes Source Code - fileoper.c
 * By StephenM
 * Copyright 2024 - 2026
 * License: GPL-3.0
 *
 * --------------------------------------
**/

#include "fileoper.h"
#include <fileioc.h>

int copyvar(char *srcname, uint8_t srctype, char *destname, uint8_t desttype) {
	uint8_t desth = ti_OpenVar(destname, "w", desttype);
	uint8_t srch = ti_OpenVar(srcname, "r", srctype);
	ti_Write(ti_GetDataPtr(srch), ti_GetSize(srch), 1, desth);
	ti_Close(desth);
	ti_Close(srch);
	return 0;
}
