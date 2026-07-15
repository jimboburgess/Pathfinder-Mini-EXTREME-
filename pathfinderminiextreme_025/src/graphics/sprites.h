//
// Created by james on 7/12/2026.
//

#ifndef PATHFINDERMINIEXTREME_025_SPRITES_H
#define PATHFINDERMINIEXTREME_025_SPRITES_H


class sprites {
};
#pragma once

#include <Arduino.h>

//======================================
// 32x32 Battle Sprites
//======================================

const int SPRITE_W = 32;
const int SPRITE_H = 32;

//======================================
// 64x64 Walking Sprites
//======================================

const int WALK_W = 64;
const int WALK_H = 64;

extern const uint16_t fighterFrame1[SPRITE_W * SPRITE_H];
extern const uint16_t fighterFrame2[SPRITE_W * SPRITE_H];

extern const uint16_t FIGHTERWALK1[WALK_W * WALK_H];
extern const uint16_t FIGHTERWALK2[WALK_W * WALK_H];

extern const uint16_t goblinFrame1[SPRITE_W * SPRITE_H];
extern const uint16_t goblinFrame2[SPRITE_W * SPRITE_H];

extern const uint16_t goblinArcherFrame1[SPRITE_W * SPRITE_H];
extern const uint16_t goblinArcherFrame2[SPRITE_W * SPRITE_H];

extern const uint16_t goblinChiefFrame1[SPRITE_W * SPRITE_H];
extern const uint16_t goblinChiefFrame2[SPRITE_W * SPRITE_H];

#endif //PATHFINDERMINIEXTREME_025_SPRITES_H
