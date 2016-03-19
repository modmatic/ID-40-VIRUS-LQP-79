#ifndef GAME_H
#define GAME_H

#include <Arduino.h>
#include "enemies.h"
#include "elements.h"

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


extern Arduboy arduboy;
extern byte gameState;
byte zombieAmount;
byte survivorAmount;

void stateGamePlaying()
{
  checkInputs();
  drawZombies(zombieAmount);
  drawSurvivors(survivorAmount);
  drawPlayer();
}

void stateGameNextLevel()
{
  zombieAmount = 8;
  survivorAmount = 2;
  createZombies(zombieAmount);
  createSurvivors(survivorAmount);
  gameState = STATE_GAME_PLAYING;
}
void stateGamePause()
{
  if (buttons.justPressed(A_BUTTON | B_BUTTON))
  {
    gameState = STATE_MENU_MAIN;
  }
}
void stateGameOver()
{
  if (buttons.justPressed(A_BUTTON | B_BUTTON))
  {
    gameState = STATE_MENU_MAIN;
  }
}

#endif
