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
  //drawWeapons();
  
  drawNumbers(86, 0, 0, 0);
  drawLife(coolGirl);
  drawAmountSurvivors();
  //drawZombieBlips();
}

int readLevelData(unsigned char index)
{
  return pgm_read_byte(levelInfo + ((int)level-1) * 14 + (int)index) * PLAYER_WIDTH;
}

// stateGameNextLevel
// called each frame the gamestate is set to next level
void stateGamePrepareLevel()
{
  clearSurvivors();
  clearPickups();
  clearZombies();

  level++;
  level = (level-1)%NUM_LEVELS + 1;
  displayLevel++;

  coolGirl.x = readLevelData(0);
  coolGirl.y = readLevelData(1);
  setDoorPosition(readLevelData(2), readLevelData(3));
  
  addSurvivor(readLevelData(4), readLevelData(5));
  addSurvivor(readLevelData(6), readLevelData(7));
  addSurvivor(readLevelData(8), readLevelData(9));
  addSurvivor(readLevelData(10), readLevelData(11));
  addSurvivor(readLevelData(12), readLevelData(13));
  
  gameState = STATE_GAME_NEXT_LEVEL;
}

void stateGameNextLevel()
{
  drawNumbers(36, 36, 1, 0);
  arduboy.drawBitmap(30, 8, nextLevel, 48, 16, WHITE);
  drawNumbers(82, 8, 1, 1);
  if (buttons.justPressed(A_BUTTON | B_BUTTON))
  {
    gameState = STATE_GAME_PLAYING;
  }
}

// stateGameOver
// called each frame the gamestate is set to game over
void stateGameOver()
{
  arduboy.drawBitmap(22, 8, gameOver, 84, 16, WHITE);
  drawNumbers(36, 36, 1, 0);
  if (buttons.justPressed(A_BUTTON | B_BUTTON))
  {
    gameState = STATE_MENU_MAIN;
  }
}
