/**
 * --------------------------------------
 *
 * Hexes Source Code - config.c 
 * By StephenM
 * Copyright 2024 - 2026
 * License: GPL-3.0
 *
 * --------------------------------------
**/

#include "config.h"
#include "defines.h"
#include "globals.h"
#include <stdlib.h>
#include <stdint.h>
#include <fileioc.h>
#include <keypadc.h>
#include <graphx.h>
#include "ui.h"
#include "colorpicker.h"

void load_config() {}

void write_config() {}

void config_menu() {
	uint8_t drawloc = gfx_GetDraw();
	//gfx_FillScreen(BLACK);

	bool exit = false;


	while (!exit) {
		//kb_Scan();
		gfx_SetDrawScreen();
		gfx_FillScreen(BLACK);

		while (kb_AnyKey());

		gfx_SetTextBGColor(COLORS_BG);
		gfx_SetTextFGColor(COLORS_FG);
		gfx_SetTextXY(208, 30);
		gfx_PrintString("> ");

		switch (modkeybehavior) {
			case MODIFIER_TOGGLE:
				gfx_PrintString("Toggle");
				break;
			case MODIFIER_TOGGLE_LOCK:
				gfx_PrintString("Toggle lock");
				break;
			case MODIFIER_HOLD:
				gfx_PrintString("Hold");
				break;
		}

		int option = ui_menu(2, 2,
			"CONFIGURATION MENU      \0"
			"Color palette           \0"
			"Modifier keys           \0"
			"Exit menu               \0",
		1, 25, 4);

		switch (option) {
			case 1: {
				for (;;) {
					//while (kb_AnyKey());
					gfx_FillScreen(COLORS_BG);
					gfx_SetTextBGColor(COLORS_BG);
					gfx_SetTextFGColor(COLORS_FG);
					gfx_PrintStringXY("COLOR PALETTE", 0, 0);
					gfx_PrintStringXY("[1] Foreground", 0, 20);
					gfx_PrintStringXY("[2] Background", 0, 30);
					gfx_SetTextFGColor(COLORS_CURSOR);
					gfx_PrintStringXY("[3] Cursor", 0, 40);
					gfx_SetTextFGColor(COLORS_NULL);
					gfx_PrintStringXY("[4] IN-EDITOR: Null bytes (0x00)", 0, 50);
					gfx_SetTextFGColor(COLORS_01_1F);
					gfx_PrintStringXY("[5] IN-EDITOR: ASCII control codes (0x01 - 0x1F)", 0, 60);
					gfx_SetTextFGColor(COLORS_20_7F);
					gfx_PrintStringXY("[6] IN-EDITOR: Displayable ASCII glyphs (0x20 - 0x7F)", 0, 70);
					gfx_SetTextFGColor(COLORS_80_FF);
					gfx_PrintStringXY("[7] IN-EDITOR: The rest (0x80 - 0xFF)", 0, 80);

					kb_Scan();
					uint8_t edcol_pal = 255;
					if kb_IsDown(kb_KeyClear) break;
					if kb_IsDown(kb_Key1) edcol_pal = 1;
					if kb_IsDown(kb_Key2) edcol_pal = 0;
					if kb_IsDown(kb_Key3) edcol_pal = 2;
					if kb_IsDown(kb_Key4) edcol_pal = 3;
					if kb_IsDown(kb_Key5) edcol_pal = 4;
					if kb_IsDown(kb_Key6) edcol_pal = 5;
					if kb_IsDown(kb_Key7) edcol_pal = 6;
					if (edcol_pal != 255) {
						palette[edcol_pal] = colorpicker(palette[edcol_pal]);
					}
					while (!kb_AnyKey());
				}
				break;
			}
			case 2:
				modkeybehavior = (modkeybehavior + 1) % 3;
				break;
			case 3:
				exit = true;
				break;
			default:
				break;
		}
	}

	gfx_SetDraw(drawloc);
}

