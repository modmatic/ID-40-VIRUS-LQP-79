#ifndef ELEMENTS_H
#define ELEMENTS_H

#include <Arduino.h>

// constants /////////////////////////////////////////////////////////////////

#define SURVIVOR_FRAME_SKIP      6
#define SURVIVOR_FRAME_COUNT     4
#define SURVIVOR_MAX             5

#define SURVIVOR_WIDTH           16
#define SURVIVOR_HEIGHT          16


// structures ////////////////////////////////////////////////////////////////

struct Element
{
  public:
    int x;
    int y;
    byte active;
};


// globals ///////////////////////////////////////////////////////////////////

// animation frame for all survivors
byte survivorFrame = 0;

// list of survivors
Element survivors[SURVIVOR_MAX];


// methods ///////////////////////////////////////////////////////////////////

// setZombie
// sets the position of a zombie, and enables that instance
void setSurvivor(Element& obj, int x, int y)
{
  obj.x = x;
  obj.y = y;
  obj.active = true;
}


// addSurvivor
// searches the survivor list for an empty slot, adds one if available
void addSurvivor(int x, int y)
{
  byte id;
  
  for(id=0; id<SURVIVOR_MAX; id++)
  {
    if(!survivors[id].active)
    {
      setSurvivor(survivors[id], x, y);
      break;
    }
  }
}


// updateSurvivors
// updates the survivor states
void updateSurvivors()
{
  // advance the frame
  if (arduboy.everyXFrames(SURVIVOR_FRAME_SKIP)) survivorFrame++;
  
  // clamp to 4 frames
  if (survivorFrame >= SURVIVOR_FRAME_COUNT ) survivorFrame = 0;
}


// drawSurvivors
// draws every active survivor in the list to the display
void drawSurvivors()
{
  // draw the survivor!
  for (byte id=0; id<SURVIVOR_MAX; id++)
  {
    if(!survivors[id].active) continue;
    sprites.drawPlusMask(survivors[id].x+ (id*17), survivors[id].y, survivor_plus_mask, survivorFrame);
  }
  
}

// survivorCollision
// takes survivor id, collision box to test against
// returns true if collision boxes intersect
bool survivorCollision(byte id, int x, int y, int w, int h)
{
  return
    ( survivors[id].active ) &&
    ( survivors[id].x < x+w ) &&
    ( survivors[id].x + SURVIVOR_WIDTH > x ) &&
    ( survivors[id].y < x+h ) &&
    ( survivors[id].y + SURVIVOR_HEIGHT > x );
}

// clearSurvivors
// clears the entire list of survivors
void clearSurvivors()
{
  byte id;
  
  for(id=0; id<SURVIVOR_MAX; id++)
  {
    survivors[id].active = false;
  }
}

#endif
