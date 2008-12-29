#pragma once

#include <nds.h>

enum Console_Type
{
    DEMO,
    DEFAULT,
};

void P_ConsoleInit(enum Console_Type t)
{
    switch(t)
    {
        case DEMO:
            //consoleDemoInit();
            break;
        case DEFAULT:
            //consoleDemoInit();
            break;
    }
}

