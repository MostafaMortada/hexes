/**
 * --------------------------------------
 *
 * Hexes Source Code - ui.c
 * By StephenM
 * Copyright 2024 - 2026
 * License: GPL-3.0
 *
 * --------------------------------------
**/

#include "ui.h"
#include "defines.h"
#include "globals.h"
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <keypadc.h>
#include <graphx.h>
#include <sys/timers.h>

#define ARROW_REPEATTIMER 6

/*
void ui_message(int x, int y, int type, char *str) {
	// i'll do it later lmao
}*/ // actually this function will never be done later cuz i can just do that with the ui_menu function lmao :p


int ui_menu(int x, int y, char *opt, int minopt, int olen, int menusize) {
	uint8_t drawloc = gfx_GetDraw();
	gfx_SetDrawScreen();

	gfx_SetColor(COLORS_FG);
	gfx_FillRectangle(x, y, olen * 8, menusize * 10 + 6);
	gfx_SetColor(COLORS_BG);
	gfx_FillRectangle(x+2, y+2, olen * 8 - 4, menusize * 10 + 2);
	gfx_Rectangle(x, y, olen * 8, menusize * 10 + 6);

	while (kb_AnyKey());

	bool keydownUp = false;
	bool keydownDown = false;
	bool keydownLeft = false;
	bool keydownRight = false;
	int arrowrepeattimer = 0;
	int option = minopt;
	for(;;) {
		kb_Scan();
		bool prevkeydownUp = keydownUp;
		bool prevkeydownDown = keydownDown;
		bool prevkeydownLeft = keydownLeft;
		bool prevkeydownRight = keydownRight;
		keydownUp = kb_IsDown(kb_KeyUp);
		keydownDown = kb_IsDown(kb_KeyDown);
		keydownLeft = kb_IsDown(kb_KeyLeft);
		keydownRight = kb_IsDown(kb_KeyRight);
		uint8_t arrowkeys = 0;
		if (keydownUp || keydownDown || keydownLeft || keydownRight) {
			arrowkeys =
				(keydownUp    ? 1 << 0 : 0) |
				(keydownDown  ? 1 << 1 : 0) |
				(keydownLeft  ? 1 << 2 : 0) |
				(keydownRight ? 1 << 3 : 0);
			uint8_t prevmap =
				(prevkeydownUp    ? 1 << 0 : 0) |
				(prevkeydownDown  ? 1 << 1 : 0) |
				(prevkeydownLeft  ? 1 << 2 : 0) |
				(prevkeydownRight ? 1 << 3 : 0);
			if (arrowkeys != prevmap) {arrowrepeattimer = 0;}
			arrowrepeattimer++;
			if (arrowrepeattimer == 1 || arrowrepeattimer > ARROW_REPEATTIMER) {
				
			} else {
				arrowkeys = 0;
			}
		} else {
			arrowrepeattimer = 0;
		}


		if (kb_IsDown(kb_Key2nd) || kb_IsDown(kb_KeyEnter)) {break;}
		if (arrowkeys & 1<<0) {option--;}
		if (arrowkeys & 1<<1) {option++;}
		if (option < minopt) {option = menusize-1;}
		if (option >= menusize) {option = minopt;}

		for (int i = 0; i < menusize; i++) {
			//gfx_SetTextTransparentColor(MAGENTA);
			gfx_SetTextFGColor(i == option ? COLORS_BG : COLORS_FG);
			gfx_SetTextBGColor(i == option ? COLORS_FG : COLORS_BG);
			gfx_PrintStringXY(opt + i * olen, x + 4, y + 4 + i * 10);
		}

		delay(40); // delay because its too fuckin fast to control otherwise
	}

	gfx_SetDraw(drawloc);
	return option;
}
