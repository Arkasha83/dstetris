#pragma once

#include <nds.h>

u8 emptyTile[64] = 
{
	1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1
};
 
u8 fullTile[64] = 
{
	2,2,2,2,2,2,2,2,
	2,2,2,2,2,2,2,2,
	2,2,2,2,2,2,2,2,
	2,2,2,2,2,2,2,2,
	2,2,2,2,2,2,2,2,
	2,2,2,2,2,2,2,2,
	2,2,2,2,2,2,2,2,
	2,2,2,2,2,2,2,2
};

u16* mapMemory;
int MapCols;
int MapRows;

void P_Map16x16_Init( int cols, int rows )
{

    MapCols=cols;
    MapRows=rows;
	//get the address of the tile and map blocks 
	u8* tileMemory = (u8*)BG_TILE_RAM(1);
	mapMemory = (u16*)BG_MAP_RAM(0);
	
	//tell the DS where we are putting everything and set 256 color mode and that we are using a 32 by 32 tile map.
	BGCTRL[0] = BG_32x32 | BG_COLOR_256 | BG_MAP_BASE(0) | BG_TILE_BASE(1);
 
	//load our palette
	BG_PALETTE[1] = RGB15(0,0,0);
	BG_PALETTE[2] = RGB15(31,31,0);

	//copy the tiles into tile memory one after the other
	swiCopy(emptyTile, tileMemory, 32);
	swiCopy(fullTile, tileMemory + 64, 32);
	
	//create a map in map memory
	int i;
	for(i = 0; i < 32 * 32; i++)
    	mapMemory[i] = 0;
    	
    //SetMap16x16To(5,true);
    	
    return;
 }
 
 void SetMap16x16To(int index16, bool full)
 {
    int value = full ? 1 : 0;
    //convert index16x16 to 32x32
    //also make it fall right->left rather than top->bottom
    //
    //  0  1  2  3     12  8  4  0
    //  4  5  6  7  => 13  9  5  1
    //  8  9 10 11  => 14 10  6  2
    // 12 13 14 15     15 11  7  3
    
    //switch x and y
    int x = index16 % MapCols;
    int y = index16 / MapCols; 
    //now inverse x
    y = -(y-MapRows+1);
    index16 = x * MapRows + y;
    
    //16x16->32*32 CONVERSION
    int index32;
    index32 =  index16*2;
    index32 += (index16/16)*32;
    mapMemory[index32] = value;
    mapMemory[index32+1] = value;
    mapMemory[index32+32] = value;
    mapMemory[index32+32+1] = value;
 }