#ifndef ELEMENTS_H
#define ELEMENTS_H

#include <Arduino.h>
#include "globals.h"
#include "bitmaps.h"

// constants /////////////////////////////////////////////////////////////////

#define SURVIVOR_FRAME_SKIP      10
#define SURVIVOR_FRAME_COUNT     4
#define SURVIVOR_MAX             5

#define SURVIVOR_WIDTH           16
#define SURVIVOR_HEIGHT          16

extern int positionOnMapX;
extern int positionOnMapY;

// structures ////////////////////////////////////////////////////////////////

struct Element
{
  public:
    int x;
    int y;
    byte active;
};


// globals ///////////////////////////////////////////////////////////////////

// list of survivors
extern Element survivors[SURVIVOR_MAX];


// method prototypes /////////////////////////////////////////////////////////

void setSurvivor(Element& obj, int x, int y);
void addSurvivor(int x, int y);
void updateSurvivors();
void drawSurvivors();
bool survivorCollision(byte id, int x, int y, int w, int h);
void clearSurvivors();

#endif
