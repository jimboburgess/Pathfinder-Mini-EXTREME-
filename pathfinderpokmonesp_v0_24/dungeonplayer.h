#pragma once

#include "dungeon.h"
#include "audio.h"

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