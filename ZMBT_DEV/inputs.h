#ifndef INPUT_H
#define INPUT_H

#include <Arduino.h>
#include "player.h"

extern Arduboy arduboy;
extern SimpleButtons buttons;
extern Player coolGuy;

#define PLAYER_FACING_SOUTH       0
#define PLAYER_FACING_SOUTHWEST   1
#define PLAYER_FACING_WEST        2
#define PLAYER_FACING_NORTHWEST   3
#define PLAYER_FACING_NORTH       4
#define PLAYER_FACING_NORTHEAST   5
#define PLAYER_FACING_EAST        6
#define PLAYER_FACING_SOUTHEAST   7


void checkInputs()
{
  coolGuy.walking = false;
  if (buttons.pressed(DOWN_BUTTON) && buttons.notPressed(LEFT_BUTTON) && buttons.notPressed(RIGHT_BUTTON))
  {
    coolGuy.walking = true;
    coolGuy.direction = PLAYER_FACING_SOUTH;
  }
  if (buttons.pressed(DOWN_BUTTON) && buttons.pressed(LEFT_BUTTON))
  {
    coolGuy.walking = true;
    coolGuy.direction = PLAYER_FACING_SOUTHWEST;
  }
  if (buttons.pressed(LEFT_BUTTON) && buttons.notPressed(UP_BUTTON) && buttons.notPressed(DOWN_BUTTON))
  {
    coolGuy.walking = true;
    coolGuy.direction = PLAYER_FACING_WEST;
  }
  if (buttons.pressed(LEFT_BUTTON) && buttons.pressed(UP_BUTTON))
  {
    coolGuy.walking = true;
    coolGuy.direction = PLAYER_FACING_NORTHWEST;
  }
  if (buttons.pressed(UP_BUTTON) && buttons.notPressed(LEFT_BUTTON) && buttons.notPressed(RIGHT_BUTTON))
  {
    coolGuy.walking = true;
    coolGuy.direction = PLAYER_FACING_NORTH;
  }
  if (buttons.pressed(UP_BUTTON) && buttons.pressed(RIGHT_BUTTON))
  {
    coolGuy.walking = true;
    coolGuy.direction = PLAYER_FACING_NORTHEAST;
  }
  if ((buttons.pressed(RIGHT_BUTTON)) && buttons.notPressed(UP_BUTTON) && buttons.notPressed(DOWN_BUTTON))
  {
    coolGuy.walking = true;
    coolGuy.direction = PLAYER_FACING_EAST;
  }
  if (buttons.pressed(RIGHT_BUTTON) && buttons.pressed(DOWN_BUTTON))
  {
    coolGuy.walking = true;
    coolGuy.direction = PLAYER_FACING_SOUTHEAST;
  }
  

  if (buttons.justPressed(A_BUTTON)) {}
  if (buttons.justPressed(B_BUTTON)) {}
}

#endif
