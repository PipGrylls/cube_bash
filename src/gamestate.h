//
// Created by Philip Grylls on 10/08/2022.
//

#ifndef CUBE_BASH_GAMESTATE_H
#define CUBE_BASH_GAMESTATE_H

#include <stdio.h>
#include <stdbool.h>

#include "pd_api.h"

// game state stored here
LCDSprite *player;
LCDSprite *npc;
int sprint_tap;
bool sprint_hold;

void updateGamestate(void);

#endif //CUBE_BASH_GAMESTATE_H
