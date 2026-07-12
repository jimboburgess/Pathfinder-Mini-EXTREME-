#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>
#include <SPI.h>
#include "config.h"
#include "characters.h"
#include "sprites.h"
#include "battle.h"
#include "animations.h"
#include "audio.h"
#include "dungeon.h"
#include "roomgen.h"
#include "roomdraw.h"
#include "dungeonplayer.h"


Adafruit_ST7789 tft =
  Adafruit_ST7789(
    TFT_CS,
    TFT_DC,
    TFT_RST);

enum GameState {
  GAME_START,
  GAME_TOWN,
  GAME_BATTLE,
  GAME_DUNGEON
};

GameState gameState = GAME_START;

enum TownOption {
  TOWN_GOBLINS,
  TOWN_STAY_HOME,
  TOWN_DUNGEON,

  TOWN_OPTION_COUNT
};

TownOption townSelection = TOWN_GOBLINS;



enum BattleState {

  PLAYER_TURN,
  ENEMY_TURN,
  PLAYER_WIN,
  PLAYER_LOSE

};


Character player = {
  "Tony",
  12,   //hp
  12,   //maxhp
  18,   //AC
  0,    // tempAC
  4,    //atkbonus
  8,    //weaponsides
  3,    //damage bonus
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
bool spritesNeedRedraw = false;

bool lastAnimFrame = false;

//======================================
// Sprite Positions
//======================================

int fighterX = 20;
int fighterY = 50;

int enemyX = 188;
int enemyY = 50;

unsigned long enemyTurnStart = 0;
bool waitingForEnemyTurn = false;

bool waitingForVictory = false;
unsigned long victoryStart = 0;

bool waitingForTown = false;
unsigned long townStart = 0;

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

  //audio
  initAudio();

  randomSeed(analogRead(0));

  generateDungeon(dungeon);

  drawRoom(
    dungeon.rooms[dungeon.currentRoom]);

  printRoom(dungeon.rooms[dungeon.currentRoom]);

  Serial.println("Dungeon:");

  for (int i = 0; i < MAX_ROOMS; i++) {
    Serial.print("Room ");
    Serial.print(i);
    Serial.print(": ");
    Serial.println(roomTypeName(dungeon.rooms[i].type));
  }

  pinMode(ENCODER_CLK, INPUT_PULLUP);
  pinMode(ENCODER_DT, INPUT_PULLUP);
  pinMode(ENCODER_SW, INPUT_PULLUP);

  pinMode(BUTTON_A, INPUT_PULLUP);
  pinMode(BUTTON_B, INPUT_PULLUP);

  needsRedraw = true;
}

void loop() {

  handleButtons();

  updateAudio();

  switch (gameState) {

    //==============================
    // START SCREEN
    //==============================
    case GAME_START:
      {

        if (needsRedraw) {

          drawStartScreen();

          needsRedraw = false;
        }

        drawStartAnimation();

        break;
      }
      //==============================
      // TOWN
      //==============================
    case GAME_TOWN:
      {

        if (needsRedraw) {

          drawTownScreen();

          needsRedraw = false;
        }

        break;
      }
    //==============================
    // BATTLE
    //==============================
    case GAME_BATTLE:
      {

        // Update any active battle animations
        updateBattleAnimation();

        // Enemy attacks after 1 second
        if (waitingForEnemyTurn && millis() - enemyTurnStart >= 1000) {

          waitingForEnemyTurn = false;

          takeEnemyTurn();

          needsRedraw = true;
        }

        // Return to town after running away
        if (waitingForTown && millis() - townStart >= 1000) {
          Serial.println("Going to town");
          waitingForTown = false;

          waitingForEnemyTurn = false;
          waitingForVictory = false;
          battleState = PLAYER_TURN;
          animationState = ANIM_IDLE;
          // Reset sprite positions
          fighterX = 20;
          enemyX = 188;
          gameState = GAME_TOWN;

          needsRedraw = true;
          break;
        }

        // Show "Enemy Defeated!" for 1 second before the win screen
        if (waitingForVictory && millis() - victoryStart >= 1000) {

          waitingForVictory = false;

          animationState = ANIM_IDLE;
          fighterX = 20;

          battleState = PLAYER_WIN;

          needsRedraw = true;
        }

        // Keep crit screen animated
        if (showCritScreen) {
          needsRedraw = true;
        }

        // Idle sprite animation
        bool currentAnimFrame = (millis() / 400) % 2;

        if (currentAnimFrame != lastAnimFrame) {

          lastAnimFrame = currentAnimFrame;

          spritesNeedRedraw = true;
        }

        // Only redraw the sprite area if needed
        if (spritesNeedRedraw) {

          redrawBattleSprites();

          spritesNeedRedraw = false;
        }

        // Redraw the entire UI only when necessary
        if (needsRedraw) {

          drawBattleScreen();

          needsRedraw = false;
        }

        break;
      }
    case GAME_DUNGEON:
      if (needsRedraw) {
        drawDungeonScreen();
        needsRedraw = false;
      }

      break;
  }

}