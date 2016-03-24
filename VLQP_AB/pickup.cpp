#include "pickup.h"
#include "player.h"

// globals ///////////////////////////////////////////////////////////////////

Pickup pickups[PICKUP_MAX];

// method implementations ////////////////////////////////////////////////////

// addPickup
// tries to add a pickup to the world. returns true if succsessful
bool addPickup(int x, int y)
{
  byte id;
  
  for(id=0; id<PICKUP_MAX; id++)
  {
    if(!pickups[id].type)
    {
      pickups[id].x = x;
      pickups[id].y = y;
      pickups[id].frame = 0;
      pickups[id].type = random(0, 3);
      return true;
    }
  }
  
  return false;
}

// drawPickups
// draws the entire list of pickups
void drawPickups()
{
  byte id;
  
  for(id=0; id < PICKUP_MAX; id++)
  {
    if(!pickups[id].type) continue;
    
    if (arduboy.everyXFrames(6)) pickups[id].frame++;
    if(pickups[id].frame > 3) pickups[id].frame = 0;
    
    if(pickups[id].type == PICKUP_TYPE_HEART)
      sprites.drawPlusMask(pickups[id].x - mapPositionX, pickups[id].y - mapPositionY, heart_plus_mask, pickups[id].frame);
    else
      sprites.drawPlusMask(pickups[id].x - mapPositionX, pickups[id].y - mapPositionY, coin_plus_mask, pickups[id].frame);
  }
}

// pickupCollision
// checks for collision against the player, and handles it
void pickupCollision(int x, int y)
{
  byte id;
  for(id=0; id < PICKUP_MAX; id++)
  {
    if(
      ( pickups[id].type ) &&
      ( pickups[id].x < x + PLAYER_WIDTH ) &&
      ( pickups[id].x + PICKUP_WIDTH > x ) &&
      ( pickups[id].y < y + PLAYER_HEIGHT ) &&
      ( pickups[id].y + PICKUP_HEIGHT > y ))
    {
      if(pickups[id].type == PICKUP_TYPE_HEART)
      {
        arduboy.tunes.tone(660, 20);
        playerHealthOffset(coolGirl, 1);
      }
      else
      {
        arduboy.tunes.tone(880, 20);
        rollingScore += 100;
      }
      pickups[id].type = PICKUP_TYPE_INACTIVE;
    }
  }
}

// clearPickups
// clears the entire list of pickups
void clearPickups()
{
  byte id;
  
  for(id=0; id<PICKUP_MAX; id++)
  {
    pickups[id].type = PICKUP_TYPE_INACTIVE;
  }
}
