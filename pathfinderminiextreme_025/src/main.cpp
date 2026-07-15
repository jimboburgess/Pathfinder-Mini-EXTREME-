#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>
#include <SPI.h>

#include "config.h"
#include "data/game.h"

#include "audio/audio.h"

#include "characters/characters.h"

#include "dungeon/combat.h"
#include "dungeon/dungeon.h"
#include "dungeon/dungeonplayer.h"
#include "dungeon/roomdraw.h"
#include "dungeon/roomgen.h"
#include "graphics/charcreationscreen.h"
#include "graphics/display.h"
#include "graphics/sprites.h"

#include "input/buttons.h"

Adafruit_ST7789 tft(
    TFT_CS,
    TFT_DC,
    TFT_RST);

GameState gameState = GAME_START;

TownOption townSelection = TOWN_GOBLINS;

Character player;

bool needsRedraw = true;

void setup()
{
    Serial.begin(115200);

    // Turn on backlight
    pinMode(TFT_BL, OUTPUT);
    digitalWrite(TFT_BL, HIGH);

    // Start SPI
    SPI.begin(
        TFT_SCL,
        -1,
        TFT_SDA,
        TFT_CS);

    // Initialize display
    tft.init(240, 240);
    tft.setRotation(0);

    // Initialize audio
    initAudio();

    // Seed random number generator
    randomSeed(analogRead(0));

    // Generate dungeon
    generateDungeon(dungeon);

    // Create monsters


    drawRoom(dungeon.rooms[dungeon.currentRoom]);
    printRoom(dungeon.rooms[dungeon.currentRoom]);

    Serial.println("Dungeon:");

    for (int i = 0; i < MAX_ROOMS; i++)
    {
        Serial.print("Room ");
        Serial.print(i);
        Serial.print(": ");
        Serial.println(roomTypeName(dungeon.rooms[i].type));
    }

    // Initialize controls
    pinMode(ENCODER_CLK, INPUT_PULLUP);
    pinMode(ENCODER_DT, INPUT_PULLUP);
    pinMode(ENCODER_SW, INPUT_PULLUP);

    pinMode(BUTTON_A, INPUT_PULLUP);
    pinMode(BUTTON_B, INPUT_PULLUP);

    needsRedraw = true;
}

void loop()
{
    handleButtons();

    updateAudio();

    switch (gameState)
    {
        case GAME_START:
        {
            if (needsRedraw)
            {
                drawStartScreen();
                needsRedraw = false;
            }

            drawStartAnimation();
            break;
        }

        case GAME_CHARACTER_CREATION:
        {
            if (needsRedraw)
            {
                drawCharacterCreationScreen();
                needsRedraw = false;
            }

            break;
        }

        case GAME_TOWN:
        {
            if (needsRedraw)
            {
                drawTownScreen();
                needsRedraw = false;
            }

            break;
        }

        case GAME_DUNGEON:
        {
            checkForCombat();

            if (needsRedraw)
            {
                drawDungeonScreen();
                needsRedraw = false;
            }

            break;
        }
    }
}