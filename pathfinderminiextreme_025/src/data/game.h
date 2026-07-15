//
// Created by james on 7/14/2026.
//

#ifndef PATHFINDERMINIEXTREME_025_GAME_H
#define PATHFINDERMINIEXTREME_025_GAME_H

#include <Adafruit_ST7789.h>

#include "characters/characters.h"

//======================================================
// Game State
//======================================================

enum GameState
{
    GAME_START,
    GAME_CHARACTER_CREATION,
    GAME_TOWN,
    GAME_DUNGEON
};

enum TownOption
{
    TOWN_GOBLINS,
    TOWN_STAY_HOME,
    TOWN_DUNGEON,
    TOWN_OPTION_COUNT
};

//======================================================
// Global Game Objects
//======================================================

extern Adafruit_ST7789 tft;

extern GameState gameState;
extern TownOption townSelection;

extern Character player;

extern bool needsRedraw;

#endif // PATHFINDERMINIEXTREME_025_GAME_H