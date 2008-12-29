#pragma once

#include <nds.h>
#include "P_Map16x16.h"
#include "P_Font.h"

#include "bkggreen_img_bin.h"
#include "bkggreen_pal_bin.h"


enum INIT_TYPE
{
    INIT_NORMAL,
};


void P_InitNDS(enum INIT_TYPE t)
{
    //Enable VBLANKS
	irqInit();
	irqEnable(IRQ_VBLANK);

	//point our video buffer to the start of bitmap background video
	P_Graphics_assignBuffer(MAIN, (u16*)BG_BMP_RAM(0),256,192);
	
	//set video mode and map vram to the background
	videoSetMode(MODE_0_2D | DISPLAY_BG0_ACTIVE);
	// 16bit tilemaps for rot scale text backgrounds require extended palettes
	videoSetModeSub(MODE_5_2D | 
					DISPLAY_BG2_ACTIVE | //background
					DISPLAY_BG3_ACTIVE | DISPLAY_BG_EXT_PALETTE //console
					);
	
    vramSetMainBanks(VRAM_A_MAIN_BG_0x06000000, VRAM_B_LCD, VRAM_C_SUB_BG_0x06200000, VRAM_D_LCD); 
					
	P_Map16x16_Init(12,16);
	
	// rot scale backgrounds have a different size code
	P_Font_LoadFontIntoSubLCD();
	
	// set up our bitmap background
	SUB_BG2_CR = BG_BMP8_256x256; 
    SUB_BG2_XDX = 256; 
    SUB_BG2_XDY = 0; 
    SUB_BG2_YDX = 0; 
    SUB_BG2_YDY = 256; 
    SUB_BG2_CX = 0; 
    SUB_BG2_CY = 0; 
	
    dmaCopy(bkggreen_img_bin, BG_GFX_SUB, 256*256); 
    dmaCopy(bkggreen_pal_bin, BG_PALETTE_SUB, 256*2); 
	
}

