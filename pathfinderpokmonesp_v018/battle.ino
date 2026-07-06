#include "battle.h"

BattleOption selectedOption = OPTION_ATTACK;

void attack(Character& attacker, Character& defender) {

  int roll = rollDie(20);
  int total = roll + attacker.attackBonus;

  bool critical = (roll == 20);

  if (critical || total >= defender.armorClass + defender.tempAC) {

    int damage =
      rollDie(attacker.weaponSides)
      + attacker.damageBonus;

    if (critical) {

      damage *= 2;

      showCritScreen = true;
      critStartTime = millis();

      critText =
        String(attacker.name) + " CRITICALS!";

      needsRedraw = true;
    }
    defender.hp -= damage;

    if (defender.hp < 0)
      defender.hp = 0;

    battleMessage =
      String(attacker.name) + " hits for " + String(damage);

  } else {

    battleMessage =
      String(attacker.name) + " misses!";
  }
}


void resetBattle() {

  player.tempAC = 0;

  showCritScreen = false;
  critText = "";

  generateGoblin();

  selectedOption = OPTION_ATTACK;

  battleState = PLAYER_TURN;

  battleMessage = "A goblin appears!";

  needsRedraw = true;
}

void generateGoblin() {

  EnemyType type = (EnemyType)random(1, 4);

  switch (type) {

    case GOBLIN_SPEARMAN:

      goblin = {
        "GOBLIN",
        8,   // HP
        8,   // Max HP
        14,  // AC
        0,   // Temp AC
        2,   // Attack Bonus
        6,   // Weapon Dice
        1,   // Damage Bonus
        0,   // Potions
        GOBLIN_SPEARMAN
      };

      break;


    case GOBLIN_ARCHER:

      goblin = {
        "ARCHER",
        6,
        6,
        13,
        0,
        3,
        6,
        0,
        0,
        GOBLIN_ARCHER
      };

      break;


    case GOBLIN_CHIEF:

      goblin = {
        "CHIEF",
        15,
        15,
        16,
        0,
        4,
        8,
        2,
        0,
        GOBLIN_CHIEF
      };

      break;
  }
}

const char* menuOptions[] = {
  "Attack",
  "Potion",
  "Defend",
  "Run"
};

void playerAttack() {

  attack(player, goblin);

  if (goblin.hp <= 0) {

    // Drop 0-2 healing potions
    potionsFound = random(0, 3);

    player.potions[POTION_HEALING] += potionsFound;

    battleMessage = "Enemy defeated!";
battleState = PLAYER_WIN;

    battleState = PLAYER_WIN;
  } else {

    waitingForEnemyTurn = true;
    enemyTurnStart = millis();
  }
}
void playerPotion() {

  usePotion(player, POTION_HEALING);

  if (battleMessage != "No healing potions!") {
    waitingForEnemyTurn = true;
    enemyTurnStart = millis();
  }
}
void playerDefend() {

  player.tempAC = 2;

  battleMessage = "FIGHTER defends! +2 AC";

  waitingForEnemyTurn = true;
  enemyTurnStart = millis();
}
void playerRun() {

  battleMessage = "Can't escape!";

  waitingForEnemyTurn = true;
  enemyTurnStart = millis();

  // Later we'll add a chance to escape.
}

void enemyTurn() {

  attack(goblin, player);

  // Defense only lasts one enemy turn
  player.tempAC = 0;

  if (player.hp <= 0) {
    battleState = PLAYER_LOSE;
  } else {
    battleState = PLAYER_TURN;
  }
}
