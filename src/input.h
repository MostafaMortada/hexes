/**
 * --------------------------------------
 *
 * Hexes Source Code - input.h
 * By StephenM
 * Copyright 2024 - 2026
 * License: GPL-3.0
 *
 * --------------------------------------
**/


#ifndef INPUT_H
#define INPUT_H

#include "defines.h"
#include <keypadc.h>
#include <stdint.h>
#include <stdbool.h>

uint8_t arrow_key_repeat_handler(int *arrowrepeattimerptr, int ARROW_REPEATTIMER, bool *keydownUp, bool *keydownDown, bool *keydownLeft, bool *keydownRight);

/*
 * bluemodifier: if 2nd is pressed
 * uppercase: if alpha is pressed
 * lowercase: if XTthetaN is pressed
 *
 * function returns a char which is the character typed from the keyboard
 */
char keyboard_typing(bool bluemodifier, bool uppercase, bool lowercase);

#endif
