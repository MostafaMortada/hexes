/**
 * --------------------------------------
 *
 * Hexes Source Code - colorpicker.c
 * By StephenM
 * Copyright 2024 - 2026
 * License: GPL-3.0
 *
 * --------------------------------------
**/

#include "colorpicker.h"
#include "defines.h"
#include "globals.h"
#include "input.h"

#define ARROW_REPEATTIMER 12

uint8_t colorpicker(uint8_t color) {
	uint8_t drawloc = gfx_GetDraw();
	gfx_SetDrawScreen();

	/*gfx_SetColor(COLORS_FG);
	gfx_FillRectangle(x, y, olen * 8, menusize * 10 + 6);
	gfx_SetColor(COLORS_BG);
	gfx_FillRectangle(x+2, y+2, olen * 8 - 4, menusize * 10 + 2);
	gfx_Rectangle(x, y, olen * 8, menusize * 10 + 6);*/

	uint8_t option = color;
	bool ret = false;

	bool keydownUp;
	bool keydownDown;
	bool keydownLeft;
	bool keydownRight;

	int arrowrepeattimer = 0;

	while (kb_AnyKey());

	while (!ret) {
		kb_Scan();

		uint8_t arrowkeys = arrow_key_repeat_handler(&arrowrepeattimer, ARROW_REPEATTIMER, &keydownUp, &keydownDown, &keydownLeft, &keydownRight);

		if (kb_IsDown(kb_Key2nd) || kb_IsDown(kb_KeyEnter)) {ret = true; break;}
		if (kb_IsDown(kb_KeyClear)) {break;}
		if ((arrowkeys & 1<<0) != 0) {option-=32;}
		if ((arrowkeys & 1<<1) != 0) {option+=32;}
		if ((arrowkeys & 1<<2) != 0) {option--;}
		if ((arrowkeys & 1<<3) != 0) {option++;}

		for (int i = 0; i < 32; i++) {
			for (int o = 0; o < 8; o++) {
				gfx_SetColor(o * 32 + i);
				gfx_FillRectangle(10 * i, 10 * o + 120, 10, 10);
				if (option == o * 32 + i) {
					gfx_SetColor(255 - option);
					gfx_Rectangle(10 * i + 1, 10 * o + 121, 8, 8);
					gfx_Rectangle(10 * i, 10 * o + 120, 10, 10);
				}
			}
		}
		gfx_SetColor(option);
		gfx_FillRectangle(0, 80 + 120, 320, 40);

		delay(12); // delay because its too fuckin fast to control otherwise
	}

	gfx_SetDraw(drawloc);
	if (ret) {
		return option;
	} else {
		return color;
	}
}
