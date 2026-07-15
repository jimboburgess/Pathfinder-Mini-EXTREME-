//
// Created by james on 7/13/2026.
//
//
// Created by james on 7/13/2026.
//

#ifndef PATHFINDERMINIEXTREME_025_PROGRESSION_H
#define PATHFINDERMINIEXTREME_025_PROGRESSION_H

#include "progression.h"
#include <Arduino.h>
#include "../characters/characters.h"

//======================================
// Progression
//======================================

int getBaseAttackBonus(CharacterClass characterClass, uint8_t level);

int getBaseHitPoints(CharacterClass characterClass, uint8_t level);

int getFortitudeSave(CharacterClass characterClass, uint8_t level);

int getReflexSave(CharacterClass characterClass, uint8_t level);

int getWillSave(CharacterClass characterClass, uint8_t level);

int getAbilityModifier(int score);

#endif

