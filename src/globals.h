/**
 * --------------------------------------
 *
 * Hexes Source Code - globals.h
 * By StephenM
 * Copyright 2024 - 2026
 * License: GPL-3.0
 *
 * --------------------------------------
**/

#ifndef GLOBALS_H
#define GLOBALS_H

#include "defines.h"
#include <stdint.h>
#include <stdbool.h>

extern uint8_t palette[];
extern modifier_key_options_t modkeybehavior;
extern bool hex_addresses;

#define COLORS_BG (palette[0])
#define COLORS_FG (palette[1])
#define COLORS_CURSOR (palette[2])
#define COLORS_NULL (palette[3])
#define COLORS_01_1F (palette[4])
#define COLORS_20_7F (palette[5])
#define COLORS_80_FF (palette[6])

#endif
