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

#define VERSION "v2.0.0 BETA"

#define ABOUT \
	"Hexes Hex Editor " VERSION "   \0" \
	"\5 Copyright 2024-2026 StephenM \0" \
	"GNU GPL v3.0 License           \0" \
	"                               \0" \
	"See website at:                \0" \
	"mostafamortada.github.io/hexes \0" \
	"                               \0" \
	"See GitHub repository at:      \0" \
	"github.com/MostafaMortada/hexes\0" \
	"                               \0" \
	"OK                             \0"

#define BUFFER_FILENAME ("HEXESBUF")
#define CONFIG_FILENAME ("HEXESCFG")
#define RECENTS_FILENAME ("HEXESRCN")

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
