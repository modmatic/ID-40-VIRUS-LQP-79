#ifndef WEAPON_H
#define WEAPON_H

#include <Arduino.h>

// constants /////////////////////////////////////////////////////////////////

#define WEAPON_MAX 3
#define WEAPON_WIDTH 16
#define WEAPON_HEIGHT 16

// structures ////////////////////////////////////////////////////////////////

struct WeaponPickup {
  int x;
  int y;
  byte type;
  byte active;
};

// globals ///////////////////////////////////////////////////////////////////

extern WeaponPickup weapons[WEAPON_MAX];

// method prototypes /////////////////////////////////////////////////////////

void setWeapon(WeaponPickup& obj, int x, int y, byte type);
void addWeapon(int x, int y, byte type);
void drawWeapons();
void clearWeapons();

#endif
