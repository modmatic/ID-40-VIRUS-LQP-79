#ifndef ENEMIES_H
#define ENEMIES_H

#include <Arduino.h>
#include "globals.h"
#include "bitmaps.h"
#include "player.h"

// constants /////////////////////////////////////////////////////////////////

#define ENEMY_FACING_SOUTH       0
#define ENEMY_FACING_WEST        1
#define ENEMY_FACING_NORTH       2
#define ENEMY_FACING_EAST        3

#define ZOMBIE_FRAME_SKIP        6
#define ZOMBIE_FRAME_COUNT       4
#define ZOMBIE_MAX               16
#define ZOMBIE_WIDTH             16
#define ZOMBIE_HEIGHT            16

#define ZOMBIE_SPEED             1

// structures ////////////////////////////////////////////////////////////////

struct Enemy
{
  public:
    int x;
    int y;
    boolean walking;
    byte direction;
    byte health;
    byte active;
};

// globals ///////////////////////////////////////////////////////////////////

extern Enemy zombies[ZOMBIE_MAX];


// method prototypes /////////////////////////////////////////////////////////

void setZombie(Enemy& obj, int x, int y);
void addZombie(int x, int y);
void updateZombie(Enemy& obj);
void updateZombies();
void drawZombies();
bool zombieHealthOffset(Enemy& obj, char amount);
bool zombieCollision(byte id, int x, int y, int w, int h);
void clearZombies();

#endif
