#include "display.h"

#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>

#include "config.h"
#include "data/game.h"

#include "audio/audio.h"

#include "graphics/sprites.h"
#include "characters/sheet.h"
#include "dungeon/dungeon.h"
#include "dungeon/dungeonplayer.h"
#include "dungeon/roomdraw.h"

Adafruit_ST7789 tft(
    TFT_CS,
    TFT_DC,
    TFT_RST);

void drawStartScreen()
{
    tft.fillScreen(ST77XX_BLACK);

    playSound(SoundEffect::TITLE_THEME);

    drawSpriteTransparent64(8,   95, ROGUE64X64);
    drawSpriteTransparent64(64,  95, FIGHTERWALK1);
    drawSpriteTransparent64(120, 95, CLERIC64X64);
    drawSpriteTransparent64(176, 95, WIZARD64X64);

    tft.setTextColor(ST77XX_WHITE);

    tft.setTextSize(3);
    tft.setCursor(30, 30);
    tft.println("Pathfinder");

    tft.setCursor(5, 60);
    tft.println("Mini EXTREME!");

    tft.setTextSize(2);
    tft.setCursor(30, 205);
    tft.println("Press A Button");
}

void drawStartAnimation()
{
    static bool lastFrame = false;

    bool frame = (millis() / 800) % 2;

    if (frame == lastFrame)
        return;

    lastFrame = frame;

    const uint16_t* fighterSprite =
        frame ? FIGHTERWALK1 : FIGHTERWALK2;

    tft.fillRect(64, 95, 64, 64, ST77XX_BLACK);

    drawSpriteTransparent64(
        64,
        95,
        fighterSprite);
}

void drawTownScreen()
{
    if (isCharacterSheetVisible())
    {
        drawCharacterSheet();
        return;
    }
    tft.fillScreen(ST77XX_BLACK);

    tft.setTextColor(ST77XX_WHITE);

    tft.setTextSize(3);
    tft.setCursor(72, 20);
    tft.print("Town");

    tft.setTextSize(2);

    tft.setCursor(20, 70);
    tft.print(townSelection == TOWN_GOBLINS ? "> " : "  ");
    tft.print("Kill Goblins");

    tft.setCursor(20, 100);
    tft.print(townSelection == TOWN_STAY_HOME ? "> " : "  ");
    tft.print("Stay Home");

    tft.setCursor(20, 130);
    tft.print(townSelection == TOWN_DUNGEON ? "> " : "  ");
    tft.print("Explore Dungeon");

    if (townSelection == TOWN_STAY_HOME)
    {
        tft.setTextSize(1);
        tft.setCursor(18, 205);
        tft.print("\"It's dangerous out there.\"");
    }
}

void drawDungeonScreen()
{
    if (isCharacterSheetVisible())
    {
        drawCharacterSheet();
        return;
    }

    drawRoom(dungeon.rooms[dungeon.currentRoom]);

    drawEntities(dungeon);

    drawMoveCursor(dungeon);
}

void drawSpriteTransparent(int x, int y, const uint16_t* sprite)
{
    for (int py = 0; py < SPRITE_H; py++)
    {
        for (int px = 0; px < SPRITE_W; px++)
        {
            uint16_t color =
                pgm_read_word(&sprite[py * SPRITE_W + px]);

            if (color != 0xF81F)
            {
                tft.drawPixel(
                    x + px,
                    y + py,
                    color);
            }
        }
    }
}

void drawSpriteTransparent64(int x, int y, const uint16_t* sprite)
{
    for (int py = 0; py < 64; py++)
    {
        for (int px = 0; px < 64; px++)
        {
            uint16_t color =
                pgm_read_word(&sprite[py * 64 + px]);

            if (color != 0xF81F)
            {
                tft.drawPixel(
                    x + px,
                    y + py,
                    color);
            }
        }
    }
}