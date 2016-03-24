/*
 VIRUS LQP-79: http://www.team-arg.org/zmbt-manual.html

 Arduboy version 0.8:  http://www.team-arg.org/zmbt-downloads.html

 MADE by TEAM a.r.g. : http://www.team-arg.org/more-about.html

 2016 - FUOPY - JO3RI - STG - JUSTIN CRY

 Game License: MIT : https://opensource.org/licenses/MIT

 */

//determine the game
#define GAME_ID 40

#include "Arglib.h"
#include "globals.h"
//#include <ArduboyExtra.h>
//#include <sprites.h>
//#include <simple_buttons.h>
#include "menu.h"
#include "player.h"
#include "enemies.h"
#include "game.h"
#include "elements.h"
#include "bitmaps.h"
//#include "inputs.h"
#include "level.h"


typedef void (*FunctionPointer) ();
FunctionPointer mainGameLoop[] =
{
  stateMenuIntro,
  stateMenuMain,
  stateMenuHelp,
  stateMenuPlay,
  stateMenuInfo,
  stateMenuSoundfx,
  stateGamePrepareLevel,
  stateGameNextLevel,
  stateGamePlaying,
  stateGameOver,
};

void setup()
{
  arduboy.start();
  arduboy.setFrameRate(60);
  gameState = 0;
  if (EEPROM.read(EEPROM_AUDIO_ON_OFF)) soundYesNo = true;
  menuSelection = 3;
}

void loop() {
  if (!(arduboy.nextFrame())) return;
  buttons.poll();
  if (soundYesNo == true) arduboy.audio.on();
  else arduboy.audio.off();
  arduboy.clearDisplay();
  mainGameLoop[gameState]();
  arduboy.display();
}
