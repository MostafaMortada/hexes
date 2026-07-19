#include "headless.h"
#include <string.h>

char *check_for_ans(uint8_t *filetype) {
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

			if (flags & (1 << 0)) { // Colorscheme present
				// uhhh idk do nothing for now
			}

			if (flags & (1 << 1)) { // Memory editor
				// also do nothing, this doesn't exist in Hexes yet
			}

			if (flags & (1 << 2)) { // Variable editor
				char filename[9] = "\0\0\0\0\0\0\0\0\0";
				for (int i = 0; i < Ans->data[17]; i++) {
					filename[i] = Ans->data[i + 9];
				}
				*filetype = (uint8_t) Ans->data[18];
				char *filen = "";
				strcpy(filen, filename);
				return filen;
			}
		}
	} else {
		return "1";
	}

	return "0";
}
