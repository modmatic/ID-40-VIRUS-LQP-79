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
    ( exitDoor.x < coolGirl.x+PLAYER_WIDTH ) &&
    ( exitDoor.x + SURVIVOR_WIDTH > coolGirl.x ) &&
    ( exitDoor.y < coolGirl.y+PLAYER_HEIGHT ) &&
    ( exitDoor.y + SURVIVOR_HEIGHT > coolGirl.y );
}

void drawDoor()
{
  if(exitDoor.active) sprites.drawPlusMask(exitDoor.x - mapPositionX, exitDoor.y - mapPositionY,door_plus_mask, 0);
}
