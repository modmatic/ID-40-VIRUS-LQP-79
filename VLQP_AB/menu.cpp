#include "menu.h"
#include "player.h"

// globals ///////////////////////////////////////////////////////////////////

byte menuSelection = STATE_MENU_PLAY;
byte counter = 0;
byte slideCount01 = 0;
byte slideCount02 = 0;

// method implementations ////////////////////////////////////////////////////
void drawTitleScreen()
{
  sprites.drawSelfMasked(0, 0, titleScreen00, 0);
  sprites.drawSelfMasked(62, 32, titleScreen01, 0);
  sprites.drawSelfMasked(66, 0, titleScreen02, 0);
}

void setSlidersToZero()
{
  slideCount02 = 0;
  slideCount01 = 0;
}


void makeItSlide()
{
  slideCount01++;
  if (slideCount01 > 22)
  {
    slideCount02++;
    slideCount01 = 22;
  }

  if (slideCount02 > 5)
  {
    slideCount02 = 5;
  }
}

void stateMenuIntro()
{
  for (byte i = 0; i < 4; i++) sprites.drawSelfMasked(32 * i, 10, TEAMarg, i);
  sprites.drawSelfMasked(43, 50, TEAM_argPart5, 0);
  counter++;
  if (counter > 180) gameState = STATE_MENU_MAIN;
}

void stateMenuMain()
{
  drawTitleScreen();
  for (byte i = 0; i < 3; i++)
  {
    sprites.drawOverwrite(127 - slideCount01 + (8 * i) , 25, smallMask, 0);
  }
  if (menuSelection == 2) sprites.drawOverwrite(98 , 25, smallMask, 0);
  for (byte i = 0; i < 4; i++)
  {
    if (((2 + i) - menuSelection) != 0)
    {
      sprites.drawSelfMasked(128 - slideCount01, 25 + (9 * i), menuText, i);
    }
    if (((2 + i) - menuSelection) == 0) sprites.drawSelfMasked(128 - slideCount01 - slideCount02, 25 + (9 * i), menuText, i);
  }
  if (buttons.justPressed(DOWN_BUTTON) && (menuSelection < 5))
  {
    menuSelection++;
    slideCount02 = 0;
  }
  if (buttons.justPressed(UP_BUTTON) && (menuSelection > 2))
  {
    menuSelection--;
    slideCount02 = 0;
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
  for (byte i = 0; i < 2; i++) sprites.drawSelfMasked(32, 32 * i, qrcode, i);
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
  sprites.drawSelfMasked(30, 0, titleScreen02, 0);
  sprites.drawSelfMasked(92, 0, titleScreen03, 0);

  sprites.drawSelfMasked(39, 33, madeBy00, 0);
  sprites.drawSelfMasked(10, 33, madeBy01, 0);
  sprites.drawSelfMasked(10, 47, madeBy02, 0);


  if (buttons.justPressed(A_BUTTON | B_BUTTON)) gameState = STATE_MENU_MAIN;
}

void stateMenuSoundfx()
{
  drawTitleScreen();
  for (byte i = 0; i < 3; i++)
  {
    sprites.drawOverwrite(127 - slideCount01 + (8 * i) , 25, smallMask, 0);
  }

  if (buttons.justPressed(DOWN_BUTTON))
  {
    soundYesNo = true;
    slideCount02 = 0;
  }
  if (buttons.justPressed(UP_BUTTON))
  {
    soundYesNo = false;
    slideCount02 = 0;
  }
  if (buttons.justPressed(A_BUTTON | B_BUTTON))
  {
    setSlidersToZero();
    arduboy.audio.saveOnOff();
    gameState = STATE_MENU_MAIN;
  }

  sprites.drawSelfMasked(128 - slideCount01, 25 , menuText, 4);
  if (soundYesNo == true)
  {
    arduboy.audio.on();
    sprites.drawSelfMasked(128 - slideCount01, 34, menuText, 5);
    sprites.drawSelfMasked(128 - slideCount01 - slideCount02, 43, menuText, 6);
  }
  else
  {
    arduboy.audio.off();
    sprites.drawSelfMasked(128 - slideCount01, 43, menuText, 6);
    sprites.drawSelfMasked(128 - slideCount01 - slideCount02, 34, menuText, 5);
  }
  makeItSlide();
}

