/*---------------------------------------------------------------------------------

	$Id: main.c,v 1.5 2007/10/23 00:46:29 wntrmute Exp $

	Simple console print demo
	-- dovoto

---------------------------------------------------------------------------------*/
#include <nds.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "Platform/PlatformIncludes.h"
#include "Tetris/TetrisDefines.h"
#include "Tetris/TetrisGameplay.h"

int touchpadUsed;
void ReadTouchPad()
{
    scanKeys();

    // Update the touch screen values.
	touchPosition touch;
	touchRead(&touch);

		iprintf("\x1b[6;5HTouch x = %04X, %04X\n", touch.rawx, touch.px);
		iprintf("\x1b[7;5HTouch y = %04X, %04X\n", touch.rawy, touch.py);	

	
	bool validY = touch.py > 87 && touch.py < 3240;
	bool topY = validY && touch.py < 1600;
	bool botY = validY && touch.py > 1710;
	bool downButtonX = touch.px > 280 && touch.px < 1000;
	bool strafeButtonX = touch.px > 1078 && touch.px < 1834;
	bool rotateButtonX = touch.px > 1918 && touch.px < 2660;
	
    if( validY && downButtonX )
    {
        if(touchpadUsed == 0)
            Gameplay_handleInput(SELECT); 
            
        touchpadUsed = 1;
    }
    else if( validY && strafeButtonX )
    {
        if(touchpadUsed == 0 && (topY || botY))
            Gameplay_handleInput(topY?LEFT:RIGHT); 
            
        touchpadUsed = 1;
    }
	else if( validY && rotateButtonX )
    {
        if(touchpadUsed == 0 && (topY || botY))
            Gameplay_handleInput(topY?UP:DOWN); 
            
        touchpadUsed = 1;
    }
	else
	{
    	touchpadUsed = 0;
	}
}

//link between hardware presses and software logic
//right now if multiple buttons are pressed, only the first one is considered and the others will have to be repressed
void FirePlayerInput()
{
    P_Input_ScanKeys();
    
    if(P_Input_IsKeyPressed(KEY_START, true)
        || P_Input_IsKeyPressed(KEY_A, true))
        Gameplay_handleInput(SELECT);
    else if(P_Input_IsKeyPressed(KEY_SELECT, true)
        || P_Input_IsKeyPressed(KEY_B, true))
        Gameplay_handleInput(EXIT);
    else if(P_Input_IsKeyPressed(KEY_L, true)
        || P_Input_IsKeyPressed(KEY_LEFT, true))
        Gameplay_handleInput(UP); //normal since ds has to be played sideways
    else if(P_Input_IsKeyPressed(KEY_R, true)
        || P_Input_IsKeyPressed(KEY_RIGHT, true))
        Gameplay_handleInput(DOWN); //normal since ds has to be played sideways
    else if(P_Input_IsKeyPressed(KEY_UP, true))
        Gameplay_handleInput(LEFT); //normal since ds has to be played sideways
    else if(P_Input_IsKeyPressed(KEY_DOWN, true))
        Gameplay_handleInput(RIGHT); //normal since ds has to be played sideways
    else
        ReadTouchPad();
}

//---------------------------------------------------------------------------------
int main(void) {
//---------------------------------------------------------------------------------
	
    P_InitNDS();
    
    srand( clock() );
	Gameplay_Load();
	touchpadUsed = 0;
    int loops = 0;
	while( true ) {

		iprintf("\x1b[0;0H  Score %03d \n", Gameplay_playerScore);
		iprintf("\n  Next : ");
		
		FirePlayerInput();
		Gameplay_update();
		Gameplay_draw();
		swiWaitForVBlank();
		loops++;
	}

	return 0;
}