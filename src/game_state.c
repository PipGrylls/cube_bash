//
// Created by Philip Grylls on 11/08/2022.
//

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "pd_api.h"

#include "game_state.h"

LCDSprite *player = NULL;
int sprint_tap = 0;
bool sprint_hold = false;