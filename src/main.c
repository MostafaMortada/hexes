/**
 * --------------------------------------
 *
 * Hexes Source Code - main.c
 * By StephenM
 * Copyright 2024 - 2026
 * License: GPL-3.0
 * Version: 2.(1672026)
 *
 * --------------------------------------
**/

#include <stdlib.h>
#include <fileioc.h>
#include <keypadc.h>
#include <graphx.h>
#include <math.h>
#include <ti/vars.h>
#include <ti/tokens.h>
#include <ti/getkey.h>
#include "defines.h"
#include "fileselect.h"
#include "editor.h"
#include "headless.h"
//#include "gfx/gfx.h"

int main(void) {

	uint8_t filetype;

	char *filename = check_for_ans(&filetype);

	gfx_Begin();
	gfx_SetFontData(font);
	kb_SetMode(MODE_3_CONTINUOUS);

	if (filename[0] < 'A') {
		filename = fileselectmenu(&filetype);
	}

	if (filename[0] >= 'A') {
		uint8_t bufferh = ti_Open(BUFFER_FILENAME, "w");
		uint8_t fileih = ti_OpenVar(filename, "r", filetype);
		ti_Write(ti_GetDataPtr(fileih), ti_GetSize(fileih), 1, bufferh);
		ti_Close(bufferh);
		ti_Close(fileih);
		start_editor(filename, filetype);
	}

	gfx_End();

	return 0;
}
