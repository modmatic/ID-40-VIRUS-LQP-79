#include "enemies.h"

// globals ///////////////////////////////////////////////////////////////////

Enemy zombies[ZOMBIE_MAX];


// method implementations ////////////////////////////////////////////////////

// setZombie
// sets the position of a zombie, and enables that instance
void setZombie(Enemy& obj, int x, int y)
{
  obj.frame = 0;
  obj.active = true;
  obj.direction = ENEMY_FACING_WEST;
  obj.x = x;
  obj.y = y;
  obj.health = 3;
  obj.flashTime = 0;
}


// addZombie
// searches the zombies list for an empty slot, adds one if available
void addZombie(int x, int y)
{
  byte id;
  
  for(id=0; id<ZOMBIE_MAX; id++)
  {
    if(!zombies[id].active)
    {
      setZombie(zombies[id], x, y);
      break;
    }
  }
}


// updateZombie
// updates the zombie according to game rules
// zombies are "removed" (set inactive) when health reaches zero
void updateZombie(Enemy& obj)
{
  byte id;
  
  int vx = 0;
  int vy = 0;
  
  if (arduboy.everyXFrames(ZOMBIE_STEP_DELAY))
  {
    // get movement: chase player
    if(obj.x < coolGirl.positionOnMapX) vx = ZOMBIE_SPEED;
    if(obj.x > coolGirl.positionOnMapX) vx = -ZOMBIE_SPEED;
    
    if(obj.y < coolGirl.positionOnMapY) vy = ZOMBIE_SPEED;
    if(obj.y > coolGirl.positionOnMapY) vy = -ZOMBIE_SPEED;
    
    //if(obj.x + ZOMBIE_WIDTH < coolGirl.positionOnMapX) vx = ZOMBIE_SPEED;
    //if(obj.x > coolGirl.positionOnMapX + PLAYER_WIDTH) vx = -ZOMBIE_SPEED;
    
    //if(obj.y + ZOMBIE_HEIGHT < coolGirl.positionOnMapY) vy = ZOMBIE_SPEED;
    //if(obj.y > coolGirl.positionOnMapY + PLAYER_HEIGHT) vy = -ZOMBIE_SPEED;
  
    // update orientation
    if(vx < 0)
      obj.direction = ENEMY_FACING_WEST;
    else if(vx > 0)
      obj.direction = ENEMY_FACING_EAST;
    
    // horizontal physics
    obj.x += vx;
    
    for(id=0; id<ZOMBIE_MAX; id++)
    {
      if(zombieCollision(zombies[id], obj.x, obj.y, ZOMBIE_WIDTH, ZOMBIE_HEIGHT))
      {
        if(&(zombies[id]) == &obj) continue;
        
        if(vx > 0)
          obj.x = zombies[id].x - ZOMBIE_WIDTH;
        else if(vx < 0)
          obj.x = zombies[id].x + ZOMBIE_WIDTH;
        vx = 0;
        break;
      }
    }
    
    if(zombieCollision(obj, coolGirl.positionOnMapX, coolGirl.positionOnMapY, PLAYER_WIDTH, PLAYER_HEIGHT))
    {
      if(vx > 0)
        obj.x = coolGirl.positionOnMapX - ZOMBIE_WIDTH;
      else if(vx < 0)
        obj.x = coolGirl.positionOnMapX + PLAYER_WIDTH;
      
      vx = 0;
    }
    
    
    
    // vertical physics
    obj.y += vy;
    
    for(id=0; id<ZOMBIE_MAX; id++)
    {
      if(zombieCollision(zombies[id], obj.x, obj.y, ZOMBIE_WIDTH, ZOMBIE_HEIGHT))
      {
        if(&(zombies[id]) == &obj) continue;
        
        if(vy > 0)
          obj.y = zombies[id].y - ZOMBIE_HEIGHT;
        else if(vy < 0)
          obj.y = zombies[id].y + ZOMBIE_HEIGHT;
        vy = 0;
        break;
      }
    }
    
    if(zombieCollision(obj, coolGirl.positionOnMapX, coolGirl.positionOnMapY, PLAYER_WIDTH, PLAYER_HEIGHT))
    {
      if(vy > 0)
        obj.y = coolGirl.positionOnMapY - ZOMBIE_HEIGHT;
      else if(vy < 0)
        obj.y = coolGirl.positionOnMapY + PLAYER_HEIGHT;
      
      vy = 0;
    }
    
    if(vx || vy)
    {
      // Advance animation frame
      if (arduboy.everyXFrames(ZOMBIE_FRAME_SKIP)) obj.frame++;
      
      // Just 4 frames
      if (obj.frame >= ZOMBIE_FRAME_COUNT ) obj.frame = 0;
    }
    else
    {
      obj.frame = 0;
    }
  }
  
  
  
  if(obj.health == 0)
  {
    obj.active = false;
  }
}


// updateZombies
// updates every active zombie in the list
void updateZombies()
{
  byte i;
  
  for(i=0; i<ZOMBIE_MAX; i++)
  {
    if(!zombies[i].active) continue;
    updateZombie(zombies[i]);
  }
}


// drawZombies
// draws every active zombie in the zombie list
void drawZombies()
{
  byte id;
  
  // Draw all the zombies!
  for (id=0; id<ZOMBIE_MAX; id++)
  {
    if(!zombies[id].active) continue;
    sprites.drawPlusMask(zombies[id].x - mapPositionX, zombies[id].y - mapPositionY, zombie_plus_mask, zombies[id].frame + 8*zombies[id].direction);
  }
}


// zombieHealthOffset
// takes a value to be added to zombie health
// kills the zombie if health goes below zero
bool zombieHealthOffset(Enemy& obj, char amount)
{
  obj.health += amount;
  
  
  if(obj.health <= 0)
  {
    arduboy.tunes.tone(220, 20);
    obj.active = false;
  }
  else if(amount < 0)
  {
    arduboy.tunes.tone(640, 20);
  }
}


// zombieCollision
// takes zombie id, collision box to test against
// returns true if collision boxes intersect
bool zombieCollision(Enemy& obj, int x, int y, int w, int h)
{
  return
    ( obj.active ) &&
    ( obj.x < x+w ) &&
    ( obj.x + ZOMBIE_WIDTH > x ) &&
    ( obj.y < y+h ) &&
    ( obj.y + ZOMBIE_HEIGHT > y );
}

// clearZombies
// clears the entire list of zombies
void clearZombies()
{
  byte id;
  
  for(id=0; id<ZOMBIE_MAX; id++)
  {
    zombies[id].active = false;
  }
}
