#include "level.h"

// method implementations ///////////////////////////////////////////////////

int mapPositionX;
int mapPositionY;

const unsigned char *levelmap01[] =
{
  tilemap00, tilemap01, tilemap01, tilemap01, tilemap01, tilemap01, tilemap01, tilemap02,
  tilemap03, tilemap04, tilemap04, tilemap04, tilemap04, tilemap04, tilemap04, tilemap05,
  tilemap03, tilemap04, tilemap04, tilemap04, tilemap04, tilemap04, tilemap04, tilemap05,
  tilemap06, tilemap07, tilemap07, tilemap07, tilemap07, tilemap07, tilemap07, tilemap08,
};

const unsigned char *levelmap02[] =
{
  tilemap00, tilemap01, tilemap01, tilemap01, tilemap01, tilemap01, tilemap01, tilemap02,
  tilemap03, tilemap04, tilemap04, tilemap04, tilemap04, tilemap04, tilemap04, tilemap05,
  tilemap03, tilemap04, tilemap04, tilemap04, tilemap04, tilemap04, tilemap04, tilemap05,
  tilemap06, tilemap07, tilemap07, tilemap07, tilemap07, tilemap07, tilemap07, tilemap08,
};

const unsigned char *levelmaps[] =
{
  *levelmap01,*levelmap01,
};

void newDraw(unsigned posX, unsigned posY) {
  unsigned int intX = posX >> 3, subX = posX & 0x07;
  unsigned int intY = posY >> 3, subY = posY & 0x07;
  for (byte x = 0; x < (subX ? 17 : 16); x++) {
    for (byte y = 0; y < (subY ?  9 :  8); y++) {
      sprites.drawSelfMasked(
        ((int)x << 3) - subX, ((int)y << 3) - subY, tileset,
        pgm_read_byte(&levelmap01
                      [((intX + x) >> 3) + ((intY + y) & 0xF8)]
                      [((intX + x) & 0x07) + (((intY + y) & 0x07) << 3)]
                     ));
    }
  }
}

void drawLevel()
{
  newDraw (mapPositionX,mapPositionY);
}


