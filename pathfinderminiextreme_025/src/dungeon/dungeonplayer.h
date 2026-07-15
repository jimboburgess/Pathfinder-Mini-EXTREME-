//
// Created by james on 7/12/2026.
//

#ifndef PATHFINDERMINIEXTREME_025_DUNGEONPLAYER_H
#define PATHFINDERMINIEXTREME_025_DUNGEONPLAYER_H

#include "dungeon.h"
#include "audio/audio.h"

enum Direction : uint8_t
{
    DIR_NORTH,
    DIR_EAST,
    DIR_SOUTH,
    DIR_WEST
};

extern Direction selectedDirection;

void rotateDirectionCW();
void rotateDirectionCCW();

void drawMoveCursor(const Dungeon &dungeon);

bool tryMovePlayer(Dungeon &dungeon);
#endif //PATHFINDERMINIEXTREME_025_DUNGEONPLAYER_H
