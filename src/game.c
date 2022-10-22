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

    // Check the buttons and update the dynamics of the player
    // pressing any button will increase the acceleration in that direction
    // GOAL: Speeding up should feel 'snowballey' stopping should be snappy.
    if (current & kButtonRight){
        player.playerDynamics.x_acc +=1;
    }
    if (current & kButtonLeft){
        player.playerDynamics.y_acc -=1;
    }

    if (current & kButtonUp){
        player.playerDynamics.y_acc +=1;
    }
    if (current & kButtonDown){
        player.playerDynamics.y_acc -=1;
    }
    // If the player presses (B) they should come quickly to a stop.
    if (current & kButtonB){
        player.playerDynamics.x_acc = 0;
        player.playerDynamics.y_acc = 0;
        player.playerDynamics.x_vel -=5;
        player.playerDynamics.y_vel -=5;
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