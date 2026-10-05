/**
 * --------------------------------------
 *
 * Hexes Source Code - dectohex.c
 * By StephenM
 * Copyright 2024 - 2026
 * License: GPL-3.0
 *
 * --------------------------------------
**/

#include "dectohex.h"
#include <stdlib.h>

// Bye bye 768-byte look-up table, you may or may not be missed

char digits[36] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";

char *uint_to_base(unsigned int num, int base, int digitcount) {
	char *buffer = malloc(digitcount + 1);
	int a = num;
	int r = 0;
	for (int i = 1; i <= digitcount; i++) {
		r = a % base;
		a = a / base;
		buffer[digitcount - i] = digits[r];
	}
	buffer[digitcount] = '\0';
	return buffer;
}
