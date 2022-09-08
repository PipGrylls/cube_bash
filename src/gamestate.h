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
int sprint_hold;


typedef enum {
    kPlayer = 0,
    kNPC = 1,
} SpriteType;

void getMovement(LCDSprite* s, int xAcl, int yAcl);

void movePassive(LCDSprite* NPC, int x_vel, int y_vel);
void movePlayer(LCDSprite* Player, int x_vel, int y_vel);

void updatePlayer(LCDSprite* s);
void updatePassive(LCDSprite* s);

#endif //CUBE_BASH_GAMESTATE_H
