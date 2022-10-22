//
// Created by Philip Grylls on 10/08/2022.
//

#ifndef CUBE_BASH_GAMESTATE_H
#define CUBE_BASH_GAMESTATE_H

#include "global.h"


struct dynamics{
    int x_acc, y_acc;
    int x_vel, y_vel;
    //pointers into the sprite position
    float *x_pos, *y_pos;
};

struct playerStruct {
    LCDSprite* playerSprite;
    struct dynamics playerDynamics;
};

// game state stored here

struct playerStruct player;
LCDSprite *npc;
int sprint_tap;
int sprint_hold;


typedef enum {
    kPlayer = 0,
    kNPC = 1,
} SpriteType;

void getMovement(LCDSprite* s);

void movePassive(LCDSprite* NPC, int x_vel, int y_vel);
void movePlayer(LCDSprite* Player, int x_vel, int y_vel);

void updatePlayer(LCDSprite* s);
void updatePassive(LCDSprite* s);

#endif //CUBE_BASH_GAMESTATE_H
