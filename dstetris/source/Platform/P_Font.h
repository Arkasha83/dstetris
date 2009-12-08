
#include <nds/jtypes.h>

#ifndef _font_h_
#define _font_h_

#include "font.h"

void P_Font_LoadFontIntoSubLCD ()
{
	const int tile_base = 0;
	const int map_base = 20;

	PrintConsole *console = consoleInit( 0, 1, BgType_Text4bpp, BgSize_T_256x256, map_base, tile_base, false, false );

	ConsoleFont font;

	font.gfx = (u16*)fontTiles;
	font.pal = (u16*)fontPal;
	font.numChars = 95;
	font.numColors =  fontPalLen / 2;
	font.bpp = 4;
	font.asciiOffset = 32;
	font.convertSingleColor = false;
	
	consoleSetFont(console, &font);
}

#endif // _font_h_