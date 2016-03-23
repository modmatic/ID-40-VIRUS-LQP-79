#ifndef PLAYER_H
#define PLAYER_H

#include <Arduino.h>
#include "bitmaps.h"
#include "bullet.h"
#include "elements.h"
#include "enemies.h"

extern int mapPositionX;
extern int mapPositionY;

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

#define PLAYER_SCREEN_XMIN        (64-12)
#define PLAYER_SCREEN_XMAX        (64+4)
#define PLAYER_SCREEN_YMIN        (32-8)
#define PLAYER_SCREEN_YMAX        (32-8)

#define PLAYER_FLASH_TIME 60


// structures ////////////////////////////////////////////////////////////////

struct Player
{
  public:
    boolean walking;
    byte direction;
    byte frame;
    byte shotDelay;
    int x;
    int y;
    byte health;
    byte flashTime;
    byte camDirection;
    byte diagonalTime;
};


// globals ///////////////////////////////////////////////////////////////////

extern Player coolGirl;
extern int rollingScore;

// method prototypes /////////////////////////////////////////////////////////

void updatePlayer(Player& obj);
void drawPlayer(Player& obj);
void hurtPlayer(Player& obj);
void initializePlayer(Player& obj);
void drawLife(Player& obj);

#endif
