//
// Created by james on 7/12/2026.
//

#include "buttons.h"
#include "Arduino.h"

//======================================
// Input State
//======================================

bool encoderLastCLK = HIGH;
unsigned long encoderLastMove = 0;

bool selectLast = HIGH;
bool aLast = HIGH;
bool bLast = HIGH;

const uint16_t ENCODER_DEBOUNCE = 3;

//======================================================
// Start Screen
//======================================================

void handleStartButtons()
{
    bool selectNow = digitalRead(ENCODER_SW);

    if (selectNow == LOW && selectLast == HIGH)
    {
        playSound(SoundEffect::MENU_SELECT);

        gameState = GAME_CHARACTER_CREATION;
        needsRedraw = true;
    }

    selectLast = selectNow;
}

//======================================================
// Character Creation
//======================================================

void handleCharacterCreationButtons()
{
    bool selectNow = digitalRead(ENCODER_SW);
    bool aNow = digitalRead(BUTTON_A);
    bool bNow = digitalRead(BUTTON_B);
    bool clkNow = digitalRead(ENCODER_CLK);

    // Encoder rotation
    if (clkNow != encoderLastCLK && clkNow == LOW)
    {
        if (millis() - encoderLastMove > ENCODER_DEBOUNCE)
        {
            encoderLastMove = millis();

            if (digitalRead(ENCODER_DT) != clkNow)
            {
                rotateCharacterClassCW();
            }
            else
            {
                rotateCharacterClassCCW();
            }

            playSound(SoundEffect::MENU_MOVE);
            needsRedraw = true;
        }
    }

    encoderLastCLK = clkNow;

    // Encoder button = Select Class
    if (selectNow == LOW && selectLast == HIGH)
    {
        playSound(SoundEffect::MENU_SELECT);

        createPreviewCharacter();

        needsRedraw = true;
    }

    // A = Accept Character
    if (aNow == LOW && aLast == HIGH)
    {
        acceptCharacter();

        needsRedraw = true;
    }

    // B = Reroll
    if (bNow == LOW && bLast == HIGH)
    {
        rerollCharacter();

        needsRedraw = true;
    }

    selectLast = selectNow;
    aLast = aNow;
    bLast = bNow;
}

//======================================================
// Town
//======================================================

void handleTownButtons()
{
    bool selectNow = digitalRead(ENCODER_SW);
    bool clkNow = digitalRead(ENCODER_CLK);

    if (clkNow != encoderLastCLK && clkNow == LOW)
    {
        if (millis() - encoderLastMove > ENCODER_DEBOUNCE)
        {
            encoderLastMove = millis();

            if (digitalRead(ENCODER_DT) != clkNow)
            {
                townSelection =
                    (TownOption)((townSelection + 1) % TOWN_OPTION_COUNT);
            }
            else
            {
                townSelection =
                    (TownOption)((townSelection - 1 + TOWN_OPTION_COUNT) % TOWN_OPTION_COUNT);
            }

            playSound(SoundEffect::MENU_MOVE);
            needsRedraw = true;
        }
    }

    encoderLastCLK = clkNow;

    if (selectNow == LOW && selectLast == HIGH)
    {
        playSound(SoundEffect::MENU_SELECT);

        switch (townSelection)
        {
            case TOWN_GOBLINS:

                // TODO:
                // Generate goblin dungeon.

                break;

            case TOWN_STAY_HOME:

                break;

            case TOWN_DUNGEON:

                generateDungeon(dungeon);
                gameState = GAME_DUNGEON;
                break;
        }

        needsRedraw = true;
    }

    selectLast = selectNow;
}

//======================================================
// Dungeon
//======================================================

void handleDungeonButtons()
{
    bool selectNow = digitalRead(ENCODER_SW);
    bool clkNow = digitalRead(ENCODER_CLK);

    if (clkNow != encoderLastCLK && clkNow == LOW)
    {
        if (millis() - encoderLastMove > ENCODER_DEBOUNCE)
        {
            encoderLastMove = millis();

            if (digitalRead(ENCODER_DT) != clkNow)
            {
                rotateDirectionCW();
            }
            else
            {
                rotateDirectionCCW();
            }

            playSound(SoundEffect::MENU_MOVE);
            needsRedraw = true;
        }
    }

    encoderLastCLK = clkNow;

    if (selectNow == LOW && selectLast == HIGH)
    {
        if (tryMovePlayer(dungeon))
        {
            needsRedraw = true;
        }
    }

    selectLast = selectNow;
}

//======================================================
// Main Button Handler
//======================================================

void handleButtons()
{
    switch (gameState)
    {
        case GAME_START:
            handleStartButtons();
            break;

        case GAME_CHARACTER_CREATION:
            handleCharacterCreationButtons();
            break;

        case GAME_TOWN:
            handleTownButtons();
            break;

        case GAME_DUNGEON:
            handleDungeonButtons();
            break;
    }
}