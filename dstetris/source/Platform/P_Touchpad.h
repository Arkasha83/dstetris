#pragma once

#include <nds.h>

touchPosition TouchPad_GetTouch()
{
	return touchReadXY();
}