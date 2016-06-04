#include "game.h"
#include "enemies.h"
#include "pickup.h"

byte gameOverAndStageFase;
boolean bonusVisible;
boolean nextLevelVisible;
int leftX;
byte rightX;


// method implementations ////////////////////////////////////////////////////

// stateGamePlaying
// called each frame the gamestate is set to playing
void stateGamePlaying()
{
  // Update Level
  if (!(arduboy.frameCount % (60 * 3))) {
    spawnZombie();
  }


  // Update Objects
  updatePlayer(coolGirl);
  updateBullets();
  updateZombies();
  updateSurvivors();

  // Draw
  drawLevel();
  drawDoor();
  drawPickups();
  drawZombies();
  drawSurvivors();
  drawBullets();
  drawPlayer(coolGirl);

  drawNumbers(86, 0, FONT_SMALL, DATA_SCORE);
  drawLife(coolGirl);
  drawAmountSurvivors();
  drawCoolDown();
  //drawZombieBlips();
}

int readSurvivorData(unsigned char index)
{
  return pgm_read_byte(survivorLocation + ((int)level - 1) * 10 + (int)index) * TILE_WIDTH; //PLAYER_WIDTH
}

int readPlayerAndExitData(unsigned char index)
{
  return pgm_read_byte(playerAndExitLocation + ((int)level - 1) * 4 + (int)index) * TILE_WIDTH; //PLAYER_WIDTH
}

// stateGameNextLevel
// called each frame the gamestate is set to next level
void stateGamePrepareLevel()
{
  clearSurvivors();
  clearPickups();
  clearZombies();

  level++;
  level = (level - 1) % NUM_LEVELS + 1;
  displayLevel++;

  pickupsCounter = 0;
  gameOverAndStageFase = 0;
  globalCounter = 0;

  gameState = STATE_GAME_NEXT_LEVEL;
}


void nextLevelStart()
{
  leftX = -48;
  rightX = 164;
  if (level > 1)
  {
    bonusVisible = true;
    nextLevelVisible = false;
    gameOverAndStageFase++;
  }
  else
  {
    bonusVisible = false;
    nextLevelVisible = true;
    gameOverAndStageFase = 4;
  }
}

void nextLevelBonusCount()
{
  if (exitDoor.counter > 0)
  {
    exitDoor.counter--;
    scorePlayer += 5;
    arduboy.audio.tone(3951, 5);
  }
  else
  {
    gameOverAndStageFase++;
  }
}

void nextLevelWait()
{
  if (arduboy.everyXFrames(4)) globalCounter++;
  if (globalCounter > 8)
  {
    gameOverAndStageFase++;
    globalCounter = 0;
  }
}

void nextLevelSlideToMiddle()
{
  bonusVisible = false;
  nextLevelVisible = true;
  if (leftX < 31)
  {
    leftX += 4;
    rightX -= 4;
  }
  else gameOverAndStageFase++;
}


void nextLevelEnd()
{
  gameState = STATE_GAME_PLAYING;
  gameOverAndStageFase = 0;
  bonusVisible = false;
  nextLevelVisible = false;
  leftX = -48;
  rightX = 164;
  
  coolGirl.x = readPlayerAndExitData(0);
  coolGirl.y = readPlayerAndExitData(1);
  setDoorPosition(readPlayerAndExitData(2), readPlayerAndExitData(3));

  for (byte i = 0; i < ((displayLevel - 1) / NUM_LEVELS) + 2; i++)
  {
    addSurvivor(readSurvivorData(2 * i), readSurvivorData((2 * i) + 1));
  }

}

typedef void (*FunctionPointer) ();
const FunctionPointer PROGMEM nextLevelFases[] =
{
  nextLevelStart,
  nextLevelWait,
  nextLevelBonusCount,
  nextLevelWait,
  nextLevelSlideToMiddle,
  nextLevelWait,
  nextLevelEnd,
};

void stateGameNextLevel()
{
  ((FunctionPointer) pgm_read_word (&nextLevelFases[gameOverAndStageFase]))();
  if (bonusVisible)
  {
    sprites.drawSelfMasked(29, 16, bonusPoints, 0);
    drawNumbers(78, 16, FONT_SMALL, DATA_TIMER);
    drawNumbers(36, 36, FONT_BIG, DATA_SCORE);
  }
  if (nextLevelVisible)
  {
    sprites.drawSelfMasked(leftX, 24, nextLevel, 0);
    drawNumbers(rightX, 24, FONT_BIG, DATA_LEVEL);
  }
}

// stateGameOver
// called each frame the gamestate is set to game over

void gameOverEnd()
{
  if (arduboy.justPressed(A_BUTTON | B_BUTTON))
  {
    gameState = STATE_MENU_MAIN;
    gameOverAndStageFase = 0;
  }
}


typedef void (*FunctionPointer) ();
const FunctionPointer PROGMEM gameOverFases[] =
{
  nextLevelWait,
  nextLevelWait,
  gameOverEnd,
};

void stateGameOver()
{
  ((FunctionPointer) pgm_read_word (&gameOverFases[gameOverAndStageFase]))();
  sprites.drawSelfMasked(22, 8, gameOver, 0);
  drawNumbers(36, 36, FONT_BIG, DATA_SCORE);
}
