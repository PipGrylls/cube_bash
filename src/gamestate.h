//
// Created by Philip Grylls on 10/08/2022.
//

#ifndef CUBE_BASH_GAMESTATE_H
#define CUBE_BASH_GAMESTATE_H

#include "global.h"

// game state stored here

LCDSprite *player;
LCDSprite *npc;
int sprint_tap;
bool sprint_hold;


typedef enum {
    kPlayer = 0,
    kNPC = 1,
} SpriteType;

void updateGamestate(void);

#endif //CUBE_BASH_GAMESTATE_H
