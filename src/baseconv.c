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

// Bye bye 768-byte look-up table, you may or may not be missed

char digits[36] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";

char *uint_to_base(unsigned int num, int base, int digitcount) {
	char *buffer = malloc(digitcount + 1); // Thank you TIny_Hacker for showing me the magic of dynamic memory allocation
	unsigned int a = num;
	unsigned int r = 0;
	for (int i = digitcount - 1; i >= 0; i--) {
		r = a % base;
		a = a / base;
		buffer[i] = digits[r];
	}
	buffer[digitcount] = '\0';
	return buffer;
}
