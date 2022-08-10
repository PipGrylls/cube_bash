//
//  main.c
//  Extension
//
//  Created by Philip Grylls on 9/08/22.
//  CCby
//

#include <stdio.h>
#include <stdlib.h>

#include "pd_api.h"

#include "game.h"

#ifdef _WINDLL
__declspec(dllexport)
#endif
int eventHandler(PlaydateAPI* playdate, PDSystemEvent event, uint32_t arg)
{
    if (event == kEventInit)
    {
        setPDPtr(playdate);
        // Note: This kills LUA and runs the game in C
        playdate->system->setUpdateCallback(update, playdate);
        setupGame();
    }

    return 0;
}