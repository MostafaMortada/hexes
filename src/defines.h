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
#include "palette.h"
#include <stdint.h>

#define BUFFER_FILENAME ("HEXESBUF")

//#define max(a, b) ((a) > (b) ? (a) : (b))
//#define min(a, b) ((a) < (b) ? (a) : (b))

// Some colors
#define BLACK	0
#define WHITE	255
#define MAGENTA	248
#define TEST_COLOR 4

// Color scheme

//#define COLORS_BG 0
//#define COLORS_FG 255
//#define COLORS_NULL 224
//#define COLORS_01_1F 241
//#define COLORS_20_7F 255
//#define COLORS_80_FF 30
//#define COLORS_CURSOR 7

#define COLORS_BG (palette[0])
#define COLORS_FG (palette[1])
#define COLORS_CURSOR (palette[2])
#define COLORS_NULL (palette[3])
#define COLORS_01_1F (palette[4])
#define COLORS_20_7F (palette[5])
#define COLORS_80_FF (palette[6])
     
#endif
