//
// Created by james on 7/12/2026.
//

#ifndef PATHFINDERMINIEXTREME_025_CHARACTERS_H
#define PATHFINDERMINIEXTREME_025_CHARACTERS_H

#include <Arduino.h>

//==================================================
// Character Constants
//==================================================

constexpr uint8_t MAX_INVENTORY = 24;

//==================================================
// Ability Scores
//==================================================

struct AbilityScores
{
    uint8_t strength;
    uint8_t dexterity;
    uint8_t constitution;

    uint8_t intelligence;
    uint8_t wisdom;
    uint8_t charisma;
};

//==================================================
// Character Classes
//==================================================

enum CharacterClass
{
    CLASS_FIGHTER,
    CLASS_ROGUE,
    CLASS_WIZARD,
    CLASS_CLERIC
};

//==================================================
// Abilities
//==================================================

enum Ability
{
    ABILITY_STRENGTH,
    ABILITY_DEXTERITY,
    ABILITY_CONSTITUTION,
    ABILITY_INTELLIGENCE,
    ABILITY_WISDOM,
    ABILITY_CHARISMA
};

//==================================================
// Skills
//==================================================

enum Skill
{
    SKILL_ACROBATICS,
    SKILL_DIPLOMACY,
    SKILL_DISABLE_DEVICE,
    SKILL_INTIMIDATE,
    SKILL_PERCEPTION,
    SKILL_STEALTH,

    SKILL_COUNT
};

enum SkillAptitude
{
    SKILL_NONE,
    SKILL_POOR,
    SKILL_AVERAGE,
    SKILL_GOOD,
    SKILL_EXCELLENT
};

//==================================================
// Items
//==================================================

enum ItemType
{
    ITEM_WEAPON,
    ITEM_ARMOR,
    ITEM_SHIELD,
    ITEM_POTION,
    ITEM_SCROLL,
    ITEM_FOOD,
    ITEM_TOOL,
    ITEM_TREASURE,
    ITEM_QUEST,
    ITEM_MISC
};

enum ItemID
{
    ITEM_NONE = 0,

    // Weapons
    ITEM_CLUB,
    ITEM_QUARTERSTAFF,
    ITEM_DAGGER,
    ITEM_SHORTSWORD,
    ITEM_LONGSWORD,
    ITEM_MACE,
    ITEM_BATTLEAXE,
    ITEM_SHORTBOW,
    ITEM_CROSSBOW,

    // Armor
    ITEM_LEATHER,
    ITEM_CHAINMAIL,
    ITEM_FULL_PLATE,

    // Shields
    ITEM_HEAVY_SHIELD,

    // Consumables
    ITEM_HEALING_POTION,

    // Tools
    ITEM_ROPE,
    ITEM_TORCH
};

//==================================================
// Creature Types
//==================================================

enum CreatureType
{
    CREATURE_PLAYER,
    CREATURE_GOBLIN,
    CREATURE_SKELETON,
    CREATURE_WOLF,
    CREATURE_ORC,
    CREATURE_ZOMBIE,
    CREATURE_BEHOLDER
};

//==================================================
// Teams
//==================================================

enum Team
{
    TEAM_PLAYER,
    TEAM_MONSTER,
    TEAM_NEUTRAL
};

//==================================================
// Character State
//==================================================

enum CharacterState
{
    STATE_ALIVE,
    STATE_UNCONSCIOUS,
    STATE_DEAD,
    STATE_LOOTED
};

//==================================================
// Character
//==================================================

struct Character
{
    // Identity
    String name;

    CharacterClass characterClass;
    CreatureType creatureType;

    Team team;
    CharacterState state;

    // Progression
    uint8_t level;
    uint16_t xp;

    // Ability Scores
    AbilityScores abilities;

    // Health
    int currentHP;
    int maxHP;

      // Equipment
    ItemID equippedWeapon;
    ItemID equippedRangedWeapon;
    ItemID equippedArmor;
    ItemID equippedShield;

    // Inventory
    ItemID inventory[MAX_INVENTORY];
    uint8_t inventoryCount;
};

//==================================================
// Character Rules
//==================================================

int getAbilityModifier(const Character& character, Ability ability);

int getMaxHP(const Character& character);

int getArmorClass(const Character& character);

int getMeleeAttackBonus(const Character& character);

int getRangedAttackBonus(const Character& character);

//==================================================
// Skills
//==================================================

SkillAptitude getSkillAptitude(CharacterClass characterClass,
                               Skill skill);

int getSkillRank(SkillAptitude aptitude,
                 uint8_t level);

int getSkillBonus(const Character& character,
                  Skill skill);

//==================================================
// Saving Throws
//==================================================

int getFortitudeSave(const Character& character);

int getReflexSave(const Character& character);

int getWillSave(const Character& character);

//==================================================
// Status
//==================================================

bool isAlive(const Character& character);

bool isDead(const Character& character);

#endif // PATHFINDERMINIEXTREME_025_CHARACTERS_H