//
// Created by Philip Grylls on 10/08/2022.
//
#include <stdio.h>
#include <stdbool.h>

#include "gamestate.h"

LCDSprite *player = NULL;
LCDSprite *npc = NULL;
int sprint_tap = false;
bool sprint_hold = true;


void getMovement(LCDSprite* s, int *xAcl, int *yAcl) {

}

void movePassive(LCDSprite* NPC, int x_vel, int y_vel)
{
    float x, y;
    playdate->sprite->getPosition(NPC, &x, &y);

    int len;
    SpriteCollisionInfo *cInfo = playdate->sprite->moveWithCollisions(NPC, x + x_vel, y + y_vel, NULL, NULL, &len);

    int i;
    for ( i = 0; i < len; i++ )
    {
        SpriteCollisionInfo info = cInfo[i];
        if ( playdate->sprite->getTag(info.other) == kNPC ) {
            movePassive(info.other, x_vel, y_vel);
        }
        if ( playdate->sprite->getTag(info.other) == kPlayer ) {
            movePlayer(info.other, x_vel, y_vel);
        }
    }

}

void movePlayer(LCDSprite* Player, int x_vel, int y_vel)
{
    // Nothing yet
}


void updatePlayer(LCDSprite* s)
{
    // Get any buttons currently held or pushed in the last cycle
    PDButtons current;
    PDButtons pushed;
    playdate->system->getButtonState(&current, &pushed, NULL);

    int dx = 0;
    int dy = 0;

    // Cycle over the buttons to get the state
    if (current & kButtonUp || pushed & kButtonUp){
        dy -= 1;
    }
    if (current & kButtonDown || pushed & kButtonDown){
        dy += 1;
    }
    if (current & kButtonRight || pushed & kButtonRight){
        dx += 1;
    }
    if (current & kButtonLeft || pushed & kButtonLeft){
        dx -= 1;
    }

    if (sprint_tap) {
        dx *= 8;
        dy *= 8;
    }
    if (sprint_hold) {
        dx *= 2;
        dy *= 2;
    }


    float x, y;
    playdate->sprite->getPosition(s, &x, &y);

    int len;
    SpriteCollisionInfo *cInfo = playdate->sprite->moveWithCollisions(s, x + dx, y + dy, NULL, NULL, &len);

    int i;
    for ( i = 0; i < len; i++ )
    {
        SpriteCollisionInfo info = cInfo[i];

        if ( playdate->sprite->getTag(info.other) == kNPC ) {
            movePassive(info.other, dx, dy);
        }
    }

}

void updatePassive(LCDSprite* s)
{

}


void