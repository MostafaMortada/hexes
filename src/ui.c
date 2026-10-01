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
#include "input.h"

#define ARROW_REPEATTIMER 6

/*
void ui_message(int x, int y, int type, char *str) {
	// i'll do it later lmao
}*/ // actually this function will never be done later cuz i can just do that with the ui_menu function lmao :p


int ui_menu(int x, int y, char *opt, int minopt, int olen, int menusize, kb_lkey_t exitkey1, kb_lkey_t exitkey2) {
	uint8_t drawloc = gfx_GetDraw();
	gfx_SetDrawScreen();

	if (x == -1) {
		x = 160 - olen * 4;
		y = 120 - menusize * 5 - 3;
	}

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
		uint8_t arrowkeys = arrow_key_repeat_handler(&arrowrepeattimer, ARROW_REPEATTIMER, &keydownUp, &keydownDown, &keydownLeft, &keydownRight);

		if (kb_IsDown(kb_Key2nd) || kb_IsDown(kb_KeyEnter)) {break;}
		if (kb_IsDown(exitkey1) || kb_IsDown(exitkey2)) {option = 255; break;}
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

	while (kb_AnyKey());
	gfx_SetDraw(drawloc);
	return option;
}

void ditherscreen(uint8_t color) {
	gfx_SetColor(color);
	//for (int x = 0; x < 320; x+=4) {
		for (int y = 0; y < 240; y+=2) {
			//gfx_SetPixel(x, y);
			//gfx_SetPixel(x+2, y+1);
			gfx_HorizLine(0, y, 320);
		}
	//}
	return;
}
