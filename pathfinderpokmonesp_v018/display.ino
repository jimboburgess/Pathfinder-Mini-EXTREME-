void drawStartScreen() {

  tft.fillScreen(ST77XX_BLACK);

  tft.setTextColor(ST77XX_WHITE);

  tft.setTextSize(3);
  tft.setCursor(60, 40);
  tft.println("Tony");

  tft.setCursor(20, 75);
  tft.println("The Fighter ");

  // Fighter sprite
  drawSpriteTransparent(
    104,
    105,
    fighterFrame1);

  tft.setTextSize(2);
  tft.setCursor(35, 200);
  tft.println("Press A button");
}

void drawCriticalHit() {

  static bool flash = false;

  flash = !flash;

  if (flash)
    tft.fillScreen(ST77XX_RED);
  else
    tft.fillScreen(ST77XX_YELLOW);

  tft.setTextColor(ST77XX_WHITE);
  tft.setTextSize(4);
  tft.setCursor(15, 80);
  tft.print("CRIT!");

  tft.setTextSize(2);
  tft.setCursor(5, 150);
  tft.print(critText);
}


void drawSpriteTransparent(int x, int y, const uint16_t* sprite) {

  for (int py = 0; py < SPRITE_H; py++) {

    for (int px = 0; px < SPRITE_W; px++) {

      uint16_t color =
        pgm_read_word(&sprite[py * SPRITE_W + px]);

      if (color != 0xF81F) {

        tft.drawPixel(
          x + px,
          y + py,
          color);
      }
    }
  }
}


void drawBattleScreen() {

  tft.fillScreen(ST77XX_BLACK);

  //==========================
  // Critical Hit Screen
  //==========================

  if (showCritScreen) {

    if (millis() - critStartTime > 3000) {

      showCritScreen = false;
      needsRedraw = true;

      return;
    }

    drawCriticalHit();
    return;
  }

  //==========================
  // Win Screen
  //==========================

  if (battleState == PLAYER_WIN) {

    tft.setTextColor(ST77XX_GREEN);
    tft.setTextSize(4);
    tft.setCursor(30, 90);
    tft.println("YOU WIN!");

    tft.setTextSize(2);
    tft.setCursor(30, 150);

    if (potionsFound == 0) {

      tft.print("No Potions");

    } else {

      tft.print("Found ");
      tft.print(potionsFound);
      tft.print(" potion");

      if (potionsFound > 1)
        tft.print("s");
    }

    tft.setTextSize(1);
    tft.setCursor(30, 210);
    tft.print("Press Any Button");

    return;
  }

  //==========================
  // Lose Screen
  //==========================

  if (battleState == PLAYER_LOSE) {

    tft.setTextColor(ST77XX_RED);
    tft.setTextSize(4);
    tft.setCursor(15, 90);
    tft.println("YOU DEAD!");

    tft.setTextSize(1);
    tft.setCursor(30, 200);
    tft.println("Press A to try again");

    return;
  }

  //==========================
  // Select Animation Frame
  //==========================

  bool animFrame = (millis() / 400) % 2;

  const uint16_t* fighterSprite =
    animFrame ? fighterFrame1 : fighterFrame2;

  const uint16_t* enemySprite = goblinFrame1;

  switch (goblin.enemyType) {

    case GOBLIN_SPEARMAN:
      enemySprite =
        animFrame ? goblinFrame1 : goblinFrame2;
      break;

    case GOBLIN_ARCHER:
      enemySprite =
        animFrame ? goblinArcherFrame1 : goblinArcherFrame2;
      break;

    case GOBLIN_CHIEF:
      enemySprite =
        animFrame ? goblinChiefFrame1 : goblinChiefFrame2;
      break;

    default:
      enemySprite =
        animFrame ? goblinFrame1 : goblinFrame2;
      break;
  }


  //==========================
  // Draw UI
  //==========================

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

  for (int i = 0; i < NUM_BATTLE_OPTIONS; i++) {

    tft.setCursor(
      20,
      170 + i * 10);

    if (i == selectedOption)
      tft.print("> ");
    else
      tft.print("  ");

    tft.print(menuOptions[i]);
  }
  drawBattleSprites();
}

void drawBattleSprites() {

  // Don't draw sprites over special screens
  if (showCritScreen || battleState == PLAYER_WIN || battleState == PLAYER_LOSE) {
    return;
  }

  // Erase only the sprite areas
  tft.fillRect(20, 50, SPRITE_W, SPRITE_H, ST77XX_BLACK);
  tft.fillRect(190, 50, SPRITE_W, SPRITE_H, ST77XX_BLACK);

  bool animFrame = (millis() / 400) % 2;

  const uint16_t* fighterSprite =
    animFrame ? fighterFrame1 : fighterFrame2;

  const uint16_t* enemySprite = goblinFrame1;

  switch (goblin.enemyType) {

    case GOBLIN_SPEARMAN:
      enemySprite = animFrame ? goblinFrame1 : goblinFrame2;
      break;

    case GOBLIN_ARCHER:
      enemySprite = animFrame ? goblinArcherFrame1 : goblinArcherFrame2;
      break;

    case GOBLIN_CHIEF:
      enemySprite = animFrame ? goblinChiefFrame1 : goblinChiefFrame2;
      break;

    default:
      break;
  }

  drawSpriteTransparent(20, 50, fighterSprite);
  drawSpriteTransparent(190, 50, enemySprite);
}