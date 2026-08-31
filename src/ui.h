/**
 * --------------------------------------
 *
 * Hexes Source Code - ui.h
 * By StephenM
 * Copyright 2024 - 2026
 * License: GPL-3.0
 *
 * --------------------------------------
**/

#ifndef UI_H
#define UI_H

#include <keypadc.h>

//void ui_message(int x, int y, int type, char *str);

int ui_menu(int x, int y, char *opt, int minopt, int olen, int menusize, kb_lkey_t exitkey1, kb_lkey_t exitkey2);

#endif
