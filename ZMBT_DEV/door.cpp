#include "door.h"

#include "player.h"

// globals ///////////////////////////////////////////////////////////////////

Door exitDoor;

// method implementations ////////////////////////////////////////////////////

void setDoorPosition(int x, int y)
{
  exitDoor.x = x;
  exitDoor.y = y;
  
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
    ( exitDoor.x < coolGirl.positionOnMapX+PLAYER_WIDTH ) &&
    ( exitDoor.x + SURVIVOR_WIDTH > coolGirl.positionOnMapX ) &&
    ( exitDoor.y < coolGirl.positionOnMapY+PLAYER_HEIGHT ) &&
    ( exitDoor.y + SURVIVOR_HEIGHT > coolGirl.positionOnMapY );
}

void drawDoor()
{
  if(!exitDoor.active) return;
  arduboy.drawRect(exitDoor.x - mapPositionX, exitDoor.y - mapPositionY, DOOR_WIDTH, DOOR_HEIGHT, 1);
}
