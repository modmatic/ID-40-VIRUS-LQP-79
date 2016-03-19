#ifndef ELEMENTS_H
#define ELEMENTS_H

#include <Arduino.h>

byte survivorFrame = 0;

struct Element
{
  public:
    int x;
    int y;
};

Element survivor[5];

void createSurvivors(byte survivorCount)
{
  for (byte i =0; i < survivorCount; i++)
  {
    survivor[i].x = 0 + (i*80);
    survivor[i].y = 5;
  }
}

void drawSurvivors(byte survivorCount)
{
  if (arduboy.everyXFrames(6))survivorFrame++;
  if (survivorFrame > 3 ) survivorFrame = 0;
  for (byte i=0; i< survivorCount; i++)
  {
    sprites.drawPlusMask(survivor[i].x+ (i*17), survivor[i].y, survivor_plus_mask, survivorFrame);
  }
  
}


#endif
