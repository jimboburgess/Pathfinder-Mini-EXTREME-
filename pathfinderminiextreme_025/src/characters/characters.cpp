//
// Created by james on 7/12/2026.
//

#include "characters.h"
#include "data/progression.h"


int getAbilityModifier(int score)
{
  if (score >= 10)
    return (score - 10) / 2;

  return (score - 11) / 2;
}

int getAbilityModifier(const Character& character, Ability ability) {
  int score = 10;

  switch (ability) {
    case ABILITY_STRENGTH:
      score = character.abilities.strength;
      break;

    case ABILITY_DEXTERITY:
      score = character.abilities.dexterity;
      break;

    case ABILITY_CONSTITUTION:
      score = character.abilities.constitution;
      break;

    case ABILITY_INTELLIGENCE:
      score = character.abilities.intelligence;
      break;

    case ABILITY_WISDOM:
      score = character.abilities.wisdom;
      break;

    case ABILITY_CHARISMA:
      score = character.abilities.charisma;
      break;
  }
  return getAbilityModifier(score);
}

int getMaxHP(const Character& character)
{
  return getBaseHitPoints(
      character.characterClass,
      character.level)
      + getAbilityModifier(character, ABILITY_CONSTITUTION);
}

int getArmorClass(const Character& character)
{
  return 10 + getAbilityModifier(character, ABILITY_DEXTERITY);
  // TODO:
  // Add armor and shield bonuses from equipped items.
}

int getMeleeAttackBonus(const Character& character)
{
  return getBaseAttackBonus(
      character.characterClass,
      character.level)
      + getAbilityModifier(character, ABILITY_STRENGTH);
}

int getRangedAttackBonus(const Character& character)
{
  return getBaseAttackBonus(
      character.characterClass,
      character.level)
      + getAbilityModifier(character, ABILITY_DEXTERITY);
}

//==================================================
// Skills
//==================================================

SkillAptitude getSkillAptitude(CharacterClass characterClass,
                               Skill skill)
{
    switch (characterClass)
    {
        case CLASS_FIGHTER:
            switch (skill)
            {
                case SKILL_INTIMIDATE:
                    return SKILL_EXCELLENT;

                case SKILL_PERCEPTION:
                    return SKILL_GOOD;

                default:
                    return SKILL_POOR;
            }

        case CLASS_ROGUE:
            switch (skill)
            {
                case SKILL_STEALTH:
                case SKILL_ACROBATICS:
                case SKILL_DISABLE_DEVICE:
                    return SKILL_EXCELLENT;

                case SKILL_DIPLOMACY:
                case SKILL_PERCEPTION:
                    return SKILL_GOOD;

                default:
                    return SKILL_AVERAGE;
            }

        case CLASS_WIZARD:
            switch (skill)
            {
                case SKILL_PERCEPTION:
                    return SKILL_GOOD;

                default:
                    return SKILL_POOR;
            }

        case CLASS_CLERIC:
            switch (skill)
            {
                case SKILL_DIPLOMACY:
                case SKILL_PERCEPTION:
                    return SKILL_GOOD;

                default:
                    return SKILL_AVERAGE;
            }
    }

    return SKILL_POOR;
}

int getSkillRank(SkillAptitude aptitude,
                 uint8_t level)
{
    switch (aptitude)
    {
        case SKILL_NONE:
            return 0;

        case SKILL_POOR:
            return level / 4;

        case SKILL_AVERAGE:
            return level / 2;

        case SKILL_GOOD:
            return level;

        case SKILL_EXCELLENT:
            return level + 2;
    }

    return 0;
}

int getSkillBonus(const Character& character,
                  Skill skill)
{
    Ability ability = ABILITY_INTELLIGENCE;

    switch (skill)
    {
        case SKILL_ACROBATICS:
        case SKILL_STEALTH:
            ability = ABILITY_DEXTERITY;
            break;

        case SKILL_DIPLOMACY:
        case SKILL_INTIMIDATE:
            ability = ABILITY_CHARISMA;
            break;

        case SKILL_DISABLE_DEVICE:
            ability = ABILITY_INTELLIGENCE;
            break;

        case SKILL_PERCEPTION:
            ability = ABILITY_WISDOM;
            break;
    }

    SkillAptitude aptitude =
        getSkillAptitude(character.characterClass,
                         skill);

    return getSkillRank(aptitude,
                        character.level)
         + getAbilityModifier(character,
                              ability);
}

//==================================================
// Saving Throws
//==================================================

int getFortitudeSave(const Character& character)
{
    int save = getAbilityModifier(character,
                                 ABILITY_CONSTITUTION);

    switch (character.characterClass)
    {
        case CLASS_FIGHTER:
        case CLASS_CLERIC:
            save += 2 + character.level / 2;
            break;

        default:
            save += character.level / 3;
            break;
    }

    return save;
}

int getReflexSave(const Character& character)
{
    int save = getAbilityModifier(character,
                                 ABILITY_DEXTERITY);

    switch (character.characterClass)
    {
        case CLASS_ROGUE:
            save += 2 + character.level / 2;
            break;

        default:
            save += character.level / 3;
            break;
    }

    return save;
}

int getWillSave(const Character& character)
{
    int save = getAbilityModifier(character,
                                 ABILITY_WISDOM);

    switch (character.characterClass)
    {
        case CLASS_WIZARD:
        case CLASS_CLERIC:
            save += 2 + character.level / 2;
            break;

        default:
            save += character.level / 3;
            break;
    }

    return save;
}

//==================================================
// Status
//==================================================

bool isAlive(const Character& character)
{
    return character.state == STATE_ALIVE;
}

bool isDead(const Character& character)
{
    return character.state == STATE_DEAD;
}
