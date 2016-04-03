#include "level.h"

// method implementations ///////////////////////////////////////////////////

int mapPositionX;
int mapPositionY;
byte level;
byte displayLevel;

/// OLD level data down here
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
/// OLD level data up here





/// NEW level data down here
/*
void newDraw()
{
  // Separate the high and low parts of the position
  // Only 3 bits are in the lower part because of the 8 pixel width of the tile
  // To draw the tile, the lower three bits can be used as an offset
  // The upper 5 bits are the section of the map the tile is on
  unsigned int upperFiveX = mapPositionX >> 3;
  unsigned int lowerThreeX = mapPositionX & 0x07;
  unsigned int upperFiveY = mapPositionY >> 3;
  unsigned int lowerThreeY = mapPositionY & 0x07;
  
  // loop 16 or 17 times, handle off-by-one: if lowerThreeX is zero, just 16
  for (byte x = 0; x < (lowerThreeX ? 17 : 16); x++) {
    
    // loop 8 or 9 times, handle off-by-one: if lowerThreeY is zero, just 8
    for (byte y = 0; y < (lowerThreeY ?  9 :  8); y++) {
      
      // Calculate block id
      unsigned char blockId = pgm_read_byte(levels + (level-1)*LEVEL_OFFSET)
      
      // call mask drawing function
      sprites.drawSelfMasked(
      
        // X position is tile position * tile width, plus lower bits
        ((int)x * 8) - lowerThreeX,
        
        // X position is tile position * tile height, plus lower bits
        ((int)y * 8) - lowerThreeY,
        
        // Use the tileset sprite
        tileset,
        
        // Calculate the sprite to draw
        
        
        // Block:read tile index (byte) for tileset
        pgm_read_byte(&(
          // Levels:read pointer (word) to blockNN, cast for arry indexing
          ((unsigned char * const)pgm_read_word(
            &levels[
              // Levels:first index is level
              level - 1
            ][
              // Levels:second index is map section (upper x/y bits)
              ((upperFiveX + x) >> 3) + ((upperFiveY + y) & 0xF8)
            ]
          ))[
            // Block:first index is map tiles (lower x/y bits)
            ((upperFiveX + x) & 0x07) + (((upperFiveY + y) & 0x07) * 8)
          ]
        ))
      );
      ;
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
  unsigned char blockShift = (blockIndex % 2 == 0) ? 4 : 0;
  unsigned char blockName = (((pgm_read_word(&levels[(level-1) * LEVEL_OFFSET + (blockIndex/2)])) >> blockShift)) & 0x0f;

  unsigned char tileID = pgm_read_byte(blocks + (blockName * BLOCK_OFFSET) + tileLocalIndex);

  return tileID;
}

void drawLevel()
{
  newDraw();
}
*/
/// NEW level data up here

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
