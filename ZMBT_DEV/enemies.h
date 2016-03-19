#ifndef ENEMIES_H
#define ENEMIES_H

#include <Arduino.h>
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

Enemy zombies[ZOMBIE_MAX];
byte zombieFrame = 0;
extern Arduboy arduboy;
extern Sprites sprites;


// methods ///////////////////////////////////////////////////////////////////

// setZombie
// sets the position of a zombie, and enables that instance
void setZombie(Enemy& obj, int x, int y)
{
  obj.walking = false;
  obj.active = true;
  obj.direction = ENEMY_FACING_SOUTH;
  obj.x = x;
  obj.y = y;
  obj.health = 3;
}


// addZombie
// searches the zombies list for an empty slot, adds one if available
void addZombie(int x, int y)
{
  byte id;
  
  for(id=0; id<ZOMBIE_MAX; id++)
  {
    if(!zombies[id].active)
    {
      setZombie(zombies[id], x, y);
      break;
    }
  }
}


// updateZombie
// updates the zombie according to game rules
// zombies are "removed" (set inactive) when health reaches zero
void updateZombie(Enemy& obj)
{
  int vx = 0;
  int vy = 0;
  
  //if(obj.x + ZOMBIE_WIDTH < coolGuy.x) vx = -ZOMBIE_SPEED;
  //if(obj.x > coolGuy.x + PLAYER_WIDTH) vx = -ZOMBIE_SPEED;
  
  //if(obj.y + ZOMBIE_HEIGHT < coolGuy.y) vy = -ZOMBIE_HEIGHT;
  //if(obj.y > coolGuy.y + PLAYER_HEIGHT) vy = -ZOMBIE_HEIGHT;
  
  obj.x += vx;
  obj.y += vy;
  
  
  if(obj.health == 0)
  {
    obj.active = false;
  }
}


// updateZombies
// updates every active zombie in the list
void updateZombies()
{
  byte i;
  
  for(i=0; i<ZOMBIE_MAX; i++)
  {
    if(!zombies[i].active) continue;
    updateZombie(zombies[i]);
  }
}


// drawZombies
// draws every active zombie in the zombie list
void drawZombies()
{
  byte id;
  
  // Advance animation frame
  if (arduboy.everyXFrames(ZOMBIE_FRAME_SKIP)) zombieFrame++;
  
  // Just 4 frames
  if (zombieFrame >= ZOMBIE_FRAME_COUNT ) zombieFrame = 0;
  
  // Draw all the zombies!
  for (id=0; id<ZOMBIE_MAX; id++)
  {
    if(!zombies[id].active) continue;
    sprites.drawPlusMask(zombies[id].x, zombies[id].y, zombie_plus_mask, zombieFrame + 4*zombies[id].direction);
  }
}


// zombieHealthOffset
// takes a value to be added to zombie health
// kills the zombie if health goes below zero
bool zombieHealthOffset(Enemy& obj, char amount)
{
  obj.health += amount;
  
  
  if(obj.health <= 0)
  {
    obj.active = false;
  }
  else if(amount < 0)
  {
    arduboy.tunes.tone(640, 20);
  }
}


// zombieCollision
// takes zombie id, collision box to test against
// returns true if collision boxes intersect
bool zombieCollision(byte id, int x, int y, int w, int h)
{
  return
    ( zombies[id].active ) &&
    ( zombies[id].x < x+w ) &&
    ( zombies[id].x + ZOMBIE_WIDTH > x ) &&
    ( zombies[id].y < x+h ) &&
    ( zombies[id].y + ZOMBIE_HEIGHT > x );
}

// clearZombies
// clears the entire list of zombies
void clearZombies()
{
  byte id;
  
  for(id=0; id<ZOMBIE_MAX; id++)
  {
    zombies[id].active = false;
  }
}

#endif
