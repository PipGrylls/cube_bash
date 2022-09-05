//
//  game.c
//  Extension OS X
//
//  Created by Philip Grylls on 9/08/22.
//  CCby
//

#include "game.h"
#include "gamestate.h"
#include "sprite_gen.h"

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
}


// game initialization
void setupGame(void)
{

    player = createPlayer(100, 100);

    npc = createPassive(250,200);
}

// update loop
int update(void* ud)
{
    checkButtons();
    checkCrank();

    playdate->sprite->updateAndDrawSprites();

    return 1;
}