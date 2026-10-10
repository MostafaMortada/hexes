/**
 * --------------------------------------
 *
 * Hexes Source Code - main.c
 * By StephenM
 * Copyright 2024 - 2026
 * License: GPL-3.0
 * Version: 2.0.0 BETA
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
#include "globals.h"
#include "fileoper.h"
#include "fileselect.h"
#include "editor.h"
#include "headless.h"
#include "colorpicker.h"
#include "config.h"
//#include "gfx/gfx.h"

int main(void) {
	uint8_t filetype;
	bool headless_has_palette;
	char *filename = check_for_ans(&filetype, &headless_has_palette); // headless start

	gfx_Begin();
	gfx_SetFontData(font_hexes);
	kb_SetMode(MODE_3_CONTINUOUS);

	load_config(headless_has_palette);
	
	gfx_SetTextTransparentColor(ret_text_trans_color());
	

	if (filename[0] < 'A') { // this only executes if headless start failed
show_file_selector:
		filename = fileselectmenu(&filetype);
	}

	{
		uint8_t handle = ti_Open(RECENTS_FILENAME, "r");
		ti_SetArchiveStatus(true, handle);
		ti_Close(handle);
	}

	if (filename[0] >= 'A') {
		copyvar(filename, filetype, BUFFER_FILENAME, OS_TYPE_APPVAR);
		int exit_code = start_editor(filename, filetype);
		if (exit_code == 1) { goto show_file_selector; }
	}

	ti_Delete(BUFFER_FILENAME);

	gfx_End();
	write_config();
	{
		uint8_t handle = ti_Open(CONFIG_FILENAME, "r");
		ti_SetArchiveStatus(true, handle);
		ti_Close(handle);
	}

	return 0;
}
