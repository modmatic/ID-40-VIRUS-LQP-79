#ifndef PLAYER_H
#define PLAYER_H

#include <Arduino.h>
#include "bitmaps.h"
#include "bullet.h"
#include "elements.h"
#include "enemies.h"


// constants /////////////////////////////////////////////////////////////////

#define PLAYER_FACING_SOUTH       0
#define PLAYER_FACING_SOUTHWEST   1
#define PLAYER_FACING_WEST        2
#define PLAYER_FACING_NORTHWEST   3
#define PLAYER_FACING_NORTH       4
#define PLAYER_FACING_NORTHEAST   5
#define PLAYER_FACING_EAST        6
#define PLAYER_FACING_SOUTHEAST   7

#define PLAYER_WIDTH  16
#define PLAYER_HEIGHT 16

// structures ////////////////////////////////////////////////////////////////

struct Player
{
  public:
    int x;
    int y;
    boolean walking;
    byte direction;
    byte frame;
    byte shotDelay;
    short vx;
    short vy;
};


// globals ///////////////////////////////////////////////////////////////////

extern Player coolGuy;


// method prototypes /////////////////////////////////////////////////////////

void updatePlayer(Player& obj);
void drawPlayer(Player& obj);


#endif
