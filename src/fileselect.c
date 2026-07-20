/**
 * --------------------------------------
 *
 * Hexes Source Code - fileselect.c
 * By StephenM
 * Copyright 2024 - 2026
 * License: GPL-3.0
 *
 * --------------------------------------
**/


#include "fileselect.h"
#include "defines.h"
#include <stdlib.h>
#include <stdint.h>
#include <fileioc.h>
#include <keypadc.h>
#include <graphx.h>
#include <sys/timers.h>
#include <ti/vars.h>
#include <string.h>

char *fileselectmenu(uint8_t *outfiletype) {
	uint24_t cursor = 0;
	uint24_t scroll = 0;

	gfx_SetTransparentColor(MAGENTA);
	gfx_SetTextTransparentColor(MAGENTA);

	gfx_FillScreen(COLORS_BG);

	gfx_SetTextFGColor(COLORS_FG);
	gfx_SetTextBGColor(COLORS_BG);

	gfx_SetMonospaceFont(8);

	int tab = 0;

	char namelist[256][9] = {};

	for (;;) {
		uint8_t filetype;
		switch (tab) {
			case 0:
				filetype = OS_TYPE_PRGM;
				break;
			case 1:
				filetype = OS_TYPE_PROT_PRGM;
				break;
			case 2:
				filetype = OS_TYPE_APPVAR;
				break;
			case 3:
				filetype = OS_TYPE_STR;
				break;
			default:
				filetype = OS_TYPE_PRGM;
				break;
		}

		uint8_t namelistsize = 0;

		for (int i = 0; i < 256; i++) {
			strcpy(namelist[i], "\0\0\0\0\0\0\0\0\0");
		}

		void *search_pos = NULL;

		for (;;) {
			uint8_t type;
			//const char *name = ti_DetectAny(&search_pos, "", &type);
			const char *name = ti_DetectAny(&search_pos, "", &type);

			if (name == NULL) {break;}

			//if (type != OS_TYPE_PRGM && type != OS_TYPE_PROT_PRGM) {continue;}
			if (type != filetype) {continue;}

			if (name[0] < 'A') {continue;}

			strcpy(namelist[namelistsize], name);
			namelistsize++;
		}

		for (;;) {
			gfx_SetDrawBuffer();
			gfx_FillScreen(COLORS_BG);
			gfx_PrintStringXY("Open", 0, 232);
			gfx_PrintStringXY("<<<", 75, 232);
			gfx_PrintStringXY(">>>", 145, 232);
			gfx_SetTextXY(10, 10);
			//gfx_PrintUInt(tab, 2);

			gfx_SetTextXY(0, 10);
			gfx_SetTextFGColor(tab == 0 ? COLORS_BG : COLORS_FG);
			gfx_SetTextBGColor(tab == 0 ? COLORS_FG : COLORS_BG);
			gfx_PrintString(" PRGM ");

			gfx_SetTextFGColor(tab == 1 ? COLORS_BG : COLORS_FG);
			gfx_SetTextBGColor(tab == 1 ? COLORS_FG : COLORS_BG);
			gfx_PrintString(" PROT.PRGM ");

			gfx_SetTextFGColor(tab == 2 ? COLORS_BG : COLORS_FG);
			gfx_SetTextBGColor(tab == 2 ? COLORS_FG : COLORS_BG);
			gfx_PrintString(" APPVAR ");

			gfx_SetTextFGColor(tab == 3 ? COLORS_BG : COLORS_FG);
			gfx_SetTextBGColor(tab == 3 ? COLORS_FG : COLORS_BG);
			gfx_PrintString(" STR ");

			gfx_SetTextFGColor(COLORS_FG);
			gfx_SetTextBGColor(COLORS_BG);

			for (int i = 0; i < 20; i++) {
				if (i + scroll < namelistsize) {
					if (i + scroll == cursor) {
						gfx_PrintStringXY(">", 32, i * 10 + 24);
					}
					uint8_t han = ti_OpenVar(namelist[i + scroll], "r", filetype);
					if (ti_IsArchived(han) != 0) {
						gfx_PrintStringXY("*", 40, i * 10 + 24);
					}
					gfx_SetTextXY(128, i * 10 + 24);
					gfx_PrintUInt(ti_GetSize(han), 5);
					ti_Close(han);
					gfx_PrintStringXY(namelist[i + scroll], 48, i * 10 + 24);
				}
			}

			gfx_SwapDraw();


			if kb_IsDown(kb_KeyClear) {return "1";}
			if kb_IsDown(kb_KeyYequ) {*outfiletype = filetype; return namelist[cursor];}
			if kb_IsDown(kb_KeyWindow) {tab--; break;}
			if kb_IsDown(kb_KeyZoom) {tab++; break;}

			if kb_IsDown(kb_KeyDown) {cursor++;}
			if kb_IsDown(kb_KeyUp) {cursor--;}
			if (cursor < scroll) {scroll--;}
			if (cursor > 1000) {cursor = namelistsize - 1; scroll = namelistsize >= 20 ? cursor - 20 : scroll;}
			if (namelist[cursor][0] == '\0') {cursor = 0; scroll = 0;}
			if (cursor > scroll + 19) {scroll++;}

			//while (!kb_AnyKey());
		}

		delay(100);
	}

	return "0"; //namelist[cursor];
}
