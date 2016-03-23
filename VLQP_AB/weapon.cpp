#include "weapon.h"
#include "player.h"

// globals ///////////////////////////////////////////////////////////////////

WeaponPickup weapons[WEAPON_MAX];

// method implementations ////////////////////////////////////////////////////

// setWeapon
// sets the members of a weapon pickup instance
void setWeapon(WeaponPickup& obj, int x, int y, byte type)
{
  obj.x = x;
  obj.y = y;
  obj.type = type;
  obj.active = true;
}

// addWeapon
// attempts to add a weapon if there is an empty spot in the list
void addWeapon(int x, int y, byte type)
{
  byte id;
  
  for(id=0; id<WEAPON_MAX; id++)
  {
    if(!weapons[id].active)
    {
      setWeapon(
        weapons[id],
        x,
        y,
        type
      );
      break;
    }
  }
}

// drawWeapons
// draws the entire list of weapons
void drawWeapons()
{
  byte id;
  byte x, y;
  
  for(id=0; id<WEAPON_MAX; id++)
  {
    if(!weapons[id].active) continue;
    x = weapons[id].x;
    y = weapons[id].y;
    arduboy.drawRect(weapons[id].x - mapPositionX, weapons[id].y - mapPositionY, WEAPON_WIDTH, WEAPON_HEIGHT, 1);
  }
}

// clearWeapons
// clears the entire list of weapons
void clearWeapons()
{
  byte id;
  
  for(id=0; id<WEAPON_MAX; id++)
  {
    weapons[id].active = false;
  }
}
