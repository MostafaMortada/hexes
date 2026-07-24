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
	while (!ret) {
		kb_Scan();
		if (kb_IsDown(kb_Key2nd) || kb_IsDown(kb_KeyEnter)) {ret = true;}
		if (kb_IsDown(kb_KeyClear)) {break;}
		if kb_IsDown(kb_KeyUp) {option-=32;}
		if kb_IsDown(kb_KeyDown) {option+=32;}
		if kb_IsDown(kb_KeyLeft) {option--;}
		if kb_IsDown(kb_KeyRight) {option++;}

		for (int i = 0; i < 32; i++) {
			for (int o = 0; o < 8; o++) {
				gfx_SetColor(o * 32 + i);
				gfx_FillRectangle(10 * i, 10 * o, 10, 10);
				if (option == o * 32 + i) {
					gfx_SetColor(COLORS_CURSOR);
					gfx_Rectangle(10 * i, 10 * o, 10, 10);
				}
			}
		}

		delay(24); // delay because its too fuckin fast to control otherwise
	}

	gfx_SetDraw(drawloc);
	if (ret) {
		return option;
	} else {
		return color;
	}
}
