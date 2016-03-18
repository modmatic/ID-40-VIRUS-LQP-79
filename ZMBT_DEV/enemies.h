#ifndef ENEMIES_H
#define ENEMIES_H

#include <Arduino.h>

#define PLAYER_FACING_SOUTH       0
#define PLAYER_FACING_WEST        1
#define PLAYER_FACING_NORTH       2
#define PLAYER_FACING_EAST        3

byte zombieFrame = 0;

struct Enemy
{
  public:
    int x;
    int y;
    boolean walking;
    byte direction;
};

Enemy zombie[16];

void createZombies(byte zombieCount)
{
  for (byte i =0; i < zombieCount; i++)
  {
    zombie[i].x = 0;
    zombie[i].y = 40;
    zombie[i].walking = false;
    zombie[i].direction = PLAYER_FACING_SOUTH;
  }
}

void drawZombies(byte zombieCount)
{
  if (arduboy.everyXFrames(6))zombieFrame++;
  if (zombieFrame > 3 ) zombieFrame = 0;
  for (byte i=0; i< zombieCount; i++)
  {
    sprites.drawPlusMask(zombie[i].x+ (i*17), zombie[i].y, zombie_plus_mask, zombieFrame + 4*zombie[i].direction);
  }
  
}


#endif
