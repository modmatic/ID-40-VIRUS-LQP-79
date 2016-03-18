#ifndef ENEMIES_H
#define ENEMIES_H

#include <Arduino.h>

#define PLAYER_FACING_SOUTH       0
#define PLAYER_FACING_WEST        1
#define PLAYER_FACING_NORTH       2
#define PLAYER_FACING_EAST        3

byte maxZombies =0;


struct Enemy
{
  public:
    int x;
    int y;
    boolean walking;
    byte direction;
    byte frame;
};

Enemy zombie[1];

void createZombies(byte zombieCount)
{
  for (byte i =0; i < zombieCount; i++)
  {
    zombie[i].x = 60;
    zombie[i].y = 20;
    zombie[i].walking = false;
    zombie[i].direction = PLAYER_FACING_SOUTH;
    zombie[i].frame = 0;
  }
}

void drawZombies()
{
  if (arduboy.everyXFrames(6)) zombie[0].frame++;
  if (zombie[0].frame > 3 ) zombie[0].frame = 0;
  sprites.drawPlusMask(zombie[0].x, zombie[0].y, zombie_plus_mask, zombie[0].frame + 4*zombie[0].direction);
}


#endif
