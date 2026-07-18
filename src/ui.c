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
#include <stdlib.h>
#include <stdint.h>
#include <keypadc.h>
#include <graphx.h>
#include <sys/timers.h>

/*
void ui_message(int x, int y, int type, char *str) {
	// i'll do it later lmao
}*/


int ui_menu(int x, int y, char *opt, int minopt, int olen, int menusize) {
	uint8_t drawloc = gfx_GetDraw();
	gfx_SetDrawScreen();

	gfx_SetColor(COLORS_FG);
	gfx_FillRectangle(x, y, olen * 8, menusize * 10 + 6);
	gfx_SetColor(COLORS_BG);
	gfx_FillRectangle(x+2, y+2, olen * 8 - 4, menusize * 10 + 2);
	gfx_Rectangle(x, y, olen * 8, menusize * 10 + 6);

	int option = minopt;
	for(;;) {
		kb_Scan();
		if (kb_IsDown(kb_Key2nd) || kb_IsDown(kb_KeyEnter)) {break;}
		if kb_IsDown(kb_KeyUp) {option--;}
		if kb_IsDown(kb_KeyDown) {option++;}
		if (option < minopt) {option = menusize-1;}
		if (option >= menusize) {option = minopt;}

		for (int i = 0; i < menusize; i++) {
			gfx_SetTextTransparentColor(MAGENTA);
			gfx_SetTextFGColor(i == option ? COLORS_BG : COLORS_FG);
			gfx_SetTextBGColor(i == option ? COLORS_FG : COLORS_BG);
			gfx_PrintStringXY(opt + i * olen, x + 4, y + 4 + i * 10);
		}

		delay(80); // delay because its too fuckin fast to control otherwise
	}

	gfx_SetDraw(drawloc);
	return option;
}
