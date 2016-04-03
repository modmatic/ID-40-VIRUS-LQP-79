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

void setSlidersToZero()
{
  slideCount02 = 0;
  slideCount01 = 0;
  slideIn = false;
  slideInToo = false;
}

void setSlideInToZero()
{
  slideIn = false;
  slideCount02 = 0;
}

void makeItSlide()
{
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
    arduboy.drawBitmap(127 - slideCount01 + (8 * i) , 25, smallMask, 8, 8, BLACK);
  }
  if (menuSelection == 2 && slideIn) arduboy.drawBitmap(98 , 25, smallMask, 8, 8, BLACK);
  for (byte i = 0; i < 4; i++)
  {
    if (((2 + i) - menuSelection) != 0)
    {
      sprites.drawSelfMasked(128 - slideCount01, 25 + (9 * i), menuText, i);
    }
    if (((2 + i) - menuSelection) == 0) sprites.drawSelfMasked(128 - slideCount01 - (2 * slideInToo) - (5 * slideIn), 25 + (9 * i), menuText, i);
  }
  if (buttons.justPressed(DOWN_BUTTON) && (menuSelection < 5))
  {
    menuSelection++;
    setSlideInToZero();
  }
  if (buttons.justPressed(UP_BUTTON) && (menuSelection > 2))
  {
    menuSelection--;
    setSlideInToZero();
  }
  if (buttons.justPressed(A_BUTTON | B_BUTTON))
  {
    setSlidersToZero();
    gameState = menuSelection;
  }
  makeItSlide();
}

void stateMenuHelp()
{
  arduboy.drawBitmap(32, 0, qrcode, 64, 64, WHITE);
  if (buttons.justPressed(A_BUTTON | B_BUTTON)) gameState = STATE_MENU_MAIN;
}

void stateMenuPlay()
{
  level = 0;
  displayLevel = 0;
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
  for (byte i = 0; i < 3; i++)
  {
    arduboy.drawBitmap(127 - slideCount01 + (8 * i) , 25, smallMask, 8, 8, BLACK);
  }
  
  if (buttons.justPressed(DOWN_BUTTON))
  {
    soundYesNo = true;
    setSlideInToZero();
  }
  if (buttons.justPressed(UP_BUTTON))
  {
    soundYesNo = false;
    setSlideInToZero();
  }
  if (buttons.justPressed(A_BUTTON | B_BUTTON))
  {
    setSlidersToZero();
    arduboy.audio.save_on_off();
    gameState = STATE_MENU_MAIN;
  }
  
  sprites.drawSelfMasked(128 - slideCount01, 25 , menuText, 4);
  if (soundYesNo == true)
  {
    arduboy.audio.on();
    sprites.drawSelfMasked(128 - slideCount01, 25 + 9, menuText, 5);
    sprites.drawSelfMasked(128 - slideCount01 - (2 * slideInToo) - (5 * slideIn), 25 + +9+9, menuText, 6);
  }
  else
  {
    arduboy.audio.off();
    sprites.drawSelfMasked(128 - slideCount01, 25 + 9 + 9, menuText, 6);
    sprites.drawSelfMasked(128 - slideCount01 - (2 * slideInToo) - (5 * slideIn), 25 + 9, menuText, 5);
  }
  makeItSlide();
}

