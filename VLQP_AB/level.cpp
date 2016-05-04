#include "level.h"

// method implementations ///////////////////////////////////////////////////

int mapPositionX;
int mapPositionY;
byte level;
byte displayLevel;


// getTileType
// takes x and y in tile coordinates
// returns the tile type
unsigned char getTileType(unsigned int posX, unsigned int posY) {
	return
	// Block:read type (byte)
	pgm_read_byte(
		// Block:first index is block number
		&blocks[
			// Levels:read index (byte) poso block[] array
			(pgm_read_byte(
				// Levels:first index is level
				&levels[level - 1]
				// Levels:second index is map section (upper x/y bits)
				[((posX >> 3) + (posY & 0xF8)) >> 1]
			) & ((posX & 8) ? 0x0F:0xFF)) >> ((posX & 8) ? 0:4)
		// Block:second index is map tiles (lower x/y bits)
		][
			(posX & 0x07) + ((posY & 0x07) << 3)
		]
	);
}

void newDraw(unsigned posX, unsigned posY) {
	unsigned int intX = posX >> 3, subX = posX & 0x07;
	unsigned int intY = posY >> 3, subY = posY & 0x07;
	for (byte x = 0; x < (subX ? 17 : 16); x++) {
		for (byte y = 0; y < (subY ?  9 :  8); y++) {
			sprites.drawSelfMasked(
				((int)x << 3) - subX, ((int)y << 3) - subY, tileset,
				getTileType(intX + x, intY + y)
			);
		}
	}
}


void drawLevel()
{
  newDraw (mapPositionX, mapPositionY);
}


void drawNumbers(byte NumbersX, byte NumbersY, byte fontType, boolean scoreOrLevel)
{
  char buf[10];
  //scorePlayer = arduboy.cpuLoad();
  if (scoreOrLevel) itoa(displayLevel,buf,10);
  else ltoa(scorePlayer, buf, 10);
  char charLen = strlen(buf);
  char pad = 6 -(scoreOrLevel*4) - charLen;

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

void mapCollide(int& x, int& y, bool horizontal, char& vel, char w, char h)
{
  short tilex;
  short tiley;
  byte tileXMax = x%TILE_WIDTH != 0;
  byte tileYMax = y%TILE_HEIGHT != 0;
  for(tilex = x/TILE_WIDTH; tilex < x/TILE_WIDTH + 2 + tileXMax; tilex++)
  {
    for(tiley = y/TILE_HEIGHT; tiley < y/TILE_HEIGHT + 2 + tileYMax; tiley++)
    {
      if(getTileType(tilex, tiley) > 2)
      {
        if(horizontal)
        {
          if(vel < 0)
            x = tilex*TILE_WIDTH + TILE_WIDTH;
          else if(vel > 0)
            x = tilex*TILE_WIDTH - w;
        }
        else
        {
          if(vel < 0)
            y = tiley*TILE_HEIGHT + TILE_HEIGHT;
          else if(vel > 0)
            y = tiley*TILE_HEIGHT - h;
        }
        vel = 0;
      }
    }
  }
}
