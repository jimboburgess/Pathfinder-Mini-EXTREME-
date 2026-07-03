

void drawBattleScreen() {


  tft.fillScreen(ST77XX_BLACK);

  // WIN SCREEN
  if (battleState == PLAYER_WIN) {

    tft.setTextColor(ST77XX_GREEN);
    tft.setTextSize(4);
    tft.setCursor(30, 90);
    tft.println("YOU WIN!");

    return;
  }

  // LOSE SCREEN
  if (battleState == PLAYER_LOSE) {

    tft.setTextColor(ST77XX_RED);
    tft.setCursor(30, 90);
    tft.println("YOU DIED!");

    return;
  }
  tft.fillScreen(ST77XX_BLACK);

  tft.setTextColor(ST77XX_WHITE);
  tft.setTextSize(2);

  tft.setCursor(20, 20);
  tft.print(player.name);

  tft.setCursor(140, 20);
  tft.print("HP:");
  tft.print(player.hp);

  tft.setCursor(100, 70);
  tft.print("VS");

  tft.setCursor(20, 110);
  tft.print(goblin.name);

  tft.setCursor(140, 110);
  tft.print("HP:");
  tft.print(goblin.hp);

  tft.setTextSize(1);
  tft.setCursor(10, 220);
  tft.print(battleMessage);

  for (int i = 0; i < MENU_COUNT; i++) {

    tft.setCursor(20, 170 + i * 30);

    if (i == selectedOption) {
      tft.print("> ");
    } else {
      tft.print("  ");
    }

    tft.print(menuOptions[i]);
  }
}