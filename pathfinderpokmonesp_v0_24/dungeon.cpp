#include "dungeon.h"
#include "roomgen.h"

Dungeon dungeon;

const char *roomTypeName(RoomType type) {
  switch (type) {
    case ROOM_ENTRANCE: return "Entrance";
    case ROOM_COMBAT: return "Combat";
    case ROOM_PUZZLE: return "Puzzle";
    case ROOM_TRAP: return "Trap";
    case ROOM_AMBUSH: return "Ambush";
    case ROOM_LOCKED_DOOR: return "Locked Door";
    case ROOM_BOSS: return "Boss";
    case ROOM_TREASURE: return "Treasure";
  }

  return "Unknown";
}


void generateDungeon(Dungeon &dungeon) {
  dungeon.currentRoom = 0;

  // Clear room connections
  for (int i = 0; i < MAX_ROOMS; i++) {
    dungeon.rooms[i].north = 255;
    dungeon.rooms[i].south = 255;
    dungeon.rooms[i].east = 255;
    dungeon.rooms[i].west = 255;

    dungeon.rooms[i].discovered = false;
    dungeon.rooms[i].completed = false;
  }

  // Connect the rooms
  for (int i = 0; i < MAX_ROOMS - 1; i++) {
    dungeon.rooms[i].east = i + 1;
    dungeon.rooms[i + 1].west = i;
  }

  dungeon.rooms[0].type = ROOM_ENTRANCE;

  dungeon.rooms[1].type = random(2) ? ROOM_COMBAT : ROOM_PUZZLE;

  switch (random(2)) {
    case 0:
      dungeon.rooms[2].type = ROOM_TRAP;
      break;

    case 1:
      dungeon.rooms[2].type = ROOM_AMBUSH;
      break;
  }

  dungeon.rooms[3].type = ROOM_BOSS;
  dungeon.rooms[4].type = ROOM_TREASURE;

  dungeon.rooms[0].discovered = true;

  // Generate every room
  for (int i = 0; i < MAX_ROOMS; i++) {
    dungeon.rooms[i].shape = (RoomShape)random(3);

    generateRoom(dungeon.rooms[i]);
  }

  // Load the starting room and create its entities.
  loadRoom(dungeon, ENTRY_START);
}

void loadRoom(Dungeon &dungeon, RoomEntry entry) {
  DungeonRoom &room = dungeon.rooms[dungeon.currentRoom];

  // Remove any entities from the previous room.
  dungeon.entityCount = 0;

  // Scan the room and create entities.
  for (int y = 0; y < ROOM_SIZE; y++) {
    for (int x = 0; x < ROOM_SIZE; x++) {
      switch (room.map.tiles[y][x]) {
        case TILE_ENEMY_START:
          {
            Entity &entity = dungeon.entities[dungeon.entityCount++];

            entity.type = ENTITY_ENEMY;
            entity.x = x;
            entity.y = y;
            entity.active = true;

            room.map.tiles[y][x] = TILE_FLOOR;
            break;
          }

        case TILE_CHEST_SPAWN:
          {
            Entity &entity = dungeon.entities[dungeon.entityCount++];

            entity.type = ENTITY_CHEST;
            entity.x = x;
            entity.y = y;
            entity.active = true;

            room.map.tiles[y][x] = TILE_FLOOR;
            break;
          }

        case TILE_LOOT_SPAWN:
          {
            Entity &entity = dungeon.entities[dungeon.entityCount++];

            entity.type = ENTITY_LOOT;
            entity.x = x;
            entity.y = y;
            entity.active = true;

            room.map.tiles[y][x] = TILE_FLOOR;
            break;
          }

        case TILE_NPC_SPAWN:
          {
            Entity &entity = dungeon.entities[dungeon.entityCount++];

            entity.type = ENTITY_NPC;
            entity.x = x;
            entity.y = y;
            entity.active = true;

            room.map.tiles[y][x] = TILE_FLOOR;
            break;
          }

        default:
          break;
      }
    }
  }

  // Create the player.
  Entity &player = dungeon.entities[dungeon.entityCount++];

  player.type = ENTITY_PLAYER;
  player.active = true;

  switch (entry) {
    case ENTRY_START:
      player.x = ROOM_SIZE / 2;
      player.y = ROOM_SIZE / 2;
      break;

    case ENTRY_NORTH:
      player.x = ROOM_SIZE / 2;
      player.y = 1;
      break;

    case ENTRY_EAST:
      player.x = ROOM_SIZE - 2;
      player.y = ROOM_SIZE / 2;
      break;

    case ENTRY_SOUTH:
      player.x = ROOM_SIZE / 2;
      player.y = ROOM_SIZE - 2;
      break;

    case ENTRY_WEST:
      player.x = 1;
      player.y = ROOM_SIZE / 2;
      break;
  }
}

Entity *getPlayer(Dungeon &dungeon) {
  for (int i = 0; i < dungeon.entityCount; i++) {
    if (dungeon.entities[i].active && dungeon.entities[i].type == ENTITY_PLAYER) {
      return &dungeon.entities[i];
    }
  }

  return nullptr;
}