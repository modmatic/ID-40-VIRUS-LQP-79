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

short converge(short start, short goal, short step);
short burp(short start, short goal, short step);
