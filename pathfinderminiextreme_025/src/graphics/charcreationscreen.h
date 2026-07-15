#ifndef CHARACTERCREATIONSCREEN_H
#define CHARACTERCREATIONSCREEN_H

#include "characters/characters.h"

void enterCharacterCreation();

void drawCharacterCreationScreen();

// Called from buttons.cpp
void rotateCharacterClassCW();
void rotateCharacterClassCCW();

void createPreviewCharacter();
void rerollCharacter();
void acceptCharacter();

#endif