#ifndef INPUT_H
#define INPUT_H

#include <Arduino.h>
#include "player.h"

extern Arduboy arduboy;
extern SimpleButtons buttons;
extern Player coolGuy;

#define PLAYER_FACING_SOUTH       0
#define PLAYER_FACING_SOUTHWEST   1
#define PLAYER_FACING_WEST        2
#define PLAYER_FACING_NORTHWEST   3
#define PLAYER_FACING_NORTH       4
#define PLAYER_FACING_NORTHEAST   5
#define PLAYER_FACING_EAST        6
#define PLAYER_FACING_SOUTHEAST   7


void checkInputs()
{
    updatePlayer();
}

#endif
