#ifndef ENEMIES_H
#define ENEMIES_H

#include <Arduino.h>

#define PLAYER_FACING_SOUTH       0
#define PLAYER_FACING_WEST        1
#define PLAYER_FACING_NORTH       2
#define PLAYER_FACING_EAST        3


struct Enemy
{
  public:
    int x;
    int y;
    boolean walking;
    byte direction;
    byte frame;
};

Enemy zombie = { .x = 60, .y = 20, .walking = false, .direction = PLAYER_FACING_SOUTH, .frame = 0};

void drawZombies()
{
  sprites.drawPlusMask(zombie.x, zombie.y, zombie_plus_mask, zombie.frame + 4*zombie.direction);
}


#endif
