#include "enemies.h"
#include "player.h"
#include "pickup.h"

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
  obj.health = 2;
  obj.flashTime = 0;
}

// spawnZombie
// adds a zombie in a random place in the map
// returns true if success, false if failure
bool spawnZombie()
{
  int x = random(16, LEVEL_WIDTH-ZOMBIE_WIDTH-16);
  int y = random(16, LEVEL_HEIGHT-ZOMBIE_HEIGHT-16);
  
  if((x < coolGirl.x - WIDTH) || (x > coolGirl.x + WIDTH) || (y < coolGirl.y - HEIGHT) || (y > coolGirl.y + HEIGHT))
  {
    return addZombie(x, y);
  }
  
  return false;
}


// addZombie
// searches the zombies list for an empty slot, adds one if available
// returns true if successful, false otherwise
bool addZombie(int x, int y)
{
  byte id;
  
  for(id=0; id<ZOMBIE_MAX; id++)
  {
    if(!zombies[id].active)
    {
      setZombie(zombies[id], x, y);
      return true;
      break;
    }
  }
  
  return false;
}


// updateZombie
// updates the zombie according to game rules
// zombies are "removed" (set inactive) when health reaches zero
void updateZombie(Enemy& obj)
{
  char vx = 0;
  char vy = 0;
  
  if (arduboy.everyXFrames(ZOMBIE_STEP_DELAY))
  {
    ///////////
    // input //
    ///////////
    
    // chase player
    if(obj.x < coolGirl.x) vx = ZOMBIE_SPEED;
    if(obj.x > coolGirl.x) vx = -ZOMBIE_SPEED;
    
    if(obj.y < coolGirl.y) vy = ZOMBIE_SPEED;
    if(obj.y > coolGirl.y) vy = -ZOMBIE_SPEED;
    
    // if out of bounds, delete this
    if((obj.x < 0) || (obj.y < 0) || (obj.x >= LEVEL_WIDTH) || (obj.y >= LEVEL_HEIGHT))
    {
      obj.active = false;
      return;
    }
  
    // update orientation
    if(vx < 0)
      obj.direction = ENEMY_FACING_WEST;
    else if(vx > 0)
      obj.direction = ENEMY_FACING_EAST;
    
    ////////////////////////
    // horizontal physics //
    ////////////////////////
    
    // update position
    obj.x += vx;
    
    // collide with other zombies
    zombieCollide(obj.x, obj.y, true, vx, ZOMBIE_WIDTH, ZOMBIE_HEIGHT);
    
    // collide with player
    if(zombieCollision(obj, coolGirl.x, coolGirl.y, PLAYER_WIDTH, PLAYER_HEIGHT))
    {
      if(vx > 0)
        obj.x = coolGirl.x - ZOMBIE_WIDTH;
      else if(vx < 0)
        obj.x = coolGirl.x + PLAYER_WIDTH;
      
      playerHealthOffset(coolGirl, -1);
      vx = 0;
    }
    
    // collide with walls
    mapCollide(obj.x, obj.y, true, vx, ZOMBIE_WIDTH, ZOMBIE_HEIGHT);
  
    //////////////////////
    // vertical physics //
    //////////////////////
    
    // update position
    obj.y += vy;
    
    // collide with other zombies
    zombieCollide(obj.x, obj.y, false, vy, ZOMBIE_WIDTH, ZOMBIE_HEIGHT);
    
    // collide with player
    if(zombieCollision(obj, coolGirl.x, coolGirl.y, PLAYER_WIDTH, PLAYER_HEIGHT))
    {
      if(vy > 0)
        obj.y = coolGirl.y - ZOMBIE_HEIGHT;
      else if(vy < 0)
        obj.y = coolGirl.y + PLAYER_HEIGHT;
      
      playerHealthOffset(coolGirl, -1);
      vy = 0;
    }
    
    // collide with walls
    mapCollide(obj.x, obj.y, false, vy, ZOMBIE_WIDTH, ZOMBIE_HEIGHT);
    
    ///////////////
    // animation //
    ///////////////
    
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

/*
void drawZombieBlips()
{
  short drawX, drawY;
  byte id;
  
  for(id=0; id<ZOMBIE_MAX; id++)
  {
    if(!zombies[id].active) continue;
    drawX = zombies[id].x - mapPositionX;
    drawY = zombies[id].y - mapPositionY;
    byte drawColor = (arduboy.frameCount % 16) < 8;

    if(drawX < 0 && drawX > -WIDTH/2)
    {
      arduboy.drawPixel(1, drawY + ZOMBIE_HEIGHT/2, drawColor);
      arduboy.drawPixel(1, drawY + ZOMBIE_HEIGHT/2+1, drawColor);
      arduboy.drawPixel(2, drawY + ZOMBIE_HEIGHT/2, drawColor);
      arduboy.drawPixel(2, drawY + ZOMBIE_HEIGHT/2+1, drawColor);
    }
    else if(drawX > WIDTH && drawX < WIDTH/2+WIDTH)
    {
      arduboy.drawPixel(WIDTH-1, drawY + ZOMBIE_HEIGHT/2, drawColor);
      arduboy.drawPixel(WIDTH-1, drawY + ZOMBIE_HEIGHT/2+1, drawColor);
      arduboy.drawPixel(WIDTH-2, drawY + ZOMBIE_HEIGHT/2, drawColor);
      arduboy.drawPixel(WIDTH-2, drawY + ZOMBIE_HEIGHT/2+1, drawColor);
    }
    else if(drawY < 0 && drawY > -HEIGHT/2)
    {
      arduboy.drawPixel(drawX + ZOMBIE_WIDTH/2, 1, drawColor);
      arduboy.drawPixel(drawX + ZOMBIE_WIDTH/2+1, 1, drawColor);
      arduboy.drawPixel(drawX + ZOMBIE_WIDTH/2, 2, drawColor);
      arduboy.drawPixel(drawX + ZOMBIE_WIDTH/2+1, 2, drawColor);
    }
    else if(drawY > HEIGHT && drawY < HEIGHT/2+HEIGHT)
    {
      arduboy.drawPixel(drawX + ZOMBIE_HEIGHT/2, HEIGHT-1, drawColor);
      arduboy.drawPixel(drawX + ZOMBIE_HEIGHT/2+1, HEIGHT-1, drawColor);
      arduboy.drawPixel(drawX + ZOMBIE_HEIGHT/2, HEIGHT-2, drawColor);
      arduboy.drawPixel(drawX + ZOMBIE_HEIGHT/2+1, HEIGHT-2, drawColor);
    }
  }
  
}
*/


// drawZombie
// draws a single zombie
void drawZombie(Enemy& obj)
{
  short drawX, drawY;
  if(obj.active)
  {
    if(obj.flashTime > 0)
    {
      obj.flashTime--;
    }
    if((obj.flashTime % 4) < 2)
    {
      drawX = obj.x - mapPositionX;
      drawY = obj.y - mapPositionY;
      
      sprites.drawPlusMask(drawX, drawY, zombie_plus_mask, obj.frame + 8*obj.direction);
    }
  }
  else if(obj.flashTime > 0)
  {
    obj.flashTime--;
    arduboy.drawCircle(obj.x - mapPositionX + ZOMBIE_WIDTH/2, obj.y - mapPositionY + ZOMBIE_HEIGHT/2, 12 - obj.flashTime*2, 1);
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
    drawZombie(zombies[id]);
  }
}


// zombieHealthOffset
// takes a value to be added to zombie health
// kills the zombie if health goes below zero
bool zombieHealthOffset(Enemy& obj, char amount)
{
  obj.health += amount;
  
  // killed
  if(obj.health <= 0)
  {
    arduboy.tunes.tone(220, 20);
    obj.flashTime = ZOMBIE_FLASH_TIME;
    obj.active = false;
    rollingScore += 100;
    addPickup(obj.x + 4, obj.y + 4);
  }
  else if(amount < 0)
  {
    obj.flashTime = ZOMBIE_FLASH_TIME;
    arduboy.tunes.tone(640, 20);
  }
}


// zombieCollision
// takes zombie id, collision box to test against
// returns true if collision boxes intersect
bool zombieCollision(Enemy& obj, int x, int y, char w, char h)
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

void zombieCollide(int &x, int &y, bool horizontal, char &vel, char w, char h)
{
  byte id;
  for(id=0; id<ZOMBIE_MAX; id++)
  {
    if(zombieCollision(zombies[id], x, y, w, h))
    {
      if(x == zombies[id].x && y == zombies[id].y) continue;
      if(horizontal)
      {
        if(vel > 0)
          x = zombies[id].x - w;
        else if(vel < 0)
          x = zombies[id].x + ZOMBIE_WIDTH;
      }
      else
      {
        if(vel > 0)
          y = zombies[id].y - h;
        else if(vel < 0)
          y = zombies[id].y + ZOMBIE_HEIGHT;
      }
      vel = 0;
    }
  }
}
