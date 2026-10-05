# Hexes Hex Editor v2

---

for the TI-84 Plus CE, TI-83 Premium CE, and their derivatives.

By Mostafa Mortada (StephenM)

Forum topic: https://ceme.tech/t19975

---

## What is this?

This is a C rewrite of my 'old' hex editor of the same name, which was written in the ICE programming language.
It was buggy, hard to use, and overall just not something I would personally use as a hex editor. So, I decided to finally rewrite this in C. So far so good. I've been documenting my progress on the Cemetech forum, you can find the link to the topic at the top of this .MD file.

---

## Building & Installation

Just run `make`, and transfer `bin/HEXES.8xp` to your CE calculator with whatever linking software you prefer, like TI-Connect CE, TiLP, WebTiLP, etc...

**DISCLAIMER**, For any versions of TI-OS >= 5.5, you need to either use arTIfiCE or a shell, like Cesium or CEaShell, to run this utility.

---

## How to use

### File selection

On program start-up, you'll be given a file menu you can scroll with the up and down arrow keys. Press the left and right arrow keys to change which tab you are viewing (for the different file types). To open the file the cursor is on, press `enter`.

### Editor

Here is the real meat of the program, where you do the actual editing operations.

#### Controls

* Arrow keys: cursor movement
* F keys (top row): menus (see more details below)
* `[mode]`: Switch editing mode

There are 2 editing modes. You can see which one is selected by the green box outlining it.

* In the first mode which the editor launches in, you edit the hex digits directly, using keys `[0]` through `[9]`, and `[math]`, `[apps]`, `[prgm]`, `[x^-1]`, `[sin]`, and `[cos]` for `A`, `B`, `C`, `D`, `E`, and `F` respectively.

* In the second mode, you can type normal ASCII characters with the whole keypad, using modifiers like `[alpha]` for uppercase letters, `[XTθn]` for lowercase, and `[2nd]` for other symbols, as highlighted on the calculator's physical keypad.

Key repeat and delay exist in both modes making the editing experience feel nice and polished.

#### F Key Menus

This part of Hexes has not been finished yet :)

---

## License

Copyright (C) 2024-2026 Mostafa Mortada (StephenM)
Licensed under the GNU General Public License 3.0
