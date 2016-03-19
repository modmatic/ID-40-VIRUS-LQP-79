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

extern Arduboy arduboy;
extern Sprites sprites;
extern SimpleButtons buttons;
extern Player coolGuy;

Player coolGuy = {
  .x = 20,
  .y = 20,
  .walking = false,
  .direction = PLAYER_FACING_SOUTH,
  .frame = 0,
  .shotDelay = 10,
  .vx = 0,
  .vy = 0
};


// methods ///////////////////////////////////////////////////////////////////

// updatePlayer
// updates the player according to game rules
void updatePlayer(Player& obj)
{
  // Input velocity
  short vx = 0;
  short vy = 0;
  
  byte id;
  
  // Read input
  bool left = buttons.pressed(LEFT_BUTTON);
  bool right = buttons.pressed(RIGHT_BUTTON);
  bool up = buttons.pressed(UP_BUTTON);
  bool down = buttons.pressed(DOWN_BUTTON);
  bool rungun = buttons.pressed(A_BUTTON);
  bool standgun = buttons.pressed(B_BUTTON);
  bool strafegun = rungun && standgun;

  // Stop or continue walking animation
  obj.walking = up || down || left || right;
  obj.walking = (standgun && !rungun) ? false : obj.walking;
  
  // Bullet timer
  if(obj.shotDelay > 0) obj.shotDelay--;
  
  // Update horizontal physics
  if(left)
    vx = -1;
  else if(right)
    vx = 1;
 
  if(strafegun || !standgun)
  {
    obj.x += vx;
  }
  
  // collide with zombies
  for(id=0; id<ZOMBIE_MAX; id++)
  {
    if(zombieCollision(id, obj.x, obj.y, PLAYER_WIDTH, PLAYER_HEIGHT))
    {
      zombieHealthOffset(zombies[id], -1);
      break;
    }
  }
  
  // collide with survivors
  for(id=0; id<ZOMBIE_MAX; id++)
  {
    if(survivorCollision(id, obj.x, obj.y, PLAYER_WIDTH, PLAYER_HEIGHT))
    {
      zombieHealthOffset(zombies[id], -1);
      break;
    }
  }
  
  
  // Update vertical physics
  if(up)
    vy = -1;
  else if(down)
    vy = 1;
  
  if(strafegun || !standgun)
  {
    obj.y += vy;
  }
  
  // collide with zombies
  for(id=0; id<ZOMBIE_MAX; id++)
  {
    if(zombieCollision(id, obj.x, obj.y, PLAYER_WIDTH, PLAYER_HEIGHT))
    {
      zombieHealthOffset(zombies[id], -1);
      break;
    }
  }
  
  // collide with survivors
  for(id=0; id<ZOMBIE_MAX; id++)
  {
    if(survivorCollision(id, obj.x, obj.y, PLAYER_WIDTH, PLAYER_HEIGHT))
    {
      zombieHealthOffset(zombies[id], -1);
      break;
    }
  }
  
  
  // Update sprite
  if(!strafegun)
  {
    if(vx < 0)
      obj.direction = PLAYER_FACING_WEST;
    else if(vx > 0)
      obj.direction = PLAYER_FACING_EAST;

    if(vy < 0) {
      if(obj.direction == PLAYER_FACING_WEST)
        obj.direction = PLAYER_FACING_NORTHWEST;
      else if(obj.direction == PLAYER_FACING_EAST)
        obj.direction = PLAYER_FACING_NORTHEAST;
      else
        obj.direction = PLAYER_FACING_NORTH;
    }
    else if(vy > 0)
    {
      if(obj.direction == PLAYER_FACING_WEST)
        obj.direction = PLAYER_FACING_SOUTHWEST;
      else if(obj.direction == PLAYER_FACING_EAST)
        obj.direction = PLAYER_FACING_SOUTHEAST;
      else
        obj.direction = PLAYER_FACING_SOUTH;
    }
  }
  
  // Update gun
  if(standgun || rungun)
  {
    if(obj.shotDelay == 0)
    {
      addBullet(obj.x + PLAYER_WIDTH/2, obj.y + PLAYER_HEIGHT/2, obj.direction, 0, 0);
      obj.shotDelay = 10;
    }
  }
  
  // Update animation
  if (arduboy.everyXFrames(6) && obj.walking) obj.frame++;
  if (obj.frame > 3 ) obj.frame = 0;
}

// drawPlayer
// draws the player to the screen
void drawPlayer(Player& obj)
{
  sprites.drawPlusMask(obj.x, obj.y, player_plus_mask, obj.frame + 4*obj.direction);
}

#endif
