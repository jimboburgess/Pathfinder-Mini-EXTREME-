#ifndef PATHFINDERMINIEXTREME_025_DISPLAY_H
#define PATHFINDERMINIEXTREME_025_DISPLAY_H

#include <stdint.h>

void drawStartScreen();
void drawStartAnimation();
void drawTownScreen();
void drawDungeonScreen();

void drawCriticalHit();

void drawSpriteTransparent(int x, int y, const uint16_t* sprite);
void drawSpriteTransparent64(int x, int y, const uint16_t* sprite);

#endif