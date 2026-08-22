/**
 * --------------------------------------
 *
 * Hexes Source Code - globals.c
 * By StephenM
 * Copyright 2024 - 2026
 * License: GPL-3.0
 *
 * --------------------------------------
**/

#include "globals.h"

uint8_t palette[PALETTE_SIZE] = {
	0  , // COLORS_BG
	255, // COLORS_FG
	7  , // COLORS_CURSOR
	224, // COLORS_NULL
	241, // COLORS_01_1F
	255, // COLORS_20_7F
	30 , // COLORS_80_FF
	8  , // COLORS_BG2
};

uint8_t ret_text_trans_color() {
	uint8_t a = 0;
	for(;;) {
		uint8_t ap = a;
		for (int i = 0; i < PALETTE_SIZE; i++) {
			if (a == palette[i]) {
				a++;
				break;
			}
		}
		if (ap == a) {break;}
	}
	return a;
}

modifier_key_options_t modkeybehavior = MODIFIER_HOLD;

bool hex_addresses = false;
