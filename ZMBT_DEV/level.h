#ifndef LEVEL_H
#define LEVEL_H

#include <Arduino.h>
#include "globals.h"
#include "bitmaps.h"

// constants /////////////////////////////////////////////////////////////////

#define LEVEL_WIDTH 512
#define LEVEL_HEIGHT 256

#define LEVEL_BLOCK_WIDTH 8
#define LEVEL_BLOCK_HEIGHT 4

#define BLOCK_WIDTH 8
#define BLOCK_HEIGHT 8

#define TILE_WIDTH 8
#define TILE_HEIGHT 8

#define SCORE_SMALL_FONT          0
#define SCORE_BIG_FONT            1

extern const unsigned char *levelmap01[][32];


// method prototypes /////////////////////////////////////////////////////////


void drawLevel();
void loadLevel();
unsigned char getTileType(unsigned int x, unsigned int y);
void drawScore(byte scoreX, byte scoreY, byte fontType);
void drawNextLevel();

// data //////////////////////////////////////////////////////////////////////


PROGMEM const unsigned char block00[] =
{
  3, 3, 3, 3, 3, 3, 3, 3,
  3, 2, 2, 2, 2, 2, 2, 2,
  3, 0, 0, 0, 0, 0, 0, 0,
  3, 0, 1, 0, 1, 0, 1, 0,
  3, 0, 0, 1, 0, 1, 0, 1,
  3, 0, 1, 0, 1, 0, 1, 0,
  3, 0, 0, 1, 0, 1, 0, 1,
  3, 0, 1, 0, 1, 0, 1, 0,
};

PROGMEM const unsigned char block01[] =
{
  3, 3, 3, 3, 3, 3, 3, 3,
  2, 2, 2, 2, 2, 2, 2, 2,
  0, 0, 0, 0, 0, 0, 0, 0,
  1, 0, 1, 0, 1, 0, 1, 0,
  0, 1, 0, 1, 0, 1, 0, 1,
  1, 0, 1, 0, 1, 0, 1, 0,
  0, 1, 0, 1, 0, 1, 0, 1,
  1, 0, 1, 0, 1, 0, 1, 0,
};

PROGMEM const unsigned char block02[] =
{
  3, 3, 3, 3, 3, 3, 3, 3,
  2, 2, 2, 2, 2, 2, 2, 3,
  0, 0, 0, 0, 0, 0, 0, 3,
  1, 0, 1, 0, 1, 0, 0, 3,
  0, 1, 0, 1, 0, 1, 0, 3,
  1, 0, 1, 0, 1, 0, 0, 3,
  0, 1, 0, 1, 0, 1, 0, 3,
  1, 0, 1, 0, 1, 0, 0, 3,
};

PROGMEM const unsigned char block03[] =
{
  3, 0, 0, 1, 0, 1, 0, 1,
  3, 0, 1, 0, 1, 0, 1, 0,
  3, 0, 0, 1, 0, 1, 0, 1,
  3, 0, 1, 0, 1, 0, 1, 0,
  3, 0, 0, 1, 0, 1, 0, 1,
  3, 0, 1, 0, 1, 0, 1, 0,
  3, 0, 0, 1, 0, 1, 0, 1,
  3, 0, 1, 0, 1, 0, 1, 0,
};

PROGMEM const unsigned char block04[] =
{
  0, 1, 0, 1, 0, 1, 0, 1,
  1, 0, 1, 0, 1, 0, 1, 0,
  0, 1, 0, 1, 0, 1, 0, 1,
  1, 0, 1, 0, 1, 0, 1, 0,
  0, 1, 0, 1, 0, 1, 0, 1,
  1, 0, 1, 0, 1, 0, 1, 0,
  0, 1, 0, 1, 0, 1, 0, 1,
  1, 0, 1, 0, 1, 0, 1, 0,
};

PROGMEM const unsigned char block05[] =
{
  0, 1, 0, 1, 0, 1, 0, 3,
  1, 0, 1, 0, 1, 0, 0, 3,
  0, 1, 0, 1, 0, 1, 0, 3,
  1, 0, 1, 0, 1, 0, 0, 3,
  0, 1, 0, 1, 0, 1, 0, 3,
  1, 0, 1, 0, 1, 0, 0, 3,
  0, 1, 0, 1, 0, 1, 0, 3,
  1, 0, 1, 0, 1, 0, 0, 3,
};

PROGMEM const unsigned char block06[] =
{
  3, 0, 0, 1, 0, 1, 0, 1,
  3, 0, 1, 0, 1, 0, 1, 0,
  3, 0, 0, 1, 0, 1, 0, 1,
  3, 0, 1, 0, 1, 0, 1, 0,
  3, 0, 0, 1, 0, 1, 0, 1,
  3, 0, 1, 0, 1, 0, 1, 0,
  3, 0, 0, 0, 0, 0, 0, 0,
  3, 3, 3, 3, 3, 3, 3, 3,
};

PROGMEM const unsigned char block07[] =
{
  0, 1, 0, 1, 0, 1, 0, 1,
  1, 0, 1, 0, 1, 0, 1, 0,
  0, 1, 0, 1, 0, 1, 0, 1,
  1, 0, 1, 0, 1, 0, 1, 0,
  0, 1, 0, 1, 0, 1, 0, 1,
  1, 0, 1, 0, 1, 0, 1, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  3, 3, 3, 3, 3, 3, 3, 3,
};

PROGMEM const unsigned char block08[] =
{
  0, 1, 0, 1, 0, 1, 0, 3,
  1, 0, 1, 0, 1, 0, 0, 3,
  0, 1, 0, 1, 0, 1, 0, 3,
  1, 0, 1, 0, 1, 0, 0, 3,
  0, 1, 0, 1, 0, 1, 0, 3,
  1, 0, 1, 0, 1, 0, 0, 3,
  0, 0, 0, 0, 0, 0, 0, 3,
  3, 3, 3, 3, 3, 3, 3, 3,
};

PROGMEM const unsigned char block09[] =
{
  0, 1, 0, 1, 0, 1, 0, 1,
  1, 0, 1, 0, 1, 0, 1, 0,
  0, 1, 4, 6, 10, 14, 0, 1,
  1, 0, 5, 7, 11, 15, 1, 0,
  0, 1, 0, 8, 12, 1, 0, 1,
  1, 0, 1, 9, 13, 0, 1, 0,
  0, 1, 0, 1, 0, 1, 0, 1,
  1, 0, 1, 0, 1, 0, 1, 0,
};

PROGMEM const unsigned char block10[] =
{
  0, 1, 0, 1, 0, 1, 0, 1,
  1, 16, 18, 0, 1, 16, 18, 0,
  0, 17, 19, 1, 0, 17, 19, 1,
  1, 0, 1, 0, 1, 0, 1, 0,
  0, 1, 0, 1, 0, 1, 0, 1,
  1, 16, 18, 0, 1, 16, 18, 0,
  0, 17, 19, 1, 0, 17, 19, 1,
  1, 0, 1, 0, 1, 0, 1, 0,
};

PROGMEM const unsigned char * const levels[3][32] = {
  {
    block00, block01, block01, block01, block01, block01, block01, block02,
    block03, block09, block10, block03, block04, block05, block04, block05,
    block03, block10, block09, block06, block07, block08, block04, block05,
    block06, block07, block07, block07, block07, block07, block07, block08
  }, {
    block00, block01, block01, block01, block01, block01, block01, block02,
    block03, block04, block00, block04, block04, block02, block04, block05,
    block03, block04, block06, block07, block07, block08, block04, block05,
    block06, block07, block07, block07, block07, block07, block07, block08
  }, {
    block06, block06, block06, block06, block06, block06, block06, block06,
    block06, block06, block06, block06, block06, block06, block06, block06,
    block06, block06, block06, block06, block06, block06, block06, block06,
    block06, block06, block06, block06, block06, block06, block06, block06
  }
};


PROGMEM const unsigned char tileset[] = {
// width, height
8, 8,
// tile 0
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
// tile 1
0x00, 0x00, 0x30, 0x00, 0x20, 0x10, 0x00, 0x00, 
// tile 2
0x00, 0xCF, 0x30, 0x03, 0x04, 0x18, 0x64, 0x83,
// tile 3
0x6D, 0xFB, 0xBF, 0x57, 0xED, 0xBD, 0xDB, 0xEE, 
// tile 4
0x80, 0x40, 0x60, 0x80, 0x64, 0x0C, 0xF0, 0x40, 
// tile 5
0x09, 0x2A, 0x12, 0x24, 0x27, 0x48, 0xB3, 0xCC, 
// tile 6
0x3C, 0x08, 0xC4, 0xB6, 0x24, 0x92, 0x48, 0x17, 
// tile 7
0x8E, 0x55, 0x68, 0x92, 0x64, 0x0C, 0xF1, 0x42, 
// tile 8
0x09, 0x2A, 0x12, 0x24, 0x27, 0x48, 0xB3, 0xCC, 
// tile 9
0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x3F, 0xFF, 
// tile 10
0xB0, 0x53, 0x6C, 0x82, 0x64, 0x0C, 0xF1, 0x42, 
// tile 11
0x3F, 0x08, 0xC4, 0xB6, 0x24, 0x92, 0x48, 0x03, 
// tile 12
0x7E, 0xE1, 0x5C, 0x42, 0x39, 0x25, 0x51, 0x0A, 
// tile 13
0x3D, 0x7F, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 
// tile 14
0x3E, 0x08, 0xC4, 0xB4, 0x20, 0x90, 0x00, 0x00, 
// tile 15
0x5E, 0xE1, 0x5C, 0x42, 0x39, 0x25, 0x51, 0x0A, 
// tile 16
0x00, 0xF8, 0x04, 0xE6, 0xA2, 0x62, 0x02, 0xC2, 
// tile 17
0x20, 0x07, 0x54, 0x09, 0xA8, 0x09, 0x50, 0x13, 
// tile 18
0x06, 0x86, 0x86, 0x8C, 0x1C, 0xF8, 0xF0, 0x00, 
// tile 19
0x50, 0x17, 0xA2, 0x23, 0xA0, 0x7F, 0x7F, 0x00, 
};


#endif
