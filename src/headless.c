/**
 * --------------------------------------
 *
 * Hexes Source Code - headless.c
 * By StephenM
 * Copyright 2024 - 2026
 * License: GPL-3.0
 *
 * --------------------------------------
**/

// This file is a mess
// I'll get back to it later I guess

#include "headless.h"
#include <string.h>

char *check_for_ans(uint8_t *filetype, bool *palette_present) {
	// Reading headless start string. Credits to Captain Calc for this format which he used in HexaEdit, I'm merely copying it.

	uint8_t AnsType;
	void *Ans1 = os_GetAnsData(&AnsType);
	string_t *Ans;
	if (Ans1 != NULL && AnsType == OS_TYPE_STR) {
		//filename_a = Ans;
		Ans = Ans1;
		//printf("Len: %d\n", name->len);
		if (Ans->len < 9 || Ans->len == 0) {
			return "1";
		} else {
			const char headstr[] = "HexaEdit";
			for (int i = 0; i < 8; i++) {
				if (Ans->data[i] != headstr[i]) {
					return "1";
				}
			}

			char flags = Ans->data[8];

			if (flags & (1 << 1)) { // Memory editor
				// do nothing, this doesn't exist in Hexes yet
				return "1";
			}

			if (flags & (1 << 0)) { // Colorscheme present
				/*
				typedef struct
					{
					uint8_t bar;						// index 22 in ans (with variable editor header)
					uint8_t bar_text;					// 23

					// Used for unavailable tools in the editor toolbar.
					uint8_t bar_text_dark;				// 24

					uint8_t background;					// 25
					uint8_t editor_side_panel;			// 26
					uint8_t editor_cursor;				// 27
					uint8_t editor_text_normal;			// 28
					uint8_t editor_text_selected;		// 29
					uint8_t list_cursor;				// 30
					uint8_t list_text_normal;			// 31
					uint8_t list_text_selected;			// 32
				} s_color;

				^^^ This was copied from the HexaEdit readme for me to reference :3
				*/

				*palette_present = true;

				COLORS_BG = Ans->data[25];
				COLORS_BG2 = Ans->data[26];
				COLORS_CURSOR = Ans->data[27];
				COLORS_FG = Ans->data[28];

				// I tried :,)
			}

			if (flags & (1 << 2)) { // Variable editor
				static char filename[9];
				memset(filename, 0, sizeof(filename));
				for (int i = 0; i < Ans->data[17] && i < 8; i++) {
					filename[i] = Ans->data[i + 9];
				}
				*filetype = (uint8_t) Ans->data[18];
				return filename;
			}
		}
	} else {
		return "1";
	}

	return "0";
}
