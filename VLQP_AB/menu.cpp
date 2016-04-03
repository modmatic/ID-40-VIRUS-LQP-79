#include "menu.h"
#include "player.h"

// globals ///////////////////////////////////////////////////////////////////

byte menuSelection;
byte counter = 0;
boolean slideIn = false;
boolean slideInToo = false;
byte slideCount01 = 0;
byte slideCount02 = 0;

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
  for (byte i = 0; i < 3; i++)
  {
    arduboy.drawBitmap(127 - slideCount01 + (8*i) , 25, smallMask, 8, 8, BLACK);
  }
  if (menuSelection == 2 && slideIn) arduboy.drawBitmap(98 , 25, smallMask, 8, 8, BLACK);
  for (byte i = 0; i < 4; i++)
  {
    if (((2 + i) - menuSelection) != 0)
    {
      sprites.drawSelfMasked(128 - slideCount01, 25 + (9 * i), menuText, i);
    }
    if (((2 + i) - menuSelection) == 0) sprites.drawSelfMasked(128 - slideCount01 - (2*slideInToo) - (5 * slideIn), 25 + (9 * i), menuText, i);
  }
  if (buttons.justPressed(DOWN_BUTTON) && (menuSelection < 5))
  {
    menuSelection++;
    slideIn = false;
    slideCount02 = 0;
  }
  if (buttons.justPressed(UP_BUTTON) && (menuSelection > 2))
  {
    menuSelection--;
    slideIn = false;
    slideCount02 = 0;
  }
  if (buttons.justPressed(A_BUTTON | B_BUTTON))
  {
    slideCount02 = 0;
    slideCount01 = 0;
    slideIn = false;
    slideInToo = false;
    gameState = menuSelection;
  }
  slideCount01++;
  if (slideCount01 > 22)
  {
    slideInToo = true;
    slideCount02++;
    slideCount01 = 22;
  }

  if (slideCount02 > 5)
  {
    slideCount02 = 5;
    slideIn = true;
  }
  //if (arduboy.everyXFrames(6)) slideIn = true;
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

  arduboy.drawBitmap(39, 33, madeBy00, 57, 32, WHITE);
  arduboy.drawBitmap(10, 33, madeBy01, 21, 8, WHITE);
  arduboy.drawBitmap(10, 47, madeBy02, 16, 8, WHITE);
  
  
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

