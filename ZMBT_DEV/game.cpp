#include "game.h"


// method implementations ////////////////////////////////////////////////////

// stateGamePlaying
// called each frame the gamestate is set to playing
void stateGamePlaying()
{
  // Update
  updatePlayer(coolGirl);
  updateBullets();
  updateZombies();
  updateSurvivors();
  
  // Draw
  drawLevel();
  drawSurvivors();
  drawZombies();
  drawBullets();
  drawPlayer(coolGirl);
}

// stateGameNextLevel
// called each frame the gamestate is set to next level
void stateGameNextLevel()
{
  clearSurvivors();
  clearZombies();
  
  addZombie(64, 48);
  addSurvivor(64+16, 48);

  gameState = STATE_GAME_PLAYING;
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
  if (buttons.justPressed(A_BUTTON | B_BUTTON))
  {
    gameState = STATE_MENU_MAIN;
  }
}
