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
#include "globals.h"
#include <stdlib.h>
#include <stdint.h>
#include <fileioc.h>
#include <keypadc.h>
#include <graphx.h>
#include <sys/timers.h>
#include <ti/vars.h>
#include <string.h>
#include "input.h"

#define TAB_COUNT 3
#define ITEM_COUNT 20 // 18 // How many file names on-screen
//#define LIST_Y 44
#define LIST_Y 26
#define ARROW_REPEATTIMER 6

#define RECENTS -1

char *fileselectmenu(uint8_t *outfiletype) {
	uint24_t cursor = 0;
	uint24_t scroll = 0;

	gfx_SetTransparentColor(MAGENTA);
	gfx_SetTextTransparentColor(MAGENTA);

	gfx_FillScreen(COLORS_BG);

	gfx_SetTextFGColor(COLORS_FG);
	gfx_SetTextBGColor(COLORS_BG);

	gfx_SetMonospaceFont(8);

	bool keydownUp = false;
	bool keydownDown = false;
	bool keydownLeft = false;
	bool keydownRight = false;
	int arrowrepeattimer = 0;
	int tab = -1; // Slightly questionable numbering but eh it's fine

	static char namelist[256][10] = {};

	{
		uint8_t rec = ti_Open(RECENTS_FILENAME, "a");
		ti_Resize(256, rec);
		ti_Close(rec);
	}

	for (;;) {
		uint8_t filetype;
		switch (tab) {
			case -1:
				break;
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
			strcpy(namelist[i], "\0\0\0\0\0\0\0\0\0\0");
		}

		if (tab == -1) {
			// Load recently opened file names and their types

			uint8_t rec = ti_Open(RECENTS_FILENAME, "r");
			if (rec != 0) {
				namelistsize = ti_GetC(rec);
				ti_Read(namelist, 10, namelistsize, rec);
				ti_Close(rec);
			}
		} else {
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
		}

		for (;;) {
			gfx_SetDrawBuffer();
			gfx_FillScreen(COLORS_BG);

			gfx_SetTextFGColor(COLORS_FG);
			gfx_SetTextBGColor(COLORS_BG);

			gfx_PrintStringXY("Open", 0, 232);
			gfx_PrintStringXY("<<<", 75, 232);
			gfx_PrintStringXY(">>>", 145, 232);
			//gfx_SetTextXY(10, 10);
			//gfx_PrintUInt(tab, 2);

			for (int i = -1; i < TAB_COUNT; i++) {
				/*if (i == 0) {
					gfx_SetTextXY(0, 10);
				} else if (i == 5) {
					gfx_SetTextXY(0, 20);
				}*/
				gfx_SetTextFGColor(tab == i ? COLORS_BG : COLORS_FG);
				gfx_SetTextBGColor(tab == i ? COLORS_FG : COLORS_BG);
				switch (i) {
					case -1:
						gfx_SetTextXY(0, 10);
						gfx_PrintString(" RECENTS ");
						break;
					case 0:
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

			for (int i = 0; i < ITEM_COUNT; i++) {
				if (i + scroll < namelistsize) {
					if (i + scroll == cursor) {
						//gfx_PrintStringXY(">", 32, i * 10 + 44);
						gfx_SetColor(COLORS_CURSOR);
						gfx_FillRectangle(32, i * 10 + LIST_Y - 2, 128 + 16, 11);
					}
					if (tab == RECENTS) {
						filetype = namelist[i + scroll][9];
					}
					gfx_SetTextFGColor(i + scroll == cursor ? COLORS_BG : COLORS_FG);
					gfx_SetTextBGColor(i + scroll == cursor ? COLORS_CURSOR : COLORS_BG);
					uint8_t han = ti_OpenVar(namelist[i + scroll], "r", filetype);
					if (ti_IsArchived(han) != 0) {
						gfx_PrintStringXY("*", 40, i * 10 + LIST_Y);
					}
					gfx_SetTextXY(128, i * 10 + LIST_Y);
					gfx_PrintUInt(ti_GetSize(han), 5);
					ti_Close(han);
					char *name = namelist[i + scroll];
					gfx_SetTextXY(48, i*10 + LIST_Y);
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

			// Draw scroll bar
			gfx_SetColor(COLORS_FG);
			gfx_Rectangle(10, LIST_Y, 6, ITEM_COUNT * 10);
			if (namelistsize <= ITEM_COUNT) {
				gfx_FillRectangle(12, LIST_Y + 2, 2, ITEM_COUNT * 10 - 4);
			} else {
				gfx_FillRectangle(12, LIST_Y + 2 + (ITEM_COUNT * 10 * scroll) / namelistsize, 2, ((ITEM_COUNT * 10 - 4) * ITEM_COUNT) / namelistsize - 2);
			}

			gfx_SwapDraw();

			uint8_t arrowkeys = arrow_key_repeat_handler(&arrowrepeattimer, ARROW_REPEATTIMER, &keydownUp, &keydownDown, &keydownLeft, &keydownRight);

			if (tab == RECENTS) {
				filetype = namelist[cursor][9];
			}
			if kb_IsDown(kb_KeyClear) {return "1";}
			if (kb_IsDown(kb_KeyYequ) || kb_IsDown(kb_Key2nd) || kb_IsDown(kb_KeyEnter)) {
				*outfiletype = filetype;
				uint8_t rec = ti_Open(RECENTS_FILENAME, "a");
				ti_Rewind(rec);
				int a = ti_GetC(rec) + 1;
				ti_Rewind(rec);
				ti_PutC(a > ITEM_COUNT ? ITEM_COUNT : a, rec);
				ti_Seek(1, SEEK_SET, rec);
				char d[ITEM_COUNT * 10];
				ti_Read(d, ITEM_COUNT * 10, 1, rec);
				ti_Seek(11, SEEK_SET, rec);
				ti_Write(d, ITEM_COUNT * 10, 1, rec);
				ti_Seek(1, SEEK_SET, rec);
				ti_Write(namelist[cursor], 10, 1, rec);
				if (tab != RECENTS) {
					ti_Seek(10, SEEK_SET, rec);
					ti_Write(&filetype, 1, 1, rec);
				}
				ti_Close(rec);
				return namelist[cursor];
			}
			if (arrowkeys & 1<<2) {
				tab--; 
				if (tab < -1) {tab = -1;}
				break;
			}
			if (arrowkeys & 1<<3) {
				tab++;
				if (tab >= TAB_COUNT) {tab = TAB_COUNT-1;}
				break;
			}

			if (arrowkeys & 1<<1) {cursor++;}
			if (arrowkeys & 1<<0) {cursor--;}

			if (cursor < scroll) {scroll--;}
			if (cursor > 1000) {cursor = namelistsize - 1; scroll = namelistsize >= ITEM_COUNT ? cursor - ITEM_COUNT : scroll;}
			if (namelist[cursor][0] == '\0') {cursor = 0; scroll = 0;}
			if (cursor > scroll + ITEM_COUNT - 1) {scroll++;}

			//while (!kb_AnyKey());
		}

		delay(100);
	}

	return "0"; //namelist[cursor];
}
