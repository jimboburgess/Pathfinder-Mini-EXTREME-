void handleStartButtons() {

  static bool upLast = HIGH;
  static bool downLast = HIGH;
  static bool aLast = HIGH;
  static bool bLast = HIGH;

  bool upNow = digitalRead(BUTTON_UP);
  bool downNow = digitalRead(BUTTON_DOWN);
  bool aNow = digitalRead(BUTTON_A);
  bool bNow = digitalRead(BUTTON_B);

  bool anyPressed =
    (upNow == LOW && upLast == HIGH) || (downNow == LOW && downLast == HIGH) || (aNow == LOW && aLast == HIGH) || (bNow == LOW && bLast == HIGH);

  if (anyPressed) {

    resetBattle();

    gameState = GAME_BATTLE;

    needsRedraw = true;
  }

  upLast = upNow;
  downLast = downNow;
  aLast = aNow;
  bLast = bNow;
}
void handleBattleButtons() {

  if (showCritScreen)
    return;

  if (waitingForEnemyTurn)
    return;

  static bool upLast = HIGH;
  static bool downLast = HIGH;
  static bool aLast = HIGH;

  bool upNow = digitalRead(BUTTON_UP);
  bool downNow = digitalRead(BUTTON_DOWN);
  bool aNow = digitalRead(BUTTON_A);

  if (battleState == PLAYER_TURN) {

    if (upNow == LOW && upLast == HIGH) {

      selectedOption =
        (BattleOption)((selectedOption - 1 + NUM_BATTLE_OPTIONS) % NUM_BATTLE_OPTIONS);

      needsRedraw = true;
    }

    if (downNow == LOW && downLast == HIGH) {

      selectedOption =
        (BattleOption)((selectedOption + 1) % NUM_BATTLE_OPTIONS);

      needsRedraw = true;
    }

    if (aNow == LOW && aLast == HIGH) {

      switch (selectedOption) {

        case OPTION_ATTACK:
          playerAttack();
          break;

        case OPTION_POTION:
          playerPotion();
          break;

        case OPTION_DEFEND:
          playerDefend();
          break;

        case OPTION_RUN:
          playerRun();
          break;
      }

      needsRedraw = true;
    }
  }

  upLast = upNow;
  downLast = downNow;
  aLast = aNow;
}

void handleEndScreenButtons() {

  static bool upLast = HIGH;
  static bool downLast = HIGH;
  static bool aLast = HIGH;
  static bool bLast = HIGH;

  bool upNow = digitalRead(BUTTON_UP);
  bool downNow = digitalRead(BUTTON_DOWN);
  bool aNow = digitalRead(BUTTON_A);
  bool bNow = digitalRead(BUTTON_B);

  bool anyPressed =
    (upNow == LOW && upLast == HIGH) ||
    (downNow == LOW && downLast == HIGH) ||
    (aNow == LOW && aLast == HIGH) ||
    (bNow == LOW && bLast == HIGH);

  if (anyPressed) {

    if (battleState == PLAYER_WIN) {

      // Continue the dungeon
      resetBattle();

    }
    else if (battleState == PLAYER_LOSE) {

      // Start a new game
      player.hp = player.maxHP;
      player.tempAC = 0;
      player.potions[POTION_HEALING] = 3;

      gameState = GAME_START;
    }

    needsRedraw = true;
  }

  upLast = upNow;
  downLast = downNow;
  aLast = aNow;
  bLast = bNow;
}

void handleButtons() {

  switch (gameState) {

    case GAME_START:
      handleStartButtons();
      break;

    case GAME_BATTLE:

      if (battleState == PLAYER_WIN || battleState == PLAYER_LOSE) {

        handleEndScreenButtons();
      } else {

        handleBattleButtons();
      }

      break;
  }
}