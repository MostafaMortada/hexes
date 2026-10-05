/**
 * --------------------------------------
 *
 * Hexes Source Code - baseconv.h
 * By StephenM
 * Copyright 2024 - 2026
 * License: GPL-3.0
 *
 * --------------------------------------
**/

#ifndef BASECONV_H
#define BASECONV_H

// convert unsigned int to any base with any number of digits
// DO NOT FORGET TO USE free() AFTER YOU ARE DONE USING THE OUTPUT OF THIS FUNCTION
char *uint_to_base(unsigned int num, int base, int digitcount);

#endif
