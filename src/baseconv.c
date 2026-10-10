/**
 * --------------------------------------
 *
 * Hexes Source Code - baseconv.c
 * By StephenM
 * Copyright 2024 - 2026
 * License: GPL-3.0
 *
 * --------------------------------------
**/

#include "baseconv.h"
#include <stdlib.h>
#include "globals.h"

// Bye bye 768-byte look-up table, you may or may not be missed

char *uint_to_base(unsigned int num, int base, int digitcount) {
	char digits[72] =
		"0123456789abcdefghijklmnopqrstuvwxyz"
		"0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	char *buffer = malloc(digitcount + 1); // Thank you TIny_Hacker for showing me the magic of dynamic memory allocation
	unsigned int a = num;
	unsigned int r = 0;
	for (int i = digitcount - 1; i >= 0; i--) {
		r = a % base;
		a = a / base;
		buffer[i] = digits[r + 36 * digits_in_uppercase];
	}
	buffer[digitcount] = '\0';
	return buffer;
}
