//======================================
// Input State
//======================================

bool encoderLastCLK = HIGH;
unsigned long encoderLastMove = 0;

bool selectLast = HIGH;
bool aLast = HIGH;
bool bLast = HIGH;

const uint16_t ENCODER_DEBOUNCE = 3;

//The encoder always performs the most obvious action.

//The A button always asks "What else can I do?"

//======================================================
// Start Screen
//======================================================

void handleStartButtons() {

  bool selectNow = digitalRead(ENCODER_SW);

  if (selectNow == LOW && selectLast == HIGH) {
    gameState = GAME_TOWN;
    needsRedraw = true;
  }

  selectLast = selectNow;
}
//======================================================
// TOWN
//======================================================
void handleTownButtons() {
  bool selectNow = digitalRead(ENCODER_SW);
  bool clkNow = digitalRead(ENCODER_CLK);

  // Encoder rotation
  if (clkNow != encoderLastCLK && clkNow == LOW) {
    if (millis() - encoderLastMove > ENCODER_DEBOUNCE) {
      encoderLastMove = millis();

      if (digitalRead(ENCODER_DT) != clkNow) {
        // Clockwise
        townSelection =
          (TownOption)((townSelection + 1) % TOWN_OPTION_COUNT);
      } else {
        // Counter-clockwise
        townSelection =
          (TownOption)((townSelection - 1 + TOWN_OPTION_COUNT) % TOWN_OPTION_COUNT);
      }

      playSound(SoundEffect::MENU_MOVE);
      needsRedraw = true;
    }
  }

  encoderLastCLK = clkNow;

  // Encoder button pressed
  if (selectNow == LOW && selectLast == HIGH) {
    playSound(SoundEffect::MENU_SELECT);

    switch (townSelection) {
      case TOWN_GOBLINS:
        resetBattle();
        gameState = GAME_BATTLE;
        break;

      case TOWN_STAY_HOME:
        // Do nothing for now 🙂
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

void handleDungeonButtons() {
  bool selectNow = digitalRead(ENCODER_SW);

  bool clkNow = digitalRead(ENCODER_CLK);

  if (clkNow != encoderLastCLK && clkNow == LOW) {
    if (millis() - encoderLastMove > ENCODER_DEBOUNCE) {
      encoderLastMove = millis();

      if (digitalRead(ENCODER_DT) != clkNow) {
        rotateDirectionCW();
      } else {
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
// Battle
//======================================================

void handleBattleButtons() {

  if (waitingForEnemyTurn)
    return;

  if (waitingForVictory)
    return;

  if (showCritScreen)
    return;

  if (waitingForTown)
    return;

  bool selectNow = digitalRead(ENCODER_SW);
  bool aNow = digitalRead(BUTTON_A);
  bool bNow = digitalRead(BUTTON_B);

  bool clkNow = digitalRead(ENCODER_CLK);

  if (clkNow != encoderLastCLK && clkNow == LOW) {

    if (millis() - encoderLastMove > ENCODER_DEBOUNCE) {

      encoderLastMove = millis();

      if (digitalRead(ENCODER_DT) != clkNow) {

        // Clockwise
        selectedOption =
          (BattleOption)((selectedOption + 1) % NUM_BATTLE_OPTIONS);

      } else {

        // Counter-clockwise
        selectedOption =
          (BattleOption)((selectedOption - 1 + NUM_BATTLE_OPTIONS) % NUM_BATTLE_OPTIONS);
      }

      playSound(SoundEffect::MENU_MOVE);

      needsRedraw = true;
    }
  }

  encoderLastCLK = clkNow;

  if (selectNow == LOW && selectLast == HIGH) {

    playSound(SoundEffect::MENU_SELECT);

    switch (selectedOption) {

      case OPTION_ATTACK:
        takePlayerTurn();
        break;

      case OPTION_POTION:
        useHealingPotion();
        break;

      case OPTION_DEFEND:
        defend();
        break;

      case OPTION_RUN:
        runAway();
        break;
    }

    needsRedraw = true;
  }

  selectLast = selectNow;
}

//======================================================
// End Screens
//======================================================

void handleEndScreenButtons() {

  bool selectNow = digitalRead(ENCODER_SW);
  bool aNow = digitalRead(BUTTON_A);
  bool bNow = digitalRead(BUTTON_B);

  bool anyPressed =
    (selectNow == LOW && selectLast == HIGH) || (bNow == LOW && bLast == HIGH);

  if (anyPressed) {

    if (battleState == PLAYER_WIN) {

      // Continue the dungeon
      resetBattle();

    } else if (battleState == PLAYER_LOSE) {

      // Start a new game
      player.hp = player.maxHP;
      player.tempAC = 0;
      player.potions[POTION_HEALING] = 3;

      gameState = GAME_START;
    }

    needsRedraw = true;
  }

  selectLast = selectNow;
  bLast = bNow;
}

//======================================================
// Main Button Handler
//======================================================

void handleButtons() {

  switch (gameState) {

    case GAME_START:
      handleStartButtons();
      break;

    case GAME_TOWN:
      handleTownButtons();
      break;

    case GAME_BATTLE:

      if (battleState == PLAYER_WIN || battleState == PLAYER_LOSE) {

        handleEndScreenButtons();

      } else {

        handleBattleButtons();
      }

      break;

    case GAME_DUNGEON:
      handleDungeonButtons();
      break;
  }
}