/**
 * --------------------------------------
 *
 * Hexes Source Code - defines.h
 * By StephenM
 * Copyright 2024 - 2026
 * License: GPL-3.0
 *
 * --------------------------------------
**/

#ifndef DEFINES_H
#define DEFINES_H

#include "font.h"
#include <stdint.h>

#define BUFFER_FILENAME ("HEXESBUF")
#define CONFIG_FILENAME ("HEXESCFG")

//#define max(a, b) ((a) > (b) ? (a) : (b))
//#define min(a, b) ((a) < (b) ? (a) : (b))

#define PALETTE_SIZE 8

// Some colors
#define BLACK	0
#define WHITE	255
#define MAGENTA	248
#define TEST_COLOR 4

typedef enum {
	MODIFIER_TOGGLE,
	MODIFIER_TOGGLE_LOCK,
	MODIFIER_HOLD
} modifier_key_options_t;

#endif
