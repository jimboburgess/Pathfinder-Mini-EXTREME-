//
// Created by james on 7/12/2026.
//

#ifndef PATHFINDERMINIEXTREME_025_DUNGEON_H
#define PATHFINDERMINIEXTREME_025_DUNGEON_H

#include <Arduino.h>
#include "../characters/characters.h"

constexpr uint8_t ROOM_SIZE = 15;
constexpr uint8_t TILE_SIZE = 16;
constexpr uint16_t SCREEN_SIZE = ROOM_SIZE * TILE_SIZE;
constexpr uint8_t MAX_ENTITIES = 16;
constexpr uint8_t NO_ROOM = 255;

//==================================================
// Rooms
//==================================================
enum RoomType : uint8_t {
    ROOM_ENTRANCE,
    ROOM_COMBAT,
    ROOM_PUZZLE,
    ROOM_TRAP,
    ROOM_AMBUSH,
    ROOM_LOCKED_DOOR,
    ROOM_BOSS,
    ROOM_TREASURE
  };

enum RoomShape : uint8_t {
    SHAPE_SQUARE,
    SHAPE_CROSS,
    SHAPE_CIRCLE
  };

enum RoomEntry {
    ENTRY_START,
    ENTRY_NORTH,
    ENTRY_EAST,
    ENTRY_SOUTH,
    ENTRY_WEST
  };

enum TileType : uint8_t {
    TILE_VOID,  // outside map
    TILE_WALL,
    TILE_FLOOR,
    TILE_DOOR,
    TILE_CHEST_SPAWN,
    TILE_LOOT_SPAWN,
    TILE_NPC_SPAWN,
    TILE_TRAP,
    TILE_EXIT,
    TILE_PLAYER_START,
    TILE_ENEMY_START
  };
//==================================================
// Entities
//==================================================
enum EntityType : uint8_t {
    ENTITY_NONE,
    ENTITY_PLAYER,
    ENTITY_ENEMY,
    ENTITY_CHEST,
    ENTITY_LOOT,
    ENTITY_NPC
  };

struct Entity {
    EntityType type;

    uint8_t x;
    uint8_t y;

    bool active = false;
};
//==================================================
// Dungeon
//==================================================
struct RoomMap {
    TileType tiles[ROOM_SIZE][ROOM_SIZE];
};

struct DungeonRoom {
    RoomType type;
    RoomShape shape;


    bool discovered;
    bool completed;

    uint8_t north;
    uint8_t south;
    uint8_t east;
    uint8_t west;

    RoomMap map;
};

constexpr uint8_t MAX_ROOMS = 5;
constexpr uint8_t MAX_DUNGEON_CHARACTERS = 16;

struct Dungeon {
    DungeonRoom rooms[MAX_ROOMS];
    Entity entities[MAX_ENTITIES];
    Character* characters[MAX_DUNGEON_CHARACTERS];
    uint8_t characterCount = 0;
    uint8_t currentRoom = 0;
    uint8_t entityCount = 0;
    };

extern Dungeon dungeon;

const char* roomTypeName(RoomType type);
void generateDungeon(Dungeon& dungeon);
void generateRoom(DungeonRoom& room);
void loadRoom(Dungeon& dungeon, RoomEntry entry);
void addCharacterToDungeon(Character* character);

Entity* getPlayerEntity(Dungeon& dungeon);
Character* getPlayerCharacter(Dungeon& dungeon);

#endif //PATHFINDERMINIEXTREME_025_DUNGEON_H
