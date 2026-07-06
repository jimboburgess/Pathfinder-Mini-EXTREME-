#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>
#include <SPI.h>
#include "config.h"
#include "characters.h"
#include "sprites.h"
#include "battle.h"


Adafruit_ST7789 tft =
  Adafruit_ST7789(
    TFT_CS,
    TFT_DC,
    TFT_RST);

enum GameState {

  GAME_START,
  GAME_BATTLE

};

GameState gameState = GAME_START;

enum BattleState {

  PLAYER_TURN,
  ENEMY_TURN,
  PLAYER_WIN,
  PLAYER_LOSE

};


Character player = {
  "Dale",
  12,  //hp
  12,  //maxhp
  18,  //AC
  0,   // tempAC
  4,   //atkbonus
  8,   //weaponsides
  3,   //damage bonus
  3,    // starting potions
  NONE  //enemy
};

Character goblin;

BattleState battleState = PLAYER_TURN;

String battleMessage = "A goblin appears!";

bool showCritScreen = false;
unsigned long critStartTime = 0;
String critText = "";

bool needsRedraw = true;

bool lastAnimFrame = false;

unsigned long enemyTurnStart = 0;
bool waitingForEnemyTurn = false;
int potionsFound = 0;

int rollDie(int sides) {
  return random(1, sides + 1);
}


void setup() {

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

  // Try rotation 0 first
  tft.setRotation(0);

  randomSeed(micros());

  pinMode(BUTTON_UP, INPUT_PULLUP);
  pinMode(BUTTON_DOWN, INPUT_PULLUP);
  pinMode(BUTTON_A, INPUT_PULLUP);
  pinMode(BUTTON_B, INPUT_PULLUP);

  needsRedraw = true;
}

void loop() {

  handleButtons();

  switch (gameState) {

    //==============================
    // START SCREEN
    //==============================

    case GAME_START:

      if (needsRedraw) {

        drawStartScreen();

        needsRedraw = false;
      }

      break;

    //==============================
    // BATTLE
    //==============================

    case GAME_BATTLE:

      // Enemy attacks after 1 second
      if (waitingForEnemyTurn &&
          millis() - enemyTurnStart >= 1000) {

        waitingForEnemyTurn = false;

        enemyTurn();

        needsRedraw = true;
      }

      // Keep crit screen animated
      if (showCritScreen) {
        needsRedraw = true;
      }

      // Animate sprites
      bool currentAnimFrame = (millis() / 400) % 2;

      if (currentAnimFrame != lastAnimFrame) {

        lastAnimFrame = currentAnimFrame;

        drawBattleSprites();
      }

      // Redraw battle UI when needed
      if (needsRedraw) {

        drawBattleScreen();

        needsRedraw = false;
      }

      break;
  }

  delay(10);
}