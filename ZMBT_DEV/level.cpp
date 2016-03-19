#include "level.h"

// method implementations ///////////////////////////////////////////////////

int mapPositionX;
int mapPositionY;
byte level;

const unsigned char *levels[][32] =
{
  block00, block01, block01, block01, block01, block01, block01, block02,
  block03, block09, block04, block09, block04, block09, block04, block05,
  block03, block04, block09, block04, block09, block04, block09, block05,
  block06, block07, block07, block07, block07, block07, block07, block08,

  block00, block01, block01, block01, block01, block01, block01, block02,
  block03, block04, block00, block04, block04, block02, block04, block05,
  block03, block04, block06, block07, block07, block08, block04, block05,
  block06, block07, block07, block07, block07, block07, block07, block08,

  block06, block06, block06, block06, block06, block06, block06, block06,
  block06, block06, block06, block06, block06, block06, block06, block06,
  block06, block06, block06, block06, block06, block06, block06, block06,
  block06, block06, block06, block06, block06, block06, block06, block06,
};


void newDraw(unsigned posX, unsigned posY) {
  unsigned int intX = posX >> 3, subX = posX & 0x07;
  unsigned int intY = posY >> 3, subY = posY & 0x07;
  for (byte x = 0; x < (subX ? 17 : 16); x++) {
    for (byte y = 0; y < (subY ?  9 :  8); y++) {
      sprites.drawSelfMasked(
        ((int)x << 3) - subX, ((int)y << 3) - subY, tileset,
        pgm_read_byte(&levels[level - 1]
                      [((intX + x) >> 3) + ((intY + y) & 0xF8)]
                      [((intX + x) & 0x07) + (((intY + y) & 0x07) << 3)]
                     ));
    }
  }
}

void drawLevel()
{
  newDraw (mapPositionX, mapPositionY);
}


