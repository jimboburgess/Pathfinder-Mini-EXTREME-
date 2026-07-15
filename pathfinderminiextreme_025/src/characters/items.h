//
// Created by james on 7/12/2026.
//

#ifndef PATHFINDERMINIEXTREME_025_ITEMS_H
#define PATHFINDERMINIEXTREME_025_ITEMS_H

#include <Arduino.h>

//==================================================
// Damage Types
//==================================================

enum DamageType
{
    DAMAGE_BLUDGEONING,
    DAMAGE_PIERCING,
    DAMAGE_SLASHING
};

//==================================================
// Weapon
//==================================================

struct Weapon
{
    const char* name;

    uint8_t damageDice;
    uint8_t damageSides;

    DamageType damageType;
};

//==================================================
// Armor
//==================================================

struct Armor
{
    const char* name;

    uint8_t armorBonus;
};

//==================================================
// Shield
//==================================================

struct Shield
{
    const char* name;

    uint8_t shieldBonus;
};

//==================================================
// Databases
//==================================================

extern const Weapon weaponDatabase[];

extern const Armor armorDatabase[];

extern const Shield shieldDatabase[];

#endif // PATHFINDERMINIEXTREME_025_ITEMS_H