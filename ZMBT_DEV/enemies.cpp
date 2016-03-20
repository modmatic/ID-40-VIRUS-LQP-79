#include "enemies.h"
#include "player.h"

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

// spawnZombie
// adds a zombie in a random place in the map
// returns true if success, false if failure
bool spawnZombie()
{
  int x = random(16, LEVEL_WIDTH-ZOMBIE_WIDTH-16);
  int y = random(16, LEVEL_HEIGHT-ZOMBIE_HEIGHT-16);
  
  if((x < coolGirl.positionOnMapX - WIDTH) || (x > coolGirl.positionOnMapX + WIDTH) || (y < coolGirl.positionOnMapY - HEIGHT) || (y > coolGirl.positionOnMapY + HEIGHT))
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
  byte id;
  byte tileXMax;
  byte tileYMax;
  byte tilex;
  byte tiley;
  
  int vx = 0;
  int vy = 0;
  
  if (arduboy.everyXFrames(ZOMBIE_STEP_DELAY))
  {
    // get movement: chase player
    if(obj.x < coolGirl.positionOnMapX) vx = ZOMBIE_SPEED;
    if(obj.x > coolGirl.positionOnMapX) vx = -ZOMBIE_SPEED;
    
    if(obj.y < coolGirl.positionOnMapY) vy = ZOMBIE_SPEED;
    if(obj.y > coolGirl.positionOnMapY) vy = -ZOMBIE_SPEED;
    
    if((obj.x < 0) || (obj.y < 0) || (obj.x >= LEVEL_WIDTH) || (obj.y >= LEVEL_HEIGHT))
    {
      obj.active = false;
      return;
    }
    
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
    
    // collide with other zombies
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
    
    // collide with player
    if(zombieCollision(obj, coolGirl.positionOnMapX, coolGirl.positionOnMapY, PLAYER_WIDTH, PLAYER_HEIGHT))
    {
      if(vx > 0)
        obj.x = coolGirl.positionOnMapX - ZOMBIE_WIDTH;
      else if(vx < 0)
        obj.x = coolGirl.positionOnMapX + PLAYER_WIDTH;
      
      hurtPlayer(coolGirl);
      vx = 0;
    }
    
    // collide with walls
    tileXMax = obj.x%TILE_WIDTH != 0;
    tileYMax = obj.y%TILE_HEIGHT != 0;
    for(tilex = obj.x/TILE_WIDTH; tilex < obj.x/TILE_WIDTH + 2 + tileXMax; tilex++)
    {
      for(tiley = obj.y/TILE_HEIGHT; tiley < obj.y/TILE_HEIGHT + 2 + tileYMax; tiley++)
      {
        if(getTileType(tilex, tiley) > 2)
        {
          if(vx < 0)
            obj.x = tilex*TILE_WIDTH + TILE_WIDTH;
          else if(vx > 0)
            obj.x = tilex*TILE_WIDTH - PLAYER_WIDTH;
          vx = 0;
        }
      }
    }
    
    // vertical physics
    obj.y += vy;
    
    // collide with other zombies
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
    
    // collide with player
    if(zombieCollision(obj, coolGirl.positionOnMapX, coolGirl.positionOnMapY, PLAYER_WIDTH, PLAYER_HEIGHT))
    {
      if(vy > 0)
        obj.y = coolGirl.positionOnMapY - ZOMBIE_HEIGHT;
      else if(vy < 0)
        obj.y = coolGirl.positionOnMapY + PLAYER_HEIGHT;
      
      hurtPlayer(coolGirl);
      vy = 0;
    }
    
    // collide with walls
    tileXMax = obj.x%TILE_WIDTH != 0;
    tileYMax = obj.y%TILE_HEIGHT != 0;
    for(tilex = obj.x/TILE_WIDTH; tilex < obj.x/TILE_WIDTH + 2 + tileXMax; tilex++)
    {
      for(tiley = obj.y/TILE_HEIGHT; tiley < obj.y/TILE_HEIGHT + 2 + tileYMax; tiley++)
      {
        if(getTileType(tilex, tiley) > 2)
        {
          if(vy < 0)
            obj.y = tiley*TILE_HEIGHT + TILE_HEIGHT;
          else if(vy > 0)
            obj.y = tiley*TILE_HEIGHT - PLAYER_HEIGHT;
          vy = 0;
        }
      }
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

// drawZombie
// draws a single zombie
void drawZombie(Enemy& obj)
{
  if(obj.active)
  {
    if(obj.flashTime > 0)
    {
      obj.flashTime--;
      //arduboy.drawCircle(obj.x - mapPositionX + ZOMBIE_WIDTH/2, obj.y - mapPositionY + ZOMBIE_HEIGHT/2, 16 - obj.flashTime*2, 1);
    }
    if((obj.flashTime % 4) < 2)
    {
      sprites.drawPlusMask(obj.x - mapPositionX, obj.y - mapPositionY, zombie_plus_mask, obj.frame + 8*obj.direction);
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
