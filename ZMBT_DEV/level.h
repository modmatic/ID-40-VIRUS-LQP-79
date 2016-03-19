#ifndef LEVEL_H
#define LEVEL_H

#include <Arduino.h>

// constants /////////////////////////////////////////////////////////////////

#define LEVEL_WIDTH WIDTH
#define LEVEL_HEIGHT HEIGHT

// methods ///////////////////////////////////////////////////////////////////

void drawLevel()
{
  
}

// data //////////////////////////////////////////////////////////////////////

const unsigned char PROGMEM level01[] =
{
  4, // amount of enemies
  2, // amount of survivors

  // blocks used in the level
  1,2,2,2,2,3,
  4,5,5,5,5,6,
  7,8,8,8,8,9,
};





#endif
