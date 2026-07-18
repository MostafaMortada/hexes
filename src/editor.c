/**
 * --------------------------------------
 *
 * Hexes Source Code - editor.c
 * By StephenM
 * Copyright 2024 - 2026
 * License: GPL-3.0
 *
 * --------------------------------------
**/

#include "editor.h"
#include "defines.h"
#include <stdlib.h>
#include <stdint.h>
#include <fileioc.h>
#include <keypadc.h>
#include <graphx.h>
#include "dectohex.h"
#include "ui.h"

#define FRAMETIMER_BUF_START 50
#define EDIT_REPEATTIMER 12

int start_editor(char *filename, uint8_t filetype) {

	bool full_redraw = true;

	uint24_t cursor_o = 0; // Cursor offset in file
	uint24_t scroll = 0;
	uint8_t nibble = 0;

	int tab = 1; // 0 for editing hex digits, 1 for editing ascii

	int frametimer = 0;
	int repeattimer = 0;

	bool modified = false;

	//gfx_SetPalette(xlibc, 256, 0);
	gfx_SetTransparentColor(MAGENTA);
	gfx_SetTextTransparentColor(1);

	gfx_FillScreen(COLORS_BG);

	gfx_SetTextFGColor(COLORS_FG);
	gfx_SetTextBGColor(COLORS_BG);

	gfx_SetMonospaceFont(8);

	uint8_t buf_h = ti_Open(BUFFER_FILENAME, "r+");

	uint24_t frame = 0; // idk why this is here, probably leftover from BloxorzCE's code which I used as a baseline for this project for some fuckin reason

	gfx_SetDrawBuffer();

	for (;;) {
		kb_Scan();
		bool wanna_quit = false;

		if (frametimer > FRAMETIMER_BUF_START) {
			if kb_IsDown(kb_KeyClear) {wanna_quit = true;}

			if kb_IsDown(kb_KeyYequ) {
				full_redraw = true;
				int option = ui_menu(2, 190,
					"Save      \0"
					"Quit      \0"
					"Close menu\0",
				0, 11, 3);
				switch (option) {
					case 0:
						modified = false;
						break;
					case 1:
						wanna_quit = true;
						break;
					default:
						break;
				}
			}

			if kb_IsDown(kb_KeyWindow) {
				full_redraw = true;
				int option = ui_menu(48, 190,
					"Option 1  \0"
					"Option 2  \0"
					"Close menu\0",
				0, 11, 3);
				switch (option) {
					case 0:
						break;
					case 1:
						break;
					default:
						break;
				}
			}

			if kb_IsDown(kb_KeyZoom) {
				full_redraw = true;
				int option = ui_menu(100, 190,
					"Option 1     \0"
					"Customization\0"
					"Close menu   \0",
				0, 14, 3);
				switch (option) {
					case 0:
						break;
					case 1:
						break;
					default:
						break;
				}
			}

			if kb_IsDown(kb_KeyTrace) {
				full_redraw = true;
				int option = ui_menu(180, 190,
					"Go to address\0"
					"Option 2     \0"
					"Close menu   \0",
				0, 14, 3);
				switch (option) {
					case 0:
						break;
					case 1:
						break;
					default:
						break;
				}
			}

			if kb_IsDown(kb_KeyGraph) {
				full_redraw = true;
				int option = ui_menu(206, 180,
					"About        \0"
					"General usage\0"
					"Other actions\0"
					"Close menu   \0",
				0, 14, 4);
				switch (option) {
					case 0:
						break;
					case 1:
						break;
					default:
						break;
				}
			}
		}

		uint24_t cursor_o_previous = cursor_o;
		if kb_IsDown(kb_KeyUp) {cursor_o-=8;}
		if kb_IsDown(kb_KeyDown) {cursor_o+=8;}
		if kb_IsDown(kb_KeyLeft) {cursor_o--;}
		if kb_IsDown(kb_KeyRight) {cursor_o++;}

		if (cursor_o > 0xFFFFF0) {cursor_o = 0;}
		if (cursor_o >= ti_GetSize(buf_h)) {cursor_o = ti_GetSize(buf_h) - 1;}
		if (cursor_o < scroll*8) {scroll--; full_redraw = true;}
		if (cursor_o >= (scroll + 21)*8) {scroll++; full_redraw = true;}

		if (cursor_o != cursor_o_previous) {nibble = 0;}

		if (tab == 0) {
			int num = -1;
			if kb_IsDown(kb_Key0) {num = 0;}
			else if kb_IsDown(kb_Key1) {num = 1;}
			else if kb_IsDown(kb_Key2) {num = 2;}
			else if kb_IsDown(kb_Key3) {num = 3;}
			else if kb_IsDown(kb_Key4) {num = 4;}
			else if kb_IsDown(kb_Key5) {num = 5;}
			else if kb_IsDown(kb_Key6) {num = 6;}
			else if kb_IsDown(kb_Key7) {num = 7;}
			else if kb_IsDown(kb_Key8) {num = 8;}
			else if kb_IsDown(kb_Key9) {num = 9;}
			else if kb_IsDown(kb_KeyMath) {num = 10;}
			else if kb_IsDown(kb_KeyApps) {num = 11;}
			else if kb_IsDown(kb_KeyPrgm) {num = 12;}
			else if kb_IsDown(kb_KeyRecip) {num = 13;}
			else if kb_IsDown(kb_KeySin) {num = 14;}
			else if kb_IsDown(kb_KeyCos) {num = 15;}
			if (num != -1) {
				repeattimer++;
				if (repeattimer == 1 || repeattimer > EDIT_REPEATTIMER) {
				modified = true;
				ti_Seek(cursor_o, SEEK_SET, buf_h);
				uint8_t c;
				ti_Read(&c, 1, 1, buf_h);
				ti_Seek(-1, SEEK_CUR, buf_h);
				if (nibble == 0) {
					c = (c & 0x0F) | (num << 4);
					nibble = 1;
				} else {
					c = (c & 0xF0) | num;
					nibble = 0;
					cursor_o++;
				}
				ti_Write(&c, 1, 1, buf_h);
				}
			} else {
				repeattimer = 0;
			}
		} else if (tab == 1) {
			char pressed = 0;
			bool s = kb_IsDown(kb_Key2nd);
			bool u = kb_IsDown(kb_KeyAlpha); // uppercase
			bool l = kb_IsDown(kb_KeyGraphVar); // lowercase
			bool k[] = {
				0, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0,
				0, 0, 0, 0, 0, 0, 0, 0,
				kb_IsDown(kb_Key0) && (u||l) && !s, // space
				kb_IsDown(kb_KeyChs) && l && !u && !s, // !
				kb_IsDown(kb_KeyAdd) && u && !l && !s, // "
				0, // #
				0, // $
				0, // %
				0, // &
				kb_IsDown(kb_KeyAdd) && l && !u && !s, // '
				kb_IsDown(kb_KeyLParen) && !(u||l||s), // (
				kb_IsDown(kb_KeyRParen) && !(u||l||s), // )
				kb_IsDown(kb_KeyMul) && !(u||l||s), // *
				kb_IsDown(kb_KeyAdd) && !(u||l||s), // +
				kb_IsDown(kb_KeyComma) && !(u||l||s), // ,
				kb_IsDown(kb_KeySub) && !(u||l||s), // -
				kb_IsDown(kb_KeyDecPnt) && !(u||l||s), // .
				kb_IsDown(kb_KeyDiv) && !(u||l||s), // /
				kb_IsDown(kb_Key0) && !(u||l||s), // 0
				kb_IsDown(kb_Key1) && !(u||l||s), // 1
				kb_IsDown(kb_Key2) && !(u||l||s), // 2
				kb_IsDown(kb_Key3) && !(u||l||s), // 3
				kb_IsDown(kb_Key4) && !(u||l||s), // 4
				kb_IsDown(kb_Key5) && !(u||l||s), // 5
				kb_IsDown(kb_Key6) && !(u||l||s), // 6
				kb_IsDown(kb_Key7) && !(u||l||s), // 7
				kb_IsDown(kb_Key8) && !(u||l||s), // 8
				kb_IsDown(kb_Key9) && !(u||l||s), // 9
				kb_IsDown(kb_KeyDecPnt) && u && !l && !s, // :
				kb_IsDown(kb_KeyDecPnt) && l && !u && !s, // ;
				0, // <
				0, // =
				0, // >
				kb_IsDown(kb_KeyChs) && u && !l && !s, // ?
				0, // @
				kb_IsDown(kb_KeyMath) && u && !l && !s, // A
				kb_IsDown(kb_KeyApps) && u && !l && !s, // B
				kb_IsDown(kb_KeyPrgm) && u && !l && !s, // C
				kb_IsDown(kb_KeyRecip) && u && !l && !s, // D
				kb_IsDown(kb_KeySin) && u && !l && !s, // E
				kb_IsDown(kb_KeyCos) && u && !l && !s, // F
				kb_IsDown(kb_KeyTan) && u && !l && !s, // G
				kb_IsDown(kb_KeyPower) && u && !l && !s, // H
				kb_IsDown(kb_KeySquare) && u && !l && !s, // I
				kb_IsDown(kb_KeyComma) && u && !l && !s, // J
				kb_IsDown(kb_KeyLParen) && u && !l && !s, // K
				kb_IsDown(kb_KeyRParen) && u && !l && !s, // L
				kb_IsDown(kb_KeyDiv) && u && !l && !s, // M
				kb_IsDown(kb_KeyLog) && u && !l && !s, // N
				kb_IsDown(kb_Key7) && u && !l && !s, // O
				kb_IsDown(kb_Key8) && u && !l && !s, // P
				kb_IsDown(kb_Key9) && u && !l && !s, // Q
				kb_IsDown(kb_KeyMul) && u && !l && !s, // R
				kb_IsDown(kb_KeyLn) && u && !l && !s, // S
				kb_IsDown(kb_Key4) && u && !l && !s, // T
				kb_IsDown(kb_Key5) && u && !l && !s, // U
				kb_IsDown(kb_Key6) && u && !l && !s, // V
				kb_IsDown(kb_KeySub) && u && !l && !s, // W
				kb_IsDown(kb_KeySto) && u && !l && !s, // X
				kb_IsDown(kb_Key1) && u && !l && !s, // Y
				kb_IsDown(kb_Key2) && u && !l && !s, // Z
				kb_IsDown(kb_KeyMul) && !(u||l) && s, // [
				kb_IsDown(kb_KeyDiv) && !(u||l) && s, // '\'
				kb_IsDown(kb_KeySub) && !(u||l) && s, // ]
				kb_IsDown(kb_KeyPower) && !(u||l||s), // ^
				kb_IsDown(kb_KeyChs) && !(u||l||s), // _
				0, // `
				kb_IsDown(kb_KeyMath) && !u && l && !s, // a
				kb_IsDown(kb_KeyApps) && !u && l && !s, // b
				kb_IsDown(kb_KeyPrgm) && !u && l && !s, // c
				kb_IsDown(kb_KeyRecip) && !u && l && !s, // d
				kb_IsDown(kb_KeySin) && !u && l && !s, // e
				kb_IsDown(kb_KeyCos) && !u && l && !s, // f
				kb_IsDown(kb_KeyTan) && !u && l && !s, // g
				kb_IsDown(kb_KeyPower) && !u && l && !s, // h
				kb_IsDown(kb_KeySquare) && !u && l && !s, // i
				kb_IsDown(kb_KeyComma) && !u && l && !s, // j
				kb_IsDown(kb_KeyLParen) && !u && l && !s, // k
				kb_IsDown(kb_KeyRParen) && !u && l && !s, // l
				kb_IsDown(kb_KeyDiv) && !u && l && !s, // m
				kb_IsDown(kb_KeyLog) && !u && l && !s, // n
				kb_IsDown(kb_Key7) && !u && l && !s, // o
				kb_IsDown(kb_Key8) && !u && l && !s, // p
				kb_IsDown(kb_Key9) && !u && l && !s, // q
				kb_IsDown(kb_KeyMul) && !u && l && !s, // r
				kb_IsDown(kb_KeyLn) && !u && l && !s, // s
				kb_IsDown(kb_Key4) && !u && l && !s, // t
				kb_IsDown(kb_Key5) && !u && l && !s, // u
				kb_IsDown(kb_Key6) && !u && l && !s, // v
				kb_IsDown(kb_KeySub) && !u && l && !s, // w
				kb_IsDown(kb_KeySto) && !u && l && !s, // x
				kb_IsDown(kb_Key1) && !u && l && !s, // y
				kb_IsDown(kb_Key2) && !u && l && !s, // z
				kb_IsDown(kb_KeyLParen) && !(u||l) && s, // {
				0, // |
				kb_IsDown(kb_KeyRParen) && !(u||l) && s, // }
				0, // ~
				0, // del
			};

			for (int i = 0; i < 128; i++) {
				if (k[i]) {pressed = i; break;}
			}

			if (pressed != 0) {
				repeattimer++;
				if (repeattimer == 1 || repeattimer > EDIT_REPEATTIMER) {
					modified = true;
					ti_Seek(cursor_o, SEEK_SET, buf_h);
					ti_Write(&pressed, 1, 1, buf_h);
					cursor_o++;
				}
			} else {
				repeattimer = 0;
			}
		}


		if (full_redraw) {
			gfx_SetDrawBuffer();
		} else {
			gfx_SetDrawScreen();
		}

		if (full_redraw) {gfx_FillScreen(COLORS_BG);}

		gfx_SetTextBGColor(COLORS_BG);
		gfx_SetTextFGColor(COLORS_FG);
		gfx_SetTextXY(2, 2);
		gfx_PrintString("Hexes   ");
		gfx_PrintString(filename);
		if (modified) {
			gfx_PrintString(" (modified)");
		}

		gfx_PrintStringXY("File", 0, 232);
		gfx_PrintStringXY("Edit", 64, 232);
		gfx_PrintStringXY("View", 132, 232);
		gfx_PrintStringXY("Navigate", 192, 232);
		gfx_PrintStringXY("Help", 288, 232);

		gfx_SetColor(COLORS_FG);
		gfx_HorizLine(0, 229, 320);
		gfx_HorizLine(0, 11, 320);
		gfx_VertLine(70, 11, 218);
		gfx_VertLine(250, 11, 218);

		int row_min = full_redraw ? 0 : (cursor_o / 8) - scroll - 2;
		int row_max = full_redraw ? 21 : (cursor_o / 8) - scroll + 3;
		if (row_min < 0) {row_min = 0;}
		if (row_max > 21) {row_max = 21;}
		ti_Seek((scroll + row_min) * 8, SEEK_SET, buf_h);
		for (uint24_t i = row_min; i < row_max; i++) {
			gfx_SetTextFGColor(COLORS_FG);
			gfx_SetTextXY(2, i*10 + 16);
			gfx_PrintUInt((i+scroll) * 8, 8);
			for (uint24_t o = 0; o < 8; o++) {
				uint24_t offset = (i+scroll)*8+o;
				if (offset < ti_GetSize(buf_h)) {
				bool selected = offset == cursor_o;
				char c;
				ti_Read(&c, 1, 1, buf_h);
				uint8_t num = (uint8_t)c;
				//uint8_t num = *(uint8_t*)b;
				/*if (selected) {
					gfx_SetTextFGColor(COLORS_BG);
				} else*/
				uint8_t color = COLORS_FG;
				if (num == 0) {color = COLORS_NULL;}
				else if (num < 0x20) {color = COLORS_01_1F;}
				else if (num < 0x80) {color = COLORS_20_7F;}
				else {color = COLORS_80_FF;}
				gfx_SetTextFGColor(color);

				/*if (selected) {
					gfx_SetColor(COLORS_CURSOR);
					gfx_Rectangle(83 + o * 20 + nibble * 10, i*10 + 15, 8, 10);
				}*/
				//gfx_SetTextXY(80 + o * 20, i*10 + 16);
				gfx_SetTextXY(84 + o * 20, i*10 + 16);
				char *sub = dec_to_hex_u8b(num);
				if (selected) {
					for (int ch = 0; ch < 2; ch++) {
						if (ch == nibble) {
							gfx_SetTextBGColor(COLORS_CURSOR);
							gfx_SetTextFGColor(COLORS_BG);
						} else {
							gfx_SetTextBGColor(COLORS_BG);
							gfx_SetTextFGColor(color);
						}
						gfx_PrintChar(sub[ch]);
					}
				} else {
					gfx_PrintString(sub);
				}
				if (selected) {
					gfx_SetTextBGColor(COLORS_CURSOR);
					gfx_SetTextFGColor(COLORS_BG);
				}
				gfx_SetTextXY(256 + o * 8, i*10 + 16);
				if (num <= 127) {
					gfx_PrintChar(c);
				} else {
					gfx_PrintChar('.');
				}
				if (selected) { gfx_SetTextBGColor(COLORS_BG); }
				}
			}
		}


		if (full_redraw) {full_redraw = false; gfx_SwapDraw();}

		if (wanna_quit) {
			if (modified) {
				bool will_quit = false;
				switch (ui_menu(8, 8,
						"There are unsaved changes.\0"
						"Do you really wanna quit? \0"
						"No                        \0"
						"Yes                       \0",
					2, 27, 4)) {
					case 3:
						will_quit = true;
						break;
					default:
						break;
				}
				if (will_quit) {break;}
			} else {
				break;
			}
		}

		frametimer++;
		//while (!kb_AnyKey()) {repeattimer = 0; frametimer++;}
	}

	ti_Close(buf_h);

	return 0;
}
