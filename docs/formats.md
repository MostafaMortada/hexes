# Formats

--------------------

## Appvar HEXESCFG

| Offset | Size | Description                                                      |
| ------ | ---- | ---------------------------------------------------------------- |
| 0x00   | 8    | Color palette data                                               |
| 0x08   | 1    | `modifier_key_options_t modkeybehavior;`                         |
| 0x09   | 1    | Use decimal or hexadecimal addresses (0x00 or 0x01 respectively) |

--------------------

## Appvar HEXESRCN

| Offset         | Size | Description               |
| -------------- | ---- | ------------------------- |
| 0x00           | 1    | Number of entries (`n`)   |
| The following section is repeated `n` times.      |
| 0x01 + 10(n-1) | 9    | Null-terminated file name |
| 0x0A + 10(n-1) | 1    | File type                 |

--------------------

## Ans Format for Headless Start

This format is originally from Captain Calc's HexaEdit, which was implemented exactly
in Hexes for compatibility purposes. See https://github.com/captain-calc/HexaEdit-CE#headless-start
for the specifications of this format.
