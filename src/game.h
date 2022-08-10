//
//  game.h
//  Extension OS X
//
//  Created by Philip Grylls on 9/08/22.
//  CCby
//

#ifndef game_h
#define game_h

#include <stdio.h>

#include "pd_api.h"

int update(void* ud);
void setPDPtr(PlaydateAPI* p);
void setupGame(void);

#endif /* game_h */