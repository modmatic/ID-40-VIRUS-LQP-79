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
    if(!pickups[id].active)
    {
      pickups[id].x = x;
      pickups[id].y = y;
      pickups[id].frame = 0;
      pickups[id].active = true;
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
    if(!pickups[id].active) continue;
    
    if (arduboy.everyXFrames(6)) pickups[id].frame++;
    if(pickups[id].frame > 3) pickups[id].frame = 0;
    
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
      ( pickups[id].active ) &&
      ( pickups[id].x < x + PLAYER_WIDTH ) &&
      ( pickups[id].x + PICKUP_WIDTH > x ) &&
      ( pickups[id].y < y + PLAYER_HEIGHT ) &&
      ( pickups[id].y + PICKUP_HEIGHT > y ))
    {
      pickups[id].active = false;
      arduboy.tunes.tone(440, 20);
      rollingScore += 100;
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
    pickups[id].active = false;
  }
}
