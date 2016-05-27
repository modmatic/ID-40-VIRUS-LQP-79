#include "game.h"
#include "enemies.h"
#include "pickup.h"

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

  drawNumbers(86, 0, 0, 0);
  drawLife(coolGirl);
  drawAmountSurvivors();
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
  
  coolGirl.x = readPlayerAndExitData(0);
  coolGirl.y = readPlayerAndExitData(1);
  setDoorPosition(readPlayerAndExitData(2), readPlayerAndExitData(3));

  for (byte i = 0; i < ((displayLevel-1) /NUM_LEVELS) + 2; i++)
  {
    addSurvivor(readSurvivorData(2 * i), readSurvivorData((2 * i) + 1));
  }

  pickupsCounter = 0;

  gameState = STATE_GAME_NEXT_LEVEL;
}

void stateGameNextLevel()
{
  drawNumbers(36, 36, 1, 0);
  sprites.drawSelfMasked(30, 8, nextLevel, 0);
  drawNumbers(82, 8, 1, 1);
  if (arduboy.justPressed(A_BUTTON | B_BUTTON))
  {
    gameState = STATE_GAME_PLAYING;
  }
}

// stateGameOver
// called each frame the gamestate is set to game over
void stateGameOver()
{
  sprites.drawSelfMasked(22, 8, gameOver, 0);
  drawNumbers(36, 36, 1, 0);
  if (arduboy.justPressed(A_BUTTON | B_BUTTON))
  {
    gameState = STATE_MENU_MAIN;
  }
}
