/**
 * --------------------------------------
 *
 * Hexes Source Code - config.h
 * By StephenM
 * Copyright 2024 - 2026
 * License: GPL-3.0
 *
 * --------------------------------------
**/

#ifndef CONFIG_H
#define CONFIG_H

#include "defines.h"
#include <stdint.h>
#include <stdbool.h>

void load_config(bool headless_has_palette);

void write_config();

void config_menu();

#endif
