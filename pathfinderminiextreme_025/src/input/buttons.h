//
// Created by james on 7/12/2026.
//

#ifndef PATHFINDERMINIEXTREME_025_BUTTONS_H
#define PATHFINDERMINIEXTREME_025_BUTTONS_H

#include <Arduino.h>
#include "config.h"
#include "audio/audio.h"
#include "graphics/charcreationscreen.h"
#include "dungeon/dungeon.h"
#include "dungeon/dungeonplayer.h"
#include "data/game.h"


// Main input handler
void handleButtons();

// Individual state handlers
void handleStartButtons();
void handleCharacterCreationButtons();
void handleTownButtons();
void handleDungeonButtons();

#endif // PATHFINDERMINIEXTREME_025_BUTTONS_H