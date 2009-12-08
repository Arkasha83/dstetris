#pragma once

//taken from http://www.dev-scene.com/NDS/Tutorials_Day_3#Talking_to_the_keypad

#define KEYS_CUR (( ((~REG_KEYINPUT)&0x3ff) | (((~IPC->buttons)&3)<<10) | (((~IPC->buttons)<<6) & (KEY_TOUCH|KEY_LID) ))^KEY_LID)
 
uint32 keysold;
uint32 keys;
 
 
void P_Input_ScanKeys(void) {

	scanKeys();

	keysold = keys;
	keys = keysHeld();
}
 
uint32 P_Input_KeysHeld(void) {
	return keys;
}
 
uint32 P_Input_KeysDown(void) {
	return (keys ^ keysold) & keys;
}

bool P_Input_IsKeyPressed(int key, bool firstTime) {
    if(firstTime)
		return (P_Input_KeysDown() & key) != 0;
    else
		return (P_Input_KeysHeld() & key) != 0;
}
 