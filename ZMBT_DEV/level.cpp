#include "level.h"

// method implementations ///////////////////////////////////////////////////

int mapPositionX;
int mapPositionY;
byte level;


void newDraw(unsigned posX, unsigned posY) {
  unsigned int intX = posX >> 3, subX = posX & 0x07;
  unsigned int intY = posY >> 3, subY = posY & 0x07;
  for (byte x = 0; x < (subX ? 17 : 16); x++) {
    for (byte y = 0; y < (subY ?  9 :  8); y++) {
      sprites.drawSelfMasked(
        ((int)x << 3) - subX, ((int)y << 3) - subY, tileset,
        // Block:read tile index (byte) for tileset
        pgm_read_byte(&(
          // Levels:read pointer (word) to blockNN, cast for arry indexing
          ((unsigned char * const)pgm_read_word(
            &levels[
              // Levels:first index is level
              level - 1
            ][
              // Levels:second index is map section (upper x/y bits)
              ((intX + x) >> 3) + ((intY + y) & 0xF8)
            ]
          ))[
            // Block:first index is map tiles (lower x/y bits)
            ((intX + x) & 0x07) + (((intY + y) & 0x07) << 3)
          ]
        ))
      );
    }
  }
}

// getTileType
// takes x and y in tile coordinates
// returns the tile type
unsigned char getTileType(unsigned int posX, unsigned int posY)
{

  int tileAbsoluteIndex = posX + posY * (LEVEL_WIDTH / TILE_WIDTH);

  int tileLocalX = posX % BLOCK_WIDTH;
  int tileLocalY = posY % BLOCK_HEIGHT;
  int tileLocalIndex = tileLocalX + tileLocalY * BLOCK_WIDTH;

  int tileBlockX = posX / BLOCK_WIDTH;
  int tileBlockY = posY / BLOCK_HEIGHT;
  int blockIndex = tileBlockX + tileBlockY * LEVEL_BLOCK_WIDTH;

  unsigned char tileID = pgm_read_byte(&(((unsigned char * const)pgm_read_word(&levels[level - 1][blockIndex]))[tileLocalIndex]));

  return tileID;

}

void drawLevel()
{
  newDraw (mapPositionX, mapPositionY);
}


void drawNumbers(byte NumbersX, byte NumbersY, byte fontType, boolean ScoreOrLevel)
{
  char buf[10];
  //scorePlayer = arduboy.cpuLoad();
  if (scoreOrLevel) itoa(level,buf,10);
  else ltoa(scorePlayer, buf, 10);
  char charLen = strlen(buf);
  char pad = 6 -(ScoreOrLevel*4) - charLen;

  //draw 0 padding
  for (byte i = 0; i < pad; i++)
  {
    switch (fontType)
    {
      case SCORE_SMALL_FONT:
        sprites.drawPlusMask(NumbersX + (7 * i), NumbersY, numbersSmall_plus_mask, 0);
        break;
      case SCORE_BIG_FONT:
        sprites.drawSelfMasked(NumbersX + (10 * i), NumbersY, numbersBig, 0);
        break;
    }
  }

  for (byte i = 0; i < charLen; i++)
  {
    char digit = buf[i];
    byte j;
    if (digit <= 48)
    {
      digit = 0;
    }
    else {
      digit -= 48;
      if (digit > 9) digit = 0;
    }

    for (byte z = 0; z < 10; z++)
    {
      if (digit == z) j = z;
    }
    switch (fontType)
    {
      case SCORE_SMALL_FONT:
        sprites.drawPlusMask(NumbersX + (pad * 7) + (7 * i), NumbersY, numbersSmall_plus_mask, digit);
        break;
      case SCORE_BIG_FONT:
        sprites.drawSelfMasked(NumbersX + (pad * 10) + (10 * i), NumbersY, numbersBig, digit);
        break;
    }
  }
}

