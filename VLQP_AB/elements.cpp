#include "elements.h"
#include "player.h"
#include "door.h"

// globals ///////////////////////////////////////////////////////////////////

Element survivors[SURVIVOR_MAX];

// animation frame for all survivors
byte survivorFrame = 0;
boolean showHelp = true;
byte amountActiveSurvivors = 0;

// method implementations ////////////////////////////////////////////////////

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

  for (id = 0; id < SURVIVOR_MAX; id++)
  {
    if (!survivors[id].active)
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
  if (arduboy.everyXFrames(30)) showHelp = !showHelp;
  // draw the survivor!
  for (byte id = 0; id < SURVIVOR_MAX; id++)
  {
    if (!survivors[id].active) continue;
    sprites.drawPlusMask(survivors[id].x - mapPositionX, survivors[id].y - mapPositionY, survivor_plus_mask, survivorFrame);
    if (showHelp)sprites.drawPlusMask(survivors[id].x + 16 - mapPositionX, survivors[id].y - 9 - mapPositionY, help_plus_mask, 0);
  }

}

// survivorCollision
// takes a survivor, collision box to test against
// returns true if collision boxes intersect
bool survivorCollision(Element& obj, int x, int y, int w, int h)
{
  return
    ( obj.active ) &&
    ( obj.x < x + w ) &&
    ( obj.x + SURVIVOR_WIDTH > x ) &&
    ( obj.y < y + h ) &&
    ( obj.y + SURVIVOR_HEIGHT > y );
}

// collectSurvivor
// takes a survivor, sets it inactive.
// returns false if no survivors are left on the map, otherwise true
bool collectSurvivor(Element& obj)
{
  byte id;
  obj.active = false;
  arduboy.tunes.tone(660, 20);

  for (id = 0; id < SURVIVOR_MAX; id++)
  {
    if (survivors[id].active)
      return false;
  }

  return true;
}

// clearSurvivors
// clears the entire list of survivors
void clearSurvivors()
{
  byte id;

  for (id = 0; id < SURVIVOR_MAX; id++)
  {
    survivors[id].active = false;
  }
}

void drawAmountSurvivors()
{
  for (byte amountSurvivors = 0; amountSurvivors < countAmountActiveSurvivors(); amountSurvivors++) // needs the amount of active survivors
  {
    sprites.drawPlusMask(40 + amountSurvivors * 10, 0, HUD_plus_mask, 1);
  }
  if (!countAmountActiveSurvivors() && showHelp)
  {
    sprites.drawPlusMask(55, 0, HUD_plus_mask, 2);
    sprites.drawPlusMask(64, 0, HUD_plus_mask, 3);
  }
}

byte countAmountActiveSurvivors()
{
  byte id;
  byte countAmount = 0;
  for (id = 0; id < SURVIVOR_MAX; id++)
  {
    if (survivors[id].active) countAmount++;
  }
  return countAmount;
};


void survivorCollide(int x, int y)
{
  byte id;
  
  for(id=0; id<SURVIVOR_MAX; id++)
  {
    if(survivorCollision(survivors[id], x, y, PLAYER_WIDTH, PLAYER_HEIGHT))
    {
      if(collectSurvivor(survivors[id]))
      {
        showDoor();
      }
    }
  }
}
