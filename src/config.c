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
#include <string.h>
#include "ui.h"
#include "colorpicker.h"

void load_config(bool headless_has_palette) {
	uint8_t cfg = ti_Open(CONFIG_FILENAME, "r");
	if (cfg != 0) {
		if (headless_has_palette) {
			ti_Seek(PALETTE_SIZE, SEEK_SET, cfg);
		} else {
			ti_Read(palette, PALETTE_SIZE, 1, cfg);
		}
		ti_Read(&modkeybehavior, 1, 1, cfg);
		uint8_t ha = 0;
		ti_Read(&ha, 1, 1, cfg);
		hex_addresses = ha != 0;
		ti_Close(cfg);
	}
	return;
}

void write_config() {
	uint8_t cfg = ti_Open(CONFIG_FILENAME, "w");
	ti_Write(palette, PALETTE_SIZE, 1, cfg);
	ti_Write(&modkeybehavior, 1, 1, cfg);
	uint8_t ha = hex_addresses ? 1 : 0;
	ti_Write(&ha, 1, 1, cfg);
	ti_Close(cfg);
	return;
}

void config_menu() {
	uint8_t drawloc = gfx_GetDraw();
	//gfx_FillScreen(BLACK);

	bool exit = false;

	bool will_draw_dither = true;

	while (!exit) {
		//kb_Scan();
		gfx_SetDrawScreen();
		//gfx_FillScreen(BLACK);

		while (kb_AnyKey());

		gfx_SetTextBGColor(COLORS_BG);
		gfx_SetTextFGColor(COLORS_FG);

		char optlist[] =
			"CONFIGURATION MENU              \0"
			"Color palette                   \0"
			"Modifier keys   ?               \0"
			"Digit case      ?               \0"
			"Exit menu                       \0";
		
		strcpy(optlist + 66 + 16, ("<   Toggle    > \0" "< Toggle lock > \0" "<    Hold     > \0") + modkeybehavior * 17); // Modifier key option
		strcpy(optlist + 99 + 16, digits_in_uppercase == 0 ? "< lowercase >   \0" : "< UPPERCASE >   \0");
		
		if (will_draw_dither) {
			ditherscreen(COLORS_FG);
		}

		switch (ui_menu(-1, 0, optlist, 1, 33, 5, kb_KeyClear, kb_KeyClear)) {
			case 1: {
				switch (ui_menu(-1, 0,
					"COLOR PALETTE  \0"
					"Default Black  \0"
					"Default White  \0"
					"HexaEdit       \0"
					"CEaShell       \0"
					"Mono Black     \0"
					"Mono White     \0"
					"Custom palette \0",
					1, 16, 9, kb_KeyClear, kb_KeyClear)
				) {
					case 1: {
						uint8_t src[] = {0, 255, 7, 224, 241, 255, 30, 8};
						memcpy(palette, src, sizeof(src));
						break; }
					case 2: {
						uint8_t src[] = {255, 0, 11, 128, 177, 0, 26, 159};
						memcpy(palette, src, sizeof(src));
						break; }
					case 3:
						break;
					case 4: {
						uint8_t src[] = {246, 0, 236, 128, 177, 0, 26, 237};
						memcpy(palette, src, sizeof(src));
						break; }
					case 5: {
						uint8_t src[] = {0, 255, 255, 255, 255, 255, 255, 0};
						memcpy(palette, src, sizeof(src));
						break; }
					case 6: {
						uint8_t src[] = {255, 0, 0, 0, 0, 0, 0, 255};
						memcpy(palette, src, sizeof(src));
						break; }
					case 7: {
						gfx_FillScreen(COLORS_BG);
						for (;;) {
							//while (kb_AnyKey());
							gfx_SetTextBGColor(COLORS_FG);
							gfx_SetTextFGColor(COLORS_BG);
							gfx_PrintStringXY(" CUSTOM COLOR PALETTE ", 0, 0);
							gfx_SetTextBGColor(COLORS_BG);
							gfx_SetTextFGColor(COLORS_FG);
							gfx_PrintStringXY("[1] Foreground", 0, 20);
							gfx_PrintStringXY("[2] Background", 0, 30);
							gfx_SetTextFGColor(COLORS_FG);
							gfx_SetTextBGColor(COLORS_BG2);
							gfx_PrintStringXY("[3] Alternate Background", 0, 40);
							gfx_SetTextBGColor(COLORS_BG);
							gfx_SetTextFGColor(COLORS_CURSOR);
							gfx_PrintStringXY("[4] Cursor", 0, 50);
							gfx_SetTextFGColor(COLORS_FG);
							gfx_PrintStringXY("IN EDITOR:", 0, 60);
							gfx_SetTextFGColor(COLORS_NULL);
							gfx_PrintStringXY("[5] Null bytes (0x00)", 10, 70);
							gfx_SetTextFGColor(COLORS_01_1F);
							gfx_PrintStringXY("[6] ASCII control codes (0x01 - 0x1F)", 10, 80);
							gfx_SetTextFGColor(COLORS_20_7F);
							gfx_PrintStringXY("[7] Displayable glyphs  (0x20 - 0x7F)", 10, 90);
							gfx_SetTextFGColor(COLORS_80_FF);
							gfx_PrintStringXY("[8] The rest            (0x80 - 0xFF)", 10, 100);

							kb_Scan();
							uint8_t edcol_pal = 255;
							if kb_IsDown(kb_KeyClear) break;
							if kb_IsDown(kb_Key1) edcol_pal = 1;
							if kb_IsDown(kb_Key2) edcol_pal = 0;
							if kb_IsDown(kb_Key3) edcol_pal = 7;
							if kb_IsDown(kb_Key4) edcol_pal = 2;
							if kb_IsDown(kb_Key5) edcol_pal = 3;
							if kb_IsDown(kb_Key6) edcol_pal = 4;
							if kb_IsDown(kb_Key7) edcol_pal = 5;
							if kb_IsDown(kb_Key8) edcol_pal = 6;
							if (edcol_pal != 255) {
								palette[edcol_pal] = colorpicker(palette[edcol_pal]);
								gfx_FillScreen(COLORS_BG);
							}
							while (!kb_AnyKey());
						}
						break;
					}
					default:
						break;
				}
				gfx_SetTextTransparentColor(ret_text_trans_color());
				will_draw_dither = true;
				break;
			}
			case 2:
				modkeybehavior = (modkeybehavior + 1) % 3;
				will_draw_dither = false;
				break;
			case 3:
				will_draw_dither = false;
				//hex_addresses = ! hex_addresses;
				digits_in_uppercase = 1 - digits_in_uppercase;
				break;
			default:
				exit = true;
				will_draw_dither = false;
				break;
		}
	}

	gfx_SetDraw(drawloc);
}

