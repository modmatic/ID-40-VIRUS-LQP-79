#include "player.h"
#include "door.h"
#include "menu.h"

// globals ///////////////////////////////////////////////////////////////////

Player coolGirl = {
  .positionOnScreenX = 25,
  .positionOnScreenY = 25,
  .walking = false,
  .direction = PLAYER_FACING_SOUTH,
  .frame = 0,
  .shotDelay = 10,
  .vx = 0,
  .vy = 0,
  .positionOnMapX = coolGirl.positionOnScreenX,
  .positionOnMapY = coolGirl.positionOnScreenY,
  .health = 3,
  .flashTime = 0,
  .camDirection = PLAYER_FACING_SOUTH,
  .diagonalTime = 0
};

int rollingScore = 0;

// method implementations  ///////////////////////////////////////////////////

// initializePlayer
// sets the default values for player
void initializePlayer(Player& obj)
{
  scorePlayer = 0;
  rollingScore = 0;
  obj.direction = PLAYER_FACING_SOUTH,
  obj.health = 3;
  obj.flashTime = 0;
}

// updatePlayer
// updates the player according to game rules
void updatePlayer(Player& obj)
{
  // Input velocity
  short vx = 0;
  short vy = 0;
  
  short tilex;
  short tiley;
  
  byte id;
  byte tileXMax;
  byte tileYMax;
  byte inputDirection = obj.direction;
  
  // Read input
  bool left = buttons.pressed(LEFT_BUTTON);
  bool right = buttons.pressed(RIGHT_BUTTON);
  bool up = buttons.pressed(UP_BUTTON);
  bool down = buttons.pressed(DOWN_BUTTON);
  bool rungun = buttons.pressed(A_BUTTON);
  bool standgun = buttons.pressed(B_BUTTON);
  bool strafegun = rungun;

  // Stop or continue walking animation
  obj.walking = up || down || left || right;
  obj.walking = (standgun && !rungun) ? false : obj.walking;
  
  if(obj.diagonalTime > 0)
    obj.diagonalTime--;
  
  if((up&&left) || (down&&left) || (up&&right) || (down&&right))
    obj.diagonalTime = 4;
  
  // Bullet timer
  if(obj.shotDelay > 0) obj.shotDelay--;
  
  // Update horizontal physics
  if(left)
  {
    vx = -1;
  }
  else if(right)
  {
    vx = 1;
  }
 
  if(strafegun || !standgun)
  {
    //obj.x += vx;
    obj.positionOnMapX += vx;
  }
  
  // collide with zombies
  for(id=0; id<ZOMBIE_MAX; id++)
  {
    if(zombieCollision(zombies[id], obj.positionOnMapX, obj.positionOnMapY, PLAYER_WIDTH, PLAYER_HEIGHT))
    {
      if(vx > 0)
        obj.positionOnMapX = zombies[id].x - PLAYER_WIDTH;
      else if(vx < 0)
        obj.positionOnMapX = zombies[id].x + ZOMBIE_WIDTH;
      vx = 0;
      hurtPlayer(obj);
      break;
    }
  }
  
  // collide with walls
  tileXMax = obj.positionOnMapX%TILE_WIDTH != 0;
  tileYMax = obj.positionOnMapY%TILE_HEIGHT != 0;
  for(tilex = obj.positionOnMapX/TILE_WIDTH; tilex < obj.positionOnMapX/TILE_WIDTH + 2 + tileXMax; tilex++)
  {
    for(tiley = obj.positionOnMapY/TILE_HEIGHT; tiley < obj.positionOnMapY/TILE_HEIGHT + 2 + tileYMax; tiley++)
    {
      if(getTileType(tilex, tiley) > 2)
      {
        if(vx < 0)
          obj.positionOnMapX = tilex*TILE_WIDTH + TILE_WIDTH;
        else if(vx > 0)
          obj.positionOnMapX = tilex*TILE_WIDTH - PLAYER_WIDTH;
        vx = 0;
      }
    }
  }

  // Update vertical physics
  if(up)
    vy = -1;
  else if(down)
    vy = 1;
  
  if(strafegun || !standgun)
  {
    //obj.y += vy;
    obj.positionOnMapY += vy;
  }
  
  // collide with zombies
  for(id=0; id<ZOMBIE_MAX; id++)
  {
    if(zombieCollision(zombies[id], obj.positionOnMapX, obj.positionOnMapY, PLAYER_WIDTH, PLAYER_HEIGHT))
    {
      if(vy > 0)
        obj.positionOnMapY = zombies[id].y - PLAYER_HEIGHT;
      else if(vy < 0)
        obj.positionOnMapY = zombies[id].y + ZOMBIE_HEIGHT;
      vy = 0;
      hurtPlayer(obj);
      break;
    }
  }
  
  // collide with walls
  tileXMax = obj.positionOnMapX%TILE_WIDTH != 0;
  tileYMax = obj.positionOnMapY%TILE_HEIGHT != 0;
  for(tilex = obj.positionOnMapX/TILE_WIDTH; tilex < obj.positionOnMapX/TILE_WIDTH + 2 + tileXMax; tilex++)
  {
    for(tiley = obj.positionOnMapY/TILE_HEIGHT; tiley < obj.positionOnMapY/TILE_HEIGHT + 2 + tileYMax; tiley++)
    {
      if(getTileType(tilex, tiley) > 2)
      {
        if(vy < 0)
          obj.positionOnMapY = tiley*TILE_HEIGHT + TILE_HEIGHT;
        else if(vy > 0)
          obj.positionOnMapY = tiley*TILE_HEIGHT - PLAYER_HEIGHT;
        vy = 0;
      }
    }
  }
  
  // collide with survivors
  for(id=0; id<SURVIVOR_MAX; id++)
  {
    if(survivorCollision(survivors[id], obj.positionOnMapX, obj.positionOnMapY, PLAYER_WIDTH, PLAYER_HEIGHT))
    {
      if(collectSurvivor(survivors[id]))
      {
        showDoor();
      }
      break;
    }
  }
  
  // collide with door
  if(checkDoorCollision())
  {
    gameState = STATE_GAME_PREPARE_LEVEL;
  }
  
  
  // Update camera direction
  if(!strafegun)
  {
    if(vx < 0)
      inputDirection = PLAYER_FACING_WEST;
    else if(vx > 0)
      inputDirection = PLAYER_FACING_EAST;

    if(vy < 0) {
      if(inputDirection == PLAYER_FACING_WEST)
        inputDirection = PLAYER_FACING_NORTHWEST;
      else if(inputDirection == PLAYER_FACING_EAST)
        inputDirection = PLAYER_FACING_NORTHEAST;
      else
        inputDirection = PLAYER_FACING_NORTH;
    }
    else if(vy > 0)
    {
      if(inputDirection == PLAYER_FACING_WEST)
        inputDirection = PLAYER_FACING_SOUTHWEST;
      else if(inputDirection == PLAYER_FACING_EAST)
        inputDirection = PLAYER_FACING_SOUTHEAST;
      else
        inputDirection = PLAYER_FACING_SOUTH;
    }
  }
  
  
  
  obj.direction = inputDirection;
  
  if((standgun && !rungun) || (obj.direction%2) == 0)
  {
    obj.camDirection = inputDirection;
  } 
  
  
  /*
  if(obj.diagonalTime > 0)
  {
    if(((obj.direction%2) == 0) && ((obj.camDirection%2) == 1)) // a diagonal direction is odd
    {
      obj.direction = obj.camDirection;
    }
    else
    {
      obj.camDirection = obj.direction; 
    }
  }
  else
  {
      obj.camDirection = obj.direction;
  }
  */
  
  // Update gun
  if(standgun || rungun)
  {
    if(obj.shotDelay == 0)
    {
      addBullet(obj.positionOnMapX + PLAYER_WIDTH/2, obj.positionOnMapY + PLAYER_HEIGHT/2, obj.direction, 0, 0);
      obj.shotDelay = 10;
    }
  }
  
  // Update animation
  if (arduboy.everyXFrames(6) && obj.walking) obj.frame++;
  if (obj.frame > 3 ) obj.frame = 0;
  
  // update score
  if(rollingScore > 0)
  {
    rollingScore -= 5;
    scorePlayer += 5;
  }
  
  // update flashing
  if(obj.flashTime > 0)
    obj.flashTime--;
  
  obj.vx = vx;
  obj.vy = vy;
  
  // update camera
  short mapGoalX = coolGirl.positionOnMapX - WIDTH/2 + PLAYER_WIDTH/2;
  short mapGoalY = coolGirl.positionOnMapY - HEIGHT/2 + PLAYER_HEIGHT/2 - 4; // hud offset
  
  // offset the goal by the direction
  mapGoalX += BulletXVelocities[coolGirl.camDirection]*4;
  mapGoalY += BulletXVelocities[(coolGirl.camDirection+6)%8]*4;
  
  // move the camera toward the desired location
  mapPositionX = burp(mapPositionX, mapGoalX, 3);
  mapPositionY = burp(mapPositionY, mapGoalY, 3);
  
  // Clamp on screen boundaries
  mapPositionX = (mapPositionX < 0) ? 0 : mapPositionX;
  mapPositionX = (mapPositionX > LEVEL_WIDTH - WIDTH) ? LEVEL_WIDTH-WIDTH : mapPositionX;
  mapPositionY = (mapPositionY < 0) ? 0 : mapPositionY;
  mapPositionY = (mapPositionY > LEVEL_HEIGHT - HEIGHT) ? LEVEL_HEIGHT-HEIGHT : mapPositionY;
}

// hurtPlayer
// make player take damage
void hurtPlayer(Player& obj)
{
  if(obj.flashTime == 0)
  {
    obj.health--;
    obj.flashTime = PLAYER_FLASH_TIME;
    arduboy.tunes.tone(880, 20);
  }
  
  if(obj.health == 0)
  {
    gameState = STATE_GAME_OVER;
  }
}

// drawPlayer
// draws the player to the screen
void drawPlayer(Player& obj)
{
  if((obj.flashTime % 8) < 4)
    sprites.drawPlusMask(obj.positionOnMapX - mapPositionX, obj.positionOnMapY - mapPositionY, player_plus_mask, obj.frame + 4*obj.direction);
}

void drawLife(Player& obj)
{
  for (byte amountLife = 0; amountLife < obj.health;amountLife++)
  {
    sprites.drawPlusMask(amountLife*10, 0, HUD_plus_mask, 0);
  }
}

