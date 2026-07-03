void handleButtons() {

  static bool upLast = HIGH;
  static bool downLast = HIGH;
  static bool aLast = HIGH;

  bool upNow = digitalRead(BUTTON_UP);
  bool downNow = digitalRead(BUTTON_DOWN);
  bool aNow = digitalRead(BUTTON_A);


  if (upLast && !upNow) {

    selectedOption--;

    if (selectedOption < 0)
      selectedOption = MENU_COUNT - 1;

    drawBattleScreen();
  }


  if (downLast && !downNow) {

    selectedOption++;

    if (selectedOption >= MENU_COUNT)
      selectedOption = 0;

    drawBattleScreen();
  }


  if (aLast && !aNow) {

    // PLAYER TURN
    if (battleState == PLAYER_TURN) {

      // ATTACK
      if (selectedOption == 0) {

        attack(player, goblin);

        if (goblin.hp <= 0)
          battleState = PLAYER_WIN;
        else
          battleState = ENEMY_TURN;
      }

      // DEFEND
      else if (selectedOption == 1) {

        player.tempAC = 2;

        battleMessage = "FIGHTER defends! +2 AC";

        battleState = ENEMY_TURN;
      }

      drawBattleScreen();
    }

    // ENEMY TURN
    else if (battleState == ENEMY_TURN) {

      attack(goblin, player);

      // Defense only lasts one enemy turn
      player.tempAC = 0;

      if (player.hp <= 0) {

        battleState = PLAYER_LOSE;
      } else {

        battleState = PLAYER_TURN;
      }

      drawBattleScreen();
    }
  }


  upLast = upNow;
  downLast = downNow;
  aLast = aNow;
}