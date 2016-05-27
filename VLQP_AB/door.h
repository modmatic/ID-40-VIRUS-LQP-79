#ifndef DOOR_H
#define DOOR_H

#include <Arduino.h>

// constants /////////////////////////////////////////////////////////////////

#define DOOR_WIDTH              16
#define DOOR_HEIGHT             16

#define EXIT_FACING_SOUTH       0
#define EXIT_FACING_WEST        1
#define EXIT_FACING_NORTH       2
#define EXIT_FACING_EAST        3

// structures ////////////////////////////////////////////////////////////////

struct Door {
  int x;
  int y;
  byte active;
  byte orientation;
  byte frame;
};

// globals ///////////////////////////////////////////////////////////////////

extern Door exitDoor;

// method prototypes /////////////////////////////////////////////////////////

void setDoorPosition(int x, int y);
void showDoor();
void drawDoor();
bool checkDoorCollision();

#endif
