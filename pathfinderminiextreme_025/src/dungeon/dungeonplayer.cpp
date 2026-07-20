//
// Created by james on 7/12/2026.
//

#include "dungeonplayer.h"
#include <Adafruit_ST7789.h>
#include "config.h"
#include <Arduino.h>
#include "../audio/audio.h"

extern Adafruit_ST7789 tft;

Direction selectedDirection = DIR_NORTH;

void rotateDirectionCW() {
  selectedDirection =
    (Direction)((selectedDirection + 1) % 4);
}

void rotateDirectionCCW() {
  selectedDirection =
    (Direction)((selectedDirection + 3) % 4);
}

void drawMoveCursor(const Dungeon &dungeon) {
    Entity* player = getPlayerEntity((Dungeon&)dungeon);

  if (player == nullptr)
    return;

  int x = player->x;
  int y = player->y;

  switch (selectedDirection) {
    case DIR_NORTH:
      y--;
      break;

    case DIR_EAST:
      x++;
      break;

    case DIR_SOUTH:
      y++;
      break;

    case DIR_WEST:
      x--;
      break;
  }

  tft.drawRect(
    x * TILE_SIZE,
    y * TILE_SIZE,
    TILE_SIZE,
    TILE_SIZE,
    ST77XX_WHITE);
}

bool tryMovePlayer(Dungeon &dungeon)
{
    Entity* player = getPlayerEntity(dungeon);

    if (player == nullptr)
        return false;

    int targetX = player->x;
    int targetY = player->y;

    switch (selectedDirection)
    {
        case DIR_NORTH:
            targetY--;
            break;

        case DIR_EAST:
            targetX++;
            break;

        case DIR_SOUTH:
            targetY++;
            break;

        case DIR_WEST:
            targetX--;
            break;
    }

    DungeonRoom &room = dungeon.rooms[dungeon.currentRoom];

    if (targetX < 0 || targetX >= ROOM_SIZE ||
        targetY < 0 || targetY >= ROOM_SIZE)
    {
        playSound(SoundEffect::BUMP);
        return false;
    }

    TileType tile = room.map.tiles[targetY][targetX];

    switch (tile)
    {
        case TILE_FLOOR:

            player->x = targetX;
            player->y = targetY;
            return true;

        case TILE_WALL:

            playSound(SoundEffect::BUMP);
            return false;

        case TILE_DOOR:
        {
            uint8_t nextRoom = 255;

            if (targetY == 0)
                nextRoom = room.north;
            else if (targetY == ROOM_SIZE - 1)
                nextRoom = room.south;
            else if (targetX == 0)
                nextRoom = room.west;
            else if (targetX == ROOM_SIZE - 1)
                nextRoom = room.east;

            if (nextRoom != 255)
            {
                dungeon.currentRoom = nextRoom;

                if (targetY == 0)
                    loadRoom(dungeon, ENTRY_SOUTH);
                else if (targetY == ROOM_SIZE - 1)
                    loadRoom(dungeon, ENTRY_NORTH);
                else if (targetX == 0)
                    loadRoom(dungeon, ENTRY_EAST);
                else if (targetX == ROOM_SIZE - 1)
                    loadRoom(dungeon, ENTRY_WEST);

                return true;
            }

            break;
        }

        default:
            return false;
    }

    return false;
}