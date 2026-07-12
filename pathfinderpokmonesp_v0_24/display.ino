void drawStartScreen() {

  tft.fillScreen(ST77XX_BLACK);

  playSound(SoundEffect::TITLE_THEME);

  drawSpriteTransparent64(
    88, 90, FIGHTERWALK1);

  tft.setTextColor(ST77XX_WHITE);

  tft.setTextSize(3);
  tft.setCursor(30, 30);
  tft.println("Pathfinder");

  tft.setCursor(5, 60);
  tft.println("Mini EXTREME!");

  //tft.fillRect(88, 90, WALK_W, WALK_H, ST77XX_BLACK);

  tft.setTextSize(2);
  tft.setCursor(30, 205);
  tft.println("Press A Button");
}

void drawStartAnimation() {

  static bool lastFrame = false;

  bool frame = (millis() / 800) % 2;

  if (frame == lastFrame)
    return;

  lastFrame = frame;

  const uint16_t* fighterSprite =
    frame ? FIGHTERWALK1 : FIGHTERWALK2;

  // Erase only the sprite
  tft.fillRect(
    88, 90, 64, 64, ST77XX_BLACK);

  drawSpriteTransparent64(
    88,
    90,
    fighterSprite);
}

void drawTownScreen()
{
    tft.fillScreen(ST77XX_BLACK);

    tft.setTextColor(ST77XX_WHITE);

    // Title
    tft.setTextSize(3);
    tft.setCursor(72, 20);
    tft.print("Town");

    // Menu
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

    // Little joke at the bottom
    if (townSelection == TOWN_STAY_HOME)
    {
        tft.setTextSize(1);
        tft.setCursor(18, 205);
        tft.print("\"It's dangerous out there.\"");
    }
}

void drawDungeonScreen()
{
    drawRoom(dungeon.rooms[dungeon.currentRoom]);

    drawEntities(dungeon);
    // Any UI or text can be drawn after this.
    drawMoveCursor(dungeon);
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
void drawSpriteTransparent64(int x, int y, const uint16_t* sprite) {

  for (int py = 0; py < 64; py++) {

    for (int px = 0; px < 64; px++) {

      uint16_t color =
        pgm_read_word(&sprite[py * 64 + px]);

      if (color != 0xF81F) {  // transparent magenta
        tft.drawPixel(x + px, y + py, color);
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


    delay(500);
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


    delay(1000);
    tft.setTextColor(ST77XX_RED);
    tft.setTextSize(4);
    tft.setCursor(15, 90);
    tft.println("YOU DEAD!");

    tft.setTextSize(1);
    tft.setCursor(30, 200);
    tft.println("Press A to try again");

    playSound(SoundEffect::GAME_OVER);

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

  tft.setCursor(10, 200);
  tft.print(battleMessage);

  tft.setTextSize(1);

  for (int i = 0; i < NUM_BATTLE_OPTIONS; i++) {

    tft.setCursor(
      20,
      140 + i * 10);

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

  const uint16_t* fighterSprite;

  if (animationState == ANIM_SWING) {

    fighterSprite = fighterFrame2;  // attack pose

  } else {

    bool animFrame = (millis() / 400) % 2;

    fighterSprite =
      animFrame ? fighterFrame1 : fighterFrame2;
  }

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

  drawSpriteTransparent(
    fighterX,
    fighterY,
    fighterSprite);

  drawSpriteTransparent(
    enemyX,
    enemyY,
    enemySprite);
}

void redrawBattleSprites() {

  // Erase fighter area
  tft.fillRect(
    fighterX - 2,
    fighterY - 2,
    36,
    36,
    ST77XX_BLACK);

  // Erase enemy area
  tft.fillRect(
    enemyX - 2,
    enemyY - 2,
    36,
    36,
    ST77XX_BLACK);

  drawBattleSprites();
}