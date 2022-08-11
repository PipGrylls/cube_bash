//
//  game.c
//  Extension OS X
//
//  Created by Philip Grylls on 9/08/22.
//  CCby
//

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "game.h"
#include "game_state.h"
#include "sprite_control.h"
#include "pd_api.h"

static PlaydateAPI* playdate = NULL;

void setPDPtr(PlaydateAPI* p) {
    playdate = p;
}

// inputs
void checkCrank(void)
{
    float change = playdate->system->getCrankChange();
}

void checkButtons(void)
{
    PDButtons pushed;
    PDButtons released;
    PDButtons current;
    playdate->system->getButtonState(&current, &pushed, &released);

    if (current & kButtonA ) {
        sprint_hold = true;
    }
    if (released & kButtonA) {
        sprint_hold = false;
    }
}


// game initialization
void setupGame(void)
{
    player = createPlayer(100, 100);
}

// update loop
int update(void* ud)
{
    checkButtons();
    checkCrank();

    playdate->sprite->updateAndDrawSprites();

    return 1;
}