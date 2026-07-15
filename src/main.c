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

/*
 * So uhm
 * This is my second ever C project
 * so beware, ugly code incoming
 */

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
//#include "gfx/gfx.h"

int main(void) {
	/*
	uint8_t AnsType;
	void *Ans = os_GetAnsData(&AnsType);
	string_t *filename_a;
	if (Ans != NULL && AnsType == OS_TYPE_STR) {
		filename_a = Ans;
		//printf("Len: %d\n", name->len);
		if (filename_a->len > 8 || filename_a->len == 0) {
			return 1;
		}
	} else {
		return 1;
	}
	*/

	gfx_Begin();
	gfx_SetFontData(font);
	kb_SetMode(MODE_3_CONTINUOUS);

	uint8_t filetype;
	char *filename = fileselectmenu(&filetype);
	if (filename[1] >= 'A') {
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
