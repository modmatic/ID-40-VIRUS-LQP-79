#include "game.h"

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
  drawZombies();
  drawSurvivors();
  drawBullets();
  drawPlayer(coolGirl);
  drawWeapons();
  drawNumbers(86, 0, 0,0);
  drawLife(coolGirl);
  drawAmountSurvivors();
}

// stateGameNextLevel
// called each frame the gamestate is set to next level
void stateGamePrepareLevel()
{
  clearSurvivors();
  clearZombies();
  clearWeapons();

  addSurvivor(64 + 16, 48);
  addSurvivor(450, 224);
  //addWeapon(128, 16, 1);
  setDoorPosition(128, 16);

  level++;

  coolGirl.positionOnMapX = 16;
  coolGirl.positionOnMapY = 16;

  for (byte spawnZombies; spawnZombies < 14; spawnZombies++)
  {
    spawnZombie();
  }

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

// stateGamePause
// called each frame the gamestate is set to paused
void stateGamePause()
{
  if (buttons.justPressed(A_BUTTON | B_BUTTON))
  {
    gameState = STATE_MENU_MAIN;
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
