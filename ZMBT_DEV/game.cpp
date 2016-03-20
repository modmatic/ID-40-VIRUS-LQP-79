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
  drawSurvivors();
  drawZombies();
  drawBullets();
  drawPlayer(coolGirl);
  drawWeapons();
  drawScore(86, 0, 0);
}

// stateGameNextLevel
// called each frame the gamestate is set to next level
void stateGamePrepareLevel()
{
  clearSurvivors();
  clearZombies();
  clearWeapons();

  //addSurvivor(64+16, 48);
  //addWeapon(128, 16, 1);
  //setDoorPosition(128, 16);

  level++;

  loadLevel();

  coolGirl.positionOnMapX = 16;
  coolGirl.positionOnMapY = 16;

  spawnZombie();
  spawnZombie();
  spawnZombie();
  spawnZombie();
  spawnZombie();
  spawnZombie();
  spawnZombie();
  spawnZombie();
  spawnZombie();
  spawnZombie();
  spawnZombie();
  spawnZombie();
  spawnZombie();
  spawnZombie();
  gameState = STATE_GAME_NEXT_LEVEL;
}

void stateGameNextLevel()
{
  drawScore(36, 36, 1);
  arduboy.drawBitmap(30, 8, nextLevel, 48, 16, WHITE);
  drawNextLevel();
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
  drawScore(36, 36, 1);
  if (buttons.justPressed(A_BUTTON | B_BUTTON))
  {
    gameState = STATE_MENU_MAIN;
  }
}
