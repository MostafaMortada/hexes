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
			case 4:
				filetype = OS_TYPE_EQU;
				break;
			case 5:
				filetype = OS_TYPE_REAL;
				break;
			case 6:
				filetype = OS_TYPE_REAL_LIST;
				break;
			case 7:
				filetype = OS_TYPE_CPLX;
				break;
			case 8:
				filetype = OS_TYPE_CPLX_LIST;
				break;
			case 9:
				filetype = OS_TYPE_MATRIX;
				break;
			case 10:
				filetype = OS_TYPE_PIC;
				break;
			case 11:
				filetype = OS_TYPE_GDB;
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
			//gfx_SetTextXY(10, 10);
			//gfx_PrintUInt(tab, 2);

			for (int i = 0; i <= 11; i++) {
				/*if (i == 0) {
					gfx_SetTextXY(0, 10);
				} else if (i == 5) {
					gfx_SetTextXY(0, 20);
				}*/
				gfx_SetTextFGColor(tab == i ? COLORS_BG : COLORS_FG);
				gfx_SetTextBGColor(tab == i ? COLORS_FG : COLORS_BG);
				switch (i) {
					case 0:
						gfx_SetTextXY(0, 10);
						gfx_PrintString(" PRGM ");
						break;
					case 1:
						gfx_PrintString(" PROT.PRGM ");
						break;
					case 2:
						gfx_PrintString(" APPVAR ");
						break;
					case 3:
						gfx_PrintString(" STR ");
						break;
					case 4:
						gfx_PrintString(" EQU ");
						gfx_PrintChar(14);
						break;
					case 5:
						gfx_SetTextXY(0, 20);
						gfx_PrintString(" REAL ");
						break;
					case 6:
						gfx_PrintString(" REAL LIST ");
						break;
					case 7:
						gfx_PrintString(" CPLX ");
						break;
					case 8:
						gfx_PrintString(" CPLX LIST ");
						gfx_PrintChar(14);
						break;
					case 9:
						gfx_SetTextXY(0, 30);
						gfx_PrintString(" MATRIX ");
						break;
					case 10:
						gfx_PrintString(" PICTURE ");
						break;
					case 11:
						gfx_PrintString(" GDB ");
						break;
				}
			}

			gfx_SetTextFGColor(COLORS_FG);
			gfx_SetTextBGColor(COLORS_BG);

			for (int i = 0; i < 18; i++) {
				if (i + scroll < namelistsize) {
					if (i + scroll == cursor) {
						gfx_PrintStringXY(">", 32, i * 10 + 44);
					}
					uint8_t han = ti_OpenVar(namelist[i + scroll], "r", filetype);
					if (ti_IsArchived(han) != 0) {
						gfx_PrintStringXY("*", 40, i * 10 + 44);
					}
					gfx_SetTextXY(128, i * 10 + 44);
					gfx_PrintUInt(ti_GetSize(han), 5);
					ti_Close(han);
					char *name = namelist[i + scroll];
					gfx_SetTextXY(48, i*10 + 44);
					switch (name[0]) {
						case 0x5D: // List
							if (name[1] < 6) {
								gfx_PrintChar('L');
								gfx_PrintChar(name[1] + '1');
							} else {
								gfx_PrintString(name + 1);
							}
							break;
						case 0x5C:
							gfx_PrintChar('[');
							gfx_PrintChar(name[1] + 'A');
							gfx_PrintChar(']');
							break;
						//case 0xAA:
						//	gfx_PrintString("Str");
						//	gfx_PrintUInt(name[1] + 1, 1);
						//	break;
						default:
							gfx_PrintString(name);
							break;
					}
					//gfx_PrintStringXY(namelist[i + scroll], 48, i * 10 + 34);
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
			if (cursor > 1000) {cursor = namelistsize - 1; scroll = namelistsize >= 18 ? cursor - 18 : scroll;}
			if (namelist[cursor][0] == '\0') {cursor = 0; scroll = 0;}
			if (cursor > scroll + 17) {scroll++;}

			//while (!kb_AnyKey());
		}

		delay(100);
	}

	return "0"; //namelist[cursor];
}
