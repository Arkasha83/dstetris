#include <stdlib.h>
#include <nds.h>
#include <nds/arm9/image.h>

//include our ball pcx file (auto generated)
#include "ball_pcx.h"

#define NUM_SPRITES 8	

SpriteEntry OAMCopySub[NUM_SPRITES];

tOAM OAMCopySub1;

//simple sprite struct
typedef struct {
	int x,y;			// screen co-ordinates 
	SpriteEntry* oam;	// pointer to the sprite attributes in OAM
	int gfxID; 			// graphics lovation
}Sprite;

Sprite sprites[NUM_SPRITES];




//---------------------------------------------------------------------------------
void initOAM(void) {
//---------------------------------------------------------------------------------
	int i;

	for(i = 0; i < NUM_SPRITES; i++) {
		OAMCopySub[i].attribute[0] = ATTR0_DISABLED;
	}	
}

//---------------------------------------------------------------------------------
void updateOAM(void) {
//---------------------------------------------------------------------------------
	unsigned int i;
	
	for(i = 0; i < NUM_SPRITES * sizeof(SpriteEntry) / 4 ; i++)
	{
		((uint32*)OAM_SUB)[i] = ((uint32*)OAMCopySub)[i];
	}
}
