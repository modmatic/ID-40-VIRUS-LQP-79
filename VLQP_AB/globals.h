#ifndef GLOBALS_H
#define GLOBALS_H

#include "Arglib.h"

// globals ///////////////////////////////////////////////////////////////////

extern Arduboy arduboy;
extern Sprites sprites;
extern SimpleButtons buttons;
extern byte gameState;
extern unsigned long scorePlayer;
extern boolean soundYesNo;

#endif

// function prototypes ///////////////////////////////////////////////////////

short burp(short start, short goal, unsigned char step);
