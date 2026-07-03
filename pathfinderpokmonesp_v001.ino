#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>
#include <SPI.h>
#include "config.h"
#include "characters.h"

Adafruit_ST7789 tft =
  Adafruit_ST7789(
    TFT_CS,
    TFT_DC,
    TFT_RST);




Character player = {
  "FIGHTER",
  12, //hp
  12,  //maxhp
  18,  //AC
  0,   // tempAC
  4,  //atkbonus
  8,  //weaponsides
  3  //damage bonus
};

Character goblin = {
  "GOBLIN",
  6,
  6,
  16,
  0,   // tempAC
  2,
  6,
  0
};

int selectedOption = 0;

const char* menuOptions[] = {
  "ATTACK",
  "DEFEND"
};

const int MENU_COUNT = 2;

String battleMessage = "A goblin appears!";

int rollDie(int sides) {
  return random(1, sides + 1);
}

void attack(Character& attacker, Character& defender) {

  int roll = rollDie(20);
  int total = roll + attacker.attackBonus;

  if (roll == 20 ||
    total >= defender.armorClass + defender.tempAC) {

    int damage =
      rollDie(attacker.weaponSides)
      + attacker.damageBonus;

    defender.hp -= damage;

    if (defender.hp < 0)
      defender.hp = 0;

    battleMessage =
      String(attacker.name) +
      " hits for " +
      String(damage);

  }
  else {

    battleMessage =
      String(attacker.name) +
      " misses!";

  }
}

enum BattleState {

  PLAYER_TURN,
  ENEMY_TURN,
  PLAYER_WIN,
  PLAYER_LOSE

};

BattleState battleState = PLAYER_TURN;

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

  drawBattleScreen();
}
void loop() {

  handleButtons();

  if (!digitalRead(BUTTON_UP))
    Serial.println("UP");

  if (!digitalRead(BUTTON_DOWN))
    Serial.println("DOWN");

  if (!digitalRead(BUTTON_A))
    Serial.println("A");

  if (!digitalRead(BUTTON_B))
    Serial.println("B");

  delay(100);
}