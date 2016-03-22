#include "globals.h"

// globals ///////////////////////////////////////////////////////////////////

Arduboy arduboy;
Sprites sprites(arduboy);
SimpleButtons buttons(arduboy);
unsigned long scorePlayer;
boolean soundYesNo;
byte gameState;

// function implementations //////////////////////////////////////////////////

short converge(short start, short goal, short step)
{
  if(start < goal)
  {
    start += step;
    if(start > goal) return goal;
  }
  else if(start > goal)
  {
    start -= step;
    if(start < goal) return goal;
  }
  
  return start;
}
/*
byte rconverge(short start, short goal, short step, short range)
{
  if(start < goal)
  {
    if((goal - start) < (start + goal)%range) // if positive is faster
      return start+1;
    return start-1;
      
  
  if(start == goal) return goal;
  short next;
  
  if(((start-goal)%range) < ((goal-start)%range)) // step negative
  {
    return (start - step)%range;
  }
  else // step positive
  {
    return (start + step)%range;
  }
  
  return goal;
  
}
*/