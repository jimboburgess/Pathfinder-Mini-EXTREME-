//
// Created by james on 7/14/2026.
//

#include "charcreationscreen.h"

#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>
#include "dungeon/dungeon.h"
#include "characters/charactercreation.h"
#include "config.h"
#include "data/game.h"

static const char *classNames[] =
{
    "Fighter",
    "Rogue",
    "Wizard",
    "Cleric"
};

extern Adafruit_ST7789 tft;

static Character previewCharacter;
static CharacterClass selectedClass = CLASS_FIGHTER;
static bool showingPreview = false;

void enterCharacterCreation() {
    selectedClass = CLASS_FIGHTER;
    showingPreview = false;

    needsRedraw = true;
}

static void drawClassSelection() {
    tft.fillScreen(ST77XX_BLACK);

    tft.setTextColor(ST77XX_WHITE);
    tft.setTextSize(2);

    tft.setCursor(30, 15);
    tft.println("Choose Class");

    for (int i = 0; i < 4; i++) {
        tft.setCursor(40, 60 + i * 35);

        if (i == selectedClass)
            tft.print("> ");
        else
            tft.print("  ");

        tft.println(classNames[i]);
    }

    tft.setTextSize(1);

    tft.setCursor(15, 220);
    tft.print("Encoder = Select   A = Choose");
}

static void drawPreview() {
    tft.fillScreen(ST77XX_BLACK);

    tft.setTextColor(ST77XX_WHITE);
    tft.setTextSize(2);

    tft.setCursor(10, 10);
    tft.println(classNames[selectedClass]);

    tft.setTextSize(2);

    tft.setCursor(10, 45);
    tft.print("STR ");
    tft.println(previewCharacter.abilities.strength);

    tft.print("DEX ");
    tft.println(previewCharacter.abilities.dexterity);

    tft.print("CON ");
    tft.println(previewCharacter.abilities.constitution);

    tft.print("INT ");
    tft.println(previewCharacter.abilities.intelligence);

    tft.print("WIS ");
    tft.println(previewCharacter.abilities.wisdom);

    tft.print("CHA ");
    tft.println(previewCharacter.abilities.charisma);

    tft.println();

    tft.print("HP ");
    tft.println(previewCharacter.maxHP);

    tft.setCursor(10, 220);

    tft.print("A=Accept  Encoder=Reroll");
}

void drawCharacterCreationScreen() {
    if (showingPreview)
        drawPreview();
    else
        drawClassSelection();
}

//======================================================
// Rotate Class Selection
//======================================================

void rotateCharacterClassCW() {
    if (showingPreview)
        return;

    selectedClass = (CharacterClass) ((selectedClass + 1) % 4);

    needsRedraw = true;
}

void rotateCharacterClassCCW() {
    if (showingPreview)
        return;

    if (selectedClass == CLASS_FIGHTER) {
        selectedClass = CLASS_CLERIC;
    } else {
        selectedClass = (CharacterClass) (selectedClass - 1);
    }

    needsRedraw = true;
}

//======================================================
// Create Preview Character
//======================================================

void createPreviewCharacter() {
    createCharacter(previewCharacter, selectedClass);

    showingPreview = true;

    needsRedraw = true;
}

//======================================================
// Reroll Character
//======================================================

void rerollCharacter() {
    if (!showingPreview)
        return;

    createCharacter(previewCharacter, selectedClass);

    needsRedraw = true;
}

//======================================================
// Accept Character
//======================================================

void acceptCharacter() {
    if (!showingPreview)
        return;

    // Copy preview into the real player
    player = previewCharacter;

    // Add the player to the dungeon
    addCharacterToDungeon(&player);

    // Continue to town
    gameState = GAME_TOWN;

    showingPreview = false;

    needsRedraw = true;
}
