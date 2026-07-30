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

uint8_t palette[16] = {
	0  , // COLORS_BG
	255, // COLORS_FG
	7  , // COLORS_CURSOR
	224, // COLORS_NULL
	241, // COLORS_01_1F
	255, // COLORS_20_7F
	30   // COLORS_80_FF
};

modifier_key_options_t modkeybehavior = MODIFIER_HOLD;
