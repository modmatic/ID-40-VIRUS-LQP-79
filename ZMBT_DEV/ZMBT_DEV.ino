/*
 Zombie Trash: http://www.team-arg.org/zmbt-manual.html

 Arduboy version 0.1:  http://www.team-arg.org/zmbt-downloads.html

 MADE by TEAM a.r.g. : http://www.team-arg.org/more-about.html

 2016 - JO3RI - FUOPY

 Game License: MIT : https://opensource.org/licenses/MIT

 */

//determine the game
#define GAME_ID 40

#include "Arglib.h"
//#include <ArduboyExtra.h>
//#include <sprites.h>
//#include <simple_buttons.h>
#include "menu.h"
#include "player.h"
#include "game.h"
#include "enemies.h"
#include "elements.h"
#include "bitmaps.h"
#include "inputs.h"

Arduboy arduboy;
SimpleButtons buttons (arduboy);
Sprites sprites(arduboy);
unsigned long scorePlayer;

byte gameState;

typedef void (*FunctionPointer) ();
FunctionPointer mainGameLoop[] =
{
  stateMenuIntro,
  stateMenuMain,
  stateMenuHelp,
  stateMenuPlay,
  stateMenuInfo,
  stateMenuSoundfx,
  stateGamePlaying,
  stateGamePause,
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

