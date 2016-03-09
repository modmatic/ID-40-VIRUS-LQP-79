#ifndef PLAYER_H
#define PLAYER_H

#include <Arduino.h>
#include "bitmaps.h"

extern Arduboy arduboy;
extern Sprites sprites;
extern SimpleButtons buttons;

#define PLAYER_FACING_SOUTH       0
#define PLAYER_FACING_SOUTHWEST   1
#define PLAYER_FACING_WEST        2
#define PLAYER_FACING_NORTHWEST   3
#define PLAYER_FACING_NORTH       4
#define PLAYER_FACING_NORTHEAST   5
#define PLAYER_FACING_EAST        6
#define PLAYER_FACING_SOUTHEAST   7


struct Player
{
  public:
    int x;
    int y;
    boolean walking;
    byte direction;
    byte frame;
};

Player coolGuy = { .x = 20, .y = 20, .walking = false, .direction = PLAYER_FACING_SOUTH, .frame = 0};

void drawPlayer()
{
  if (arduboy.everyXFrames(6) && coolGuy.walking) coolGuy.frame++;
  if (coolGuy.frame > 3 ) coolGuy.frame = 0;
  sprites.drawPlusMask(coolGuy.x, coolGuy.y, player_plus_mask, coolGuy.frame + 4*coolGuy.direction);
}

#endif
