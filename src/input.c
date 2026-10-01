/**
 * --------------------------------------
 *
 * Hexes Source Code - input.c
 * By StephenM
 * Copyright 2024 - 2026
 * License: GPL-3.0
 *
 * --------------------------------------
**/

#include "input.h"

uint8_t arrow_key_repeat_handler(int *arrowrepeattimerptr, int ARROW_REPEATTIMER, bool *keydownUp, bool *keydownDown, bool *keydownLeft, bool *keydownRight) {
	bool prevkeydownUp = *keydownUp;
	bool prevkeydownDown = *keydownDown;
	bool prevkeydownLeft = *keydownLeft;
	bool prevkeydownRight = *keydownRight;
	*keydownUp = kb_IsDown(kb_KeyUp);
	*keydownDown = kb_IsDown(kb_KeyDown);
	*keydownLeft = kb_IsDown(kb_KeyLeft);
	*keydownRight = kb_IsDown(kb_KeyRight);
	int arrowrepeattimer = *arrowrepeattimerptr;
	uint8_t arrowkeys = 0;
	if (*keydownUp || *keydownDown || *keydownLeft || *keydownRight) {
		arrowkeys =
			(*keydownUp    ? 1 << 0 : 0) |
			(*keydownDown  ? 1 << 1 : 0) |
			(*keydownLeft  ? 1 << 2 : 0) |
			(*keydownRight ? 1 << 3 : 0);
		uint8_t prevmap =
			(prevkeydownUp    ? 1 << 0 : 0) |
			(prevkeydownDown  ? 1 << 1 : 0) |
			(prevkeydownLeft  ? 1 << 2 : 0) |
			(prevkeydownRight ? 1 << 3 : 0);
		if (arrowkeys != prevmap) {
			arrowrepeattimer = 0;
		}
		arrowrepeattimer += 1;
		if (arrowrepeattimer == 1 || arrowrepeattimer > ARROW_REPEATTIMER) {

		} else {
			arrowkeys = 0;
		}
	} else {
		arrowrepeattimer = 0;
	}

	*arrowrepeattimerptr = arrowrepeattimer;
	return arrowkeys;
}

char keyboard_typing(bool bluemodifier, bool uppercase, bool lowercase) {
	char pressed = 0;
	bool s = bluemodifier; // shift / 2nd
	bool u = uppercase; // uppercase (duh)
	bool l = lowercase; // lowercase (duh)
	bool k[] = { // Long ass keyboard map with key combinations for most characters in the ASCII table
	// Ignore the weird indentation
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

	return pressed;
}
