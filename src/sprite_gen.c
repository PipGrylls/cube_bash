//
// Created by Philip Grylls on 10/08/2022.
//

#include "sprite_gen.h"
#include "gamestate.h"

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


static inline dynamics makeDynamics(int xa, int ya, int xv, int yv, LCDSprite* s)
{
    float yp, xp;
    playdate->sprite->getPosition(s, &xp, &yp);
    return (dynamics){.x_acc = xa, .y_acc = ya, .x_vel = xv, .y_vel = yv, .x_pos = &xp, .y_pos = &yp};
}

static inline playerStruct playerStructMake(LCDSprite* s)
{
    return (playerStruct){ .playerSprite = s, .playerDynamics = makeDynamics(0,0,0,0,s)};
}

playerStruct createPlayer(int startX, int startY)
{
    // create the player
    LCDSprite *playerCubeSprite = playdate->sprite->newSprite();
    // give the sprite an update
    playdate->sprite->setUpdateFunction(playerCubeSprite, updatePlayer);

    // load and push the image to the sprite
    LCDBitmap *square = loadImageAtPath("images/square");
    int w, h;
    playdate->graphics->getBitmapData(square, &w, &h, NULL, NULL, NULL);

    playdate->sprite->setImage(playerCubeSprite, square, kBitmapUnflipped);

    PDRect cr = PDRectMake(5, 5, w, h);
    playdate->sprite->setCollideRect(playerCubeSprite, cr);
    playdate->sprite->setCollisionResponseFunction(playerCubeSprite, playerCollisionResponse);

    playdate->sprite->moveTo(playerCubeSprite, startX, startY);

    playdate->sprite->setZIndex(playerCubeSprite, 1000);
    playdate->sprite->addSprite(playerCubeSprite);

    playdate->sprite->setTag(playerCubeSprite, kPlayer);

    // Sprite is set up now assign it to a struct that contains the custom attributes

    playerStruct playerCube = playerStructMake(playerCubeSprite);

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

    playdate->sprite->setTag(passiveCube, kNPC);

    return passiveCube;
}