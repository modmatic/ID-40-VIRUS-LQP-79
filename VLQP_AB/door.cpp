#include "door.h"

#include "player.h"

// globals ///////////////////////////////////////////////////////////////////

Door exitDoor;

// method implementations ////////////////////////////////////////////////////
byte checkDoorOrientation()
{
  if (exitDoor.y == 0) return EXIT_FACING_SOUTH;
  if (exitDoor.x == 62) return EXIT_FACING_WEST;
  if (exitDoor.y == 30) return EXIT_FACING_NORTH;
  if (exitDoor.x == 0) return EXIT_FACING_EAST;
}

void setDoorPosition(int x, int y)
{
  exitDoor.x = x;
  exitDoor.y = y;
  exitDoor.orientation = checkDoorOrientation();
  exitDoor.active = false;
}

void showDoor()
{
  exitDoor.active = true;
}

bool checkDoorCollision()
{
  return
    ( exitDoor.active ) &&
    ( exitDoor.x < coolGirl.x + PLAYER_WIDTH ) &&
    ( exitDoor.x + SURVIVOR_WIDTH > coolGirl.x ) &&
    ( exitDoor.y < coolGirl.y + PLAYER_HEIGHT ) &&
    ( exitDoor.y + SURVIVOR_HEIGHT > coolGirl.y );
}

void drawDoor()
{
  if (exitDoor.active)
  {
    if (arduboy.everyXFrames(10))exitDoor.frame++;
    if (exitDoor.frame > 3)exitDoor.frame = 0;
    for (byte x = 0; x < 2; x++)
    {
      for (byte y = 0; y < 2; y++)
      {
        sprites.drawPlusMask(exitDoor.x - mapPositionX +(x*8), exitDoor.y - mapPositionY + (y*8), exit_plus_mask, exitDoor.frame + 4 * exitDoor.orientation);
      }
    }
  }
}
