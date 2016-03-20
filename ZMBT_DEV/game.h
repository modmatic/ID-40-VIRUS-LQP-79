#ifndef GAME_H
#define GAME_H

#include <Arduino.h>
#include "globals.h"
#include "level.h"
#include "enemies.h"
#include "elements.h"
#include "bullet.h"
#include "weapon.h"
#include "door.h"


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

extern byte level;

// methods prototypes ////////////////////////////////////////////////////////

void stateGamePlaying();
void stateGameNextLevel();
void stateGamePause();
void stateGameOver();


#endif
