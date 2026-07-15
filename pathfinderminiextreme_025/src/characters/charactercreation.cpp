//
// Created by james on 7/13/2026.
//

#include "graphics/charcreationscreen.h"
#include "data/dice.h"

struct StartingEquipment
{
    ItemID meleeWeapon;
    ItemID rangedWeapon;

    ItemID armor;
    ItemID shield;
};

static const StartingEquipment startingEquipment[] =
{
    // Fighter
    {
        ITEM_LONGSWORD,
        ITEM_SHORTBOW,
        ITEM_CHAINMAIL,
        ITEM_HEAVY_SHIELD
    },

    // Rogue
    {
        ITEM_DAGGER,
        ITEM_CROSSBOW,
        ITEM_LEATHER,
        ITEM_NONE
    },

    // Wizard
    {
        ITEM_QUARTERSTAFF,
        ITEM_SHORTBOW,
        ITEM_NONE,
        ITEM_NONE
    },

    // Cleric
    {
        ITEM_MACE,
        ITEM_CROSSBOW,
        ITEM_CHAINMAIL,
        ITEM_HEAVY_SHIELD
    }
};

static void sortDescending(int values[], int count)
{
    for (int i = 0; i < count - 1; i++)
    {
        for (int j = i + 1; j < count; j++)
        {
            if (values[j] > values[i])
            {
                int temp = values[i];
                values[i] = values[j];
                values[j] = temp;
            }
        }
    }
}

static void rollabilities(int scores[])
{
    for (int i = 0; i < 6; i++)
    {
        scores[i] = rollAbilityScore();
    }

    sortDescending(scores, 6);;
}

static void assignabilitiesForClass(Character &character,
                                        CharacterClass characterClass,
                                        int scores[])
{
    switch (characterClass)
    {
        case CLASS_FIGHTER:

            character.abilities.strength     = scores[0];
            character.abilities.constitution = scores[1];
            character.abilities.dexterity    = scores[2];
            character.abilities.wisdom       = scores[3];
            character.abilities.charisma     = scores[4];
            character.abilities.intelligence = scores[5];
            break;

        case CLASS_ROGUE:

            character.abilities.dexterity    = scores[0];
            character.abilities.intelligence = scores[1];
            character.abilities.charisma     = scores[2];
            character.abilities.constitution = scores[3];
            character.abilities.wisdom       = scores[4];
            character.abilities.strength     = scores[5];
            break;

        case CLASS_WIZARD:

            character.abilities.intelligence = scores[0];
            character.abilities.dexterity    = scores[1];
            character.abilities.constitution = scores[2];
            character.abilities.wisdom       = scores[3];
            character.abilities.charisma     = scores[4];
            character.abilities.strength     = scores[5];
            break;

        case CLASS_CLERIC:

            character.abilities.wisdom       = scores[0];
            character.abilities.constitution = scores[1];
            character.abilities.strength     = scores[2];
            character.abilities.charisma     = scores[3];
            character.abilities.dexterity    = scores[4];
            character.abilities.intelligence = scores[5];
            break;
    }
}

static void giveStartingEquipment(Character &character,
                                  CharacterClass characterClass)
{
    const StartingEquipment &gear = startingEquipment[characterClass];

    character.equippedWeapon       = gear.meleeWeapon;
    character.equippedRangedWeapon = gear.rangedWeapon;
    character.equippedArmor        = gear.armor;
    character.equippedShield       = gear.shield;

    character.inventoryCount = 0;

    // TODO: Add starting potions once consumables are implemented.
}

void createCharacter(Character &character, CharacterClass characterClass)
{
    int scores[6];

    rollabilities(scores);

    character.characterClass = characterClass;

    assignabilitiesForClass(character, characterClass, scores);

    giveStartingEquipment(character, characterClass);

    character.level = 1;
    character.xp = 0;

    character.maxHP = getMaxHP(character);
    character.currentHP = character.maxHP;

    character.team = TEAM_PLAYER;
    character.state = STATE_ALIVE;
}

