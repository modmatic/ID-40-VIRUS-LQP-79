#include "menu.h"
#include "player.h"

// globals ///////////////////////////////////////////////////////////////////

byte menuSelection;
byte counter = 0;
boolean slideIn = false;

// method implementations ////////////////////////////////////////////////////
void drawTitleScreen()
{
  arduboy.drawBitmap(0, 0, titleScreen00, 62, 64, WHITE);
  arduboy.drawBitmap(62, 32, titleScreen01, 37, 32, WHITE);
  arduboy.drawBitmap(66, 0, titleScreen02, 62, 32, WHITE);
}


void stateMenuIntro()
{
  arduboy.drawBitmap(0, 8, TEAMarg, 128, 48, WHITE);
  counter++;
  if (counter > 180) gameState = STATE_MENU_MAIN;
}

void stateMenuMain()
{
  drawTitleScreen();
  for (byte i=0; i<4;i++)
  {
  if (((2+i)-menuSelection) != 0) sprites.drawSelfMasked(106, 25+(9*i), menuText, i);
  if (((2+i)-menuSelection) == 0) sprites.drawSelfMasked(104 - 5*slideIn, 25+(9*i), menuText, i);
  }
  if (buttons.justPressed(DOWN_BUTTON) && (menuSelection < 5)) menuSelection++;
  if (buttons.justPressed(UP_BUTTON) && (menuSelection > 2)) menuSelection--;
  if (buttons.justPressed(A_BUTTON | B_BUTTON)) gameState = menuSelection;
}

void stateMenuHelp()
{
  arduboy.drawBitmap(32, 0, qrcode, 64, 64, WHITE);
  if (buttons.justPressed(A_BUTTON | B_BUTTON)) gameState = STATE_MENU_MAIN;
}

void stateMenuPlay()
{
  level = 0;
  scorePlayer = 0;
  gameState = STATE_GAME_PREPARE_LEVEL;
  initializePlayer(coolGirl);
}

void stateMenuInfo()
{
  arduboy.drawBitmap(30, 0, titleScreen02, 62, 32, WHITE);
  arduboy.drawBitmap(92, 0, titleScreen03, 6, 32, WHITE);
  if (buttons.justPressed(A_BUTTON | B_BUTTON)) gameState = STATE_MENU_MAIN;
}

void stateMenuSoundfx()
{
  drawTitleScreen();
  if (buttons.justPressed(DOWN_BUTTON)) soundYesNo = true;
  if (buttons.justPressed(UP_BUTTON)) soundYesNo = false;
  if (buttons.justPressed(A_BUTTON | B_BUTTON))
  {
    arduboy.audio.save_on_off();
    gameState = STATE_MENU_MAIN;
  }
  if (soundYesNo == true) arduboy.audio.on();
  else arduboy.audio.off();
}

