#ifndef GAME_H
#define GAME_H

#include <Arduino.h>
#include "level.h"
#include "enemies.h"
#include "elements.h"
#include "bullet.h"

// constants /////////////////////////////////////////////////////////////////

//define menu states (on main menu)
#define STATE_MENU_INTRO         0
#define STATE_MENU_MAIN          1
#define STATE_MENU_HELP          2
#define STATE_MENU_PLAY          3
#define STATE_MENU_INFO          4
#define STATE_MENU_SOUNDFX       5

//define game states (on main menu)
#define STATE_GAME_PLAYING       6
#define STATE_GAME_PAUSE         7
#define STATE_GAME_OVER          8
#define STATE_GAME_NEXT_LEVEL    9


// globals ///////////////////////////////////////////////////////////////////

extern Arduboy arduboy;
extern byte gameState;


// methods ///////////////////////////////////////////////////////////////////

// stateGamePlaying
// called each frame the gamestate is set to playing
void stateGamePlaying()
{
  // Update
  updatePlayer(coolGuy);
  updateBullets();
  updateZombies();
  updateSurvivors();
  
  // Draw
  drawLevel();
  drawSurvivors();
  drawZombies();
  drawPlayer(coolGuy);
  drawBullets();
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

#endif
