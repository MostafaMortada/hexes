NAME = HEXES
DESCRIPTION = "A Hex Editor"
ICON = icon.png
COMPRESSED = YES
ARCHIVED = NO
OUTPUT_MAP = NO
CFLAGS = -Wall -Wextra -Oz
CXXFLAGS = -Wall -Wextra -Oz
#MAKE_GFX = cd $(GFXDIR) && $(CONVIMG)

include $(shell cedev-config --makefile)
