//
// Created by Philip Grylls on 10/08/2022.
//

#include "sprite_gen.h"
#include "gamestate.h"

static PlaydateAPI* playdate = NULL;

LCDBitmap *loadImageAtPath(const char *path)
{
    const char *outErr = NULL;
    LCDBitmap *img = playdate->graphics->loadBitmap(path, &outErr);
    if ( outErr != NULL ) {
        playdate->system->logToConsole("Error loading image at path '%s': %s", path, outErr);
    }
    return img;
}

static SpriteCollisionResponseType playerCollisionResponse(LCDSprite* sprite, LCDSprite* other)
{
    return kCollisionTypeOverlap;
}

static SpriteCollisionResponseType passiveCollisionResponse(LCDSprite* sprite, LCDSprite* other)
{
    return kCollisionTypeOverlap;
}

static void updatePlayer(LCDSprite* s)
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

    playdate->sprite->moveBy(s, dx, dy);
}

static void updatePassive(LCDSprite* s)
{

}

LCDSprite* createPlayer(int startX, int startY)
{
    // create the player
    LCDSprite *playerCube = playdate->sprite->newSprite();
    // give the sprite an update
    playdate->sprite->setUpdateFunction(playerCube, updatePlayer);

    // load and push the image to the sprite
    LCDBitmap *square = loadImageAtPath("images/square");
    int w, h;
    playdate->graphics->getBitmapData(square, &w, &h, NULL, NULL, NULL);

    playdate->sprite->setImage(playerCube, square, kBitmapUnflipped);

    PDRect cr = PDRectMake(5, 5, w, h);
    playdate->sprite->setCollideRect(playerCube, cr);
    playdate->sprite->setCollisionResponseFunction(playerCube, playerCollisionResponse);

    playdate->sprite->moveTo(playerCube, startX, startY);

    playdate->sprite->setZIndex(playerCube, 1000);
    playdate->sprite->addSprite(playerCube);

    return playerCube;
}

LCDSprite* createPassive(int startX, int startY)
{
    // create the player
    LCDSprite *passiveCube = playdate->sprite->newSprite();
    // give the sprite an update
    playdate->sprite->setUpdateFunction(passiveCube, updatePassive);

    // load and push the image to the sprite
    LCDBitmap *square = loadImageAtPath("images/square");
    int w, h;
    playdate->graphics->getBitmapData(square, &w, &h, NULL, NULL, NULL);

    playdate->sprite->setImage(passiveCube, square, kBitmapUnflipped);

    PDRect cr = PDRectMake(5, 5, w, h);
    playdate->sprite->setCollideRect(passiveCube, cr);
    playdate->sprite->setCollisionResponseFunction(passiveCube, passiveCollisionResponse);

    playdate->sprite->moveTo(passiveCube, startX, startY);

    playdate->sprite->setZIndex(passiveCube, 1000);
    playdate->sprite->addSprite(passiveCube);

    return passiveCube;
}