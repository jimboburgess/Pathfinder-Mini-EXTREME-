#include "combat.h"
#include "dungeon.h"

Combat combat;

void checkForCombat()
{
    // TODO
}

void startCombat()
{
    combat.active = true;
    combat.phase = COMBAT_INITIATIVE;
}

void updateCombat()
{
    switch (combat.phase)
    {
        case COMBAT_NONE:
            break;

        case COMBAT_INITIATIVE:
            break;

        case COMBAT_TURN:
            break;

        case COMBAT_END:
            endCombat();
            break;
    }
}

void endCombat()
{
    combat.active = false;
    combat.phase = COMBAT_NONE;
}

bool isCombatActive()
{
    return combat.active;
}