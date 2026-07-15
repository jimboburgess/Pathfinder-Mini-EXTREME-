//
// Created by james on 7/13/2026.
//

#include "progression.h"

static const uint8_t noneProgression[20] =
{
    0,0,0,0,0,
    0,0,0,0,0,
    0,0,0,0,0,
    0,0,0,0,0
  };

static const uint8_t poorProgression[20] =
{
    0,0,0,0,
    1,1,1,1,
    2,2,2,2,
    3,3,3,3,
    4,4,4,5
  };

static const uint8_t averageProgression[20] =
{
    1,1,2,2,
    3,3,4,4,
    5,5,6,6,
    7,7,8,8,
    9,9,10,10
  };

static const uint8_t goodProgression[20] =
{
    1,2,2,3,
    4,4,5,6,
    7,7,8,9,
    10,10,11,12,
    13,13,14,15
  };

static const uint8_t excellentProgression[20] =
{
    1,2,3,4,
    5,6,7,8,
    9,10,11,12,
    13,14,15,16,
    17,18,19,20
  };

//==================================================
// Base Attack Bonus Progression
//==================================================

static const uint8_t highBAB[20] =
{
    1,2,3,4,5,
    6,7,8,9,10,
    11,12,13,14,15,
    16,17,18,19,20
};

static const uint8_t mediumBAB[20] =
{
    0,1,2,3,3,
    4,5,6,6,7,
    8,9,9,10,11,
    12,12,13,14,15
};

static const uint8_t lowBAB[20] =
{
    0,1,1,2,2,
    3,3,4,4,5,
    5,6,6,7,7,
    8,8,9,9,10
};

//==================================================
// Hit Point Progression
//==================================================

static const uint8_t fighterHP[20] =
{
    10,15,21,26,32,
    37,43,48,54,59,
    65,70,76,81,87,
    92,98,103,109,114
};

static const uint8_t rogueHP[20] =
{
    6,9,13,16,20,
    23,27,30,34,37,
    41,44,48,51,55,
    58,62,65,69,72
};

static const uint8_t wizardHP[20] =
{
    4,6,9,11,14,
    16,19,21,24,26,
    29,31,34,36,39,
    41,44,46,49,51
};

static const uint8_t clericHP[20] =
{
    8,12,17,21,26,
    30,35,39,44,48,
    53,57,62,66,71,
    75,80,84,89,93
};

//==================================================
// Saving Throws
//==================================================

static const uint8_t goodSave[20] =
{
    2,3,3,4,4,
    5,5,6,6,6,
    7,8,8,9,9,
    10,10,11,11,12
};

static const uint8_t poorSave[20] =
{
    0,0,1,1,1,
    2,2,2,3,3,
    3,4,4,4,5,
    5,5,6,6,6
};

//==================================================
// Base Attack Bonus
//==================================================

int getBaseAttackBonus(CharacterClass characterClass, uint8_t level)
{
    if (level < 1) level = 1;
    if (level > 20) level = 20;

    switch (characterClass)
    {
        case CLASS_FIGHTER:
            return highBAB[level - 1];

        case CLASS_ROGUE:
        case CLASS_CLERIC:
            return mediumBAB[level - 1];

        case CLASS_WIZARD:
            return lowBAB[level - 1];
    }

    return 0;
}

//==================================================
// Base Hit Points
//==================================================

int getBaseHitPoints(CharacterClass characterClass, uint8_t level)
{
    if (level < 1) level = 1;
    if (level > 20) level = 20;

    switch (characterClass)
    {
        case CLASS_FIGHTER:
            return fighterHP[level - 1];

        case CLASS_ROGUE:
            return rogueHP[level - 1];

        case CLASS_WIZARD:
            return wizardHP[level - 1];

        case CLASS_CLERIC:
            return clericHP[level - 1];
    }

    return 0;
}

//==================================================
// Saving Throws
//==================================================

int getFortitudeSave(CharacterClass characterClass, uint8_t level)
{
    if (level < 1) level = 1;
    if (level > 20) level = 20;

    switch (characterClass)
    {
        case CLASS_FIGHTER:
        case CLASS_CLERIC:
            return goodSave[level - 1];

        default:
            return poorSave[level - 1];
    }
}

int getReflexSave(CharacterClass characterClass, uint8_t level)
{
    if (level < 1) level = 1;
    if (level > 20) level = 20;

    switch (characterClass)
    {
        case CLASS_ROGUE:
            return goodSave[level - 1];

        default:
            return poorSave[level - 1];
    }
}

int getWillSave(CharacterClass characterClass, uint8_t level)
{
    if (level < 1) level = 1;
    if (level > 20) level = 20;

    switch (characterClass)
    {
        case CLASS_WIZARD:
        case CLASS_CLERIC:
            return goodSave[level - 1];

        default:
            return poorSave[level - 1];
    }
}
