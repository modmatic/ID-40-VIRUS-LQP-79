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
    byte shotDelay;
};

Player coolGuy = { .x = 20, .y = 20, .walking = false, .direction = PLAYER_FACING_SOUTH, .frame = 0, .shotDelay = 10};

void updatePlayer()
{
  short vx = 0;
  short vy = 0;
  
  // Read input
  bool left = buttons.pressed(LEFT_BUTTON);
  bool right = buttons.pressed(RIGHT_BUTTON);
  bool up = buttons.pressed(UP_BUTTON);
  bool down = buttons.pressed(DOWN_BUTTON);
  bool rungun = buttons.pressed(A_BUTTON);
  bool standgun = buttons.pressed(B_BUTTON);
  bool strafegun = rungun && standgun;

  coolGuy.walking = up || down || left || right;
  coolGuy.walking = (standgun && !rungun) ? false : coolGuy.walking;
  
  if(coolGuy.shotDelay > 0) coolGuy.shotDelay--;
  
  // Update horizontal physics
  if(left)
    vx = -1;
  else if(right)
    vx = 1;
  
  if(strafegun || !standgun)
  {
    coolGuy.x += vx;
  }
  
  // Update vertical physics
  if(up)
    vy = -1;
  else if(down)
    vy = 1;
  
  if(strafegun || !standgun)
  {
    coolGuy.y += vy;
  }
  
  
  // Update sprite
  if(!strafegun)
  {
    if(vx < 0)
      coolGuy.direction = PLAYER_FACING_WEST;
    else if(vx > 0)
      coolGuy.direction = PLAYER_FACING_EAST;

    if(vy < 0) {
      if(coolGuy.direction == PLAYER_FACING_WEST)
        coolGuy.direction = PLAYER_FACING_NORTHWEST;
      else if(coolGuy.direction == PLAYER_FACING_EAST)
        coolGuy.direction = PLAYER_FACING_NORTHEAST;
      else
        coolGuy.direction = PLAYER_FACING_NORTH;
    }
    else if(vy > 0)
    {
      if(coolGuy.direction == PLAYER_FACING_WEST)
        coolGuy.direction = PLAYER_FACING_SOUTHWEST;
      else if(coolGuy.direction == PLAYER_FACING_EAST)
        coolGuy.direction = PLAYER_FACING_SOUTHEAST;
      else
        coolGuy.direction = PLAYER_FACING_SOUTH;
    }
  }
  
  if(standgun || rungun)
  {
    if(coolGuy.shotDelay == 0)
    {
      arduboy.tunes.tone(440, 20);
      coolGuy.shotDelay = 10;
    }
  }
}

void drawPlayer()
{
  if (arduboy.everyXFrames(6) && coolGuy.walking) coolGuy.frame++;
  if (coolGuy.frame > 3 ) coolGuy.frame = 0;
  sprites.drawPlusMask(coolGuy.x, coolGuy.y, player_plus_mask, coolGuy.frame + 4*coolGuy.direction);
}

#endif
