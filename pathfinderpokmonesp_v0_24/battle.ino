#include "battle.h"

BattleOption selectedOption = OPTION_ATTACK;

const char* menuOptions[] = {
  "Attack",
  "Potion",
  "Defend",
  "Run"
};

//======================================================
// Combat Engine
//======================================================

void performAttack(Character& attacker, Character& defender) {

  int roll = rollDie(20);
  int total = roll + attacker.attackBonus;

  bool critical = (roll == 20);

  if (critical || total >= defender.armorClass + defender.tempAC) {

    int damage =
      rollDie(attacker.weaponSides)
      + attacker.damageBonus;

    if (critical) {

      playSound(SoundEffect::CRIT);

      damage *= 2;

      showCritScreen = true;
      critStartTime = millis();

      critText =
        String(attacker.name) + " CRITICAL HIT!";

      needsRedraw = true;

    } else {

      if (attacker.enemyType == EnemyType::NONE) {
        // Player attack
        playSound(SoundEffect::ATTACK);
      } else {
        // Monster attack
        playSound(SoundEffect::GOBLIN_ATTACK);
      }
    }

    defender.hp -= damage;

    if (defender.hp < 0)
      defender.hp = 0;
    if (defender.hp == 0) {
      playSound(SoundEffect::ENEMY_DIE);
    }

    battleMessage =
      String(attacker.name) + " hits for " + String(damage);

  } else {

    playSound(SoundEffect::MISS);

    battleMessage =
      String(attacker.name) + " misses!";
  }
}

//======================================================
// Battle Setup
//======================================================

void resetBattle() {

  player.tempAC = 0;

  showCritScreen = false;
  critText = "";

  waitingForEnemyTurn = false;
  waitingForVictory = false;

  generateGoblin();

  selectedOption = OPTION_ATTACK;

  battleState = PLAYER_TURN;

  battleMessage = "A goblin appears!";

  potionsFound = 0;

  needsRedraw = true;
}

//======================================================
// Player Actions
//======================================================

void takePlayerTurn() {

  animationState = ANIM_STEP_FORWARD;

  performAttack(player, goblin);

  if (goblin.hp <= 0) {

    playSound(SoundEffect::VICTORY);

    potionsFound = random(0, 3);

    player.potions[POTION_HEALING] += potionsFound;

    battleMessage = "Enemy defeated!";

    waitingForVictory = true;
    victoryStart = millis();

} else {

    waitingForEnemyTurn = true;
    enemyTurnStart = millis();
}

  needsRedraw = true;
}

void useHealingPotion() {

  usePotion(player, POTION_HEALING);

  if (battleMessage != "No healing potions!") {

    waitingForEnemyTurn = true;
    enemyTurnStart = millis();
  }

  needsRedraw = true;
}

void defend() {

  player.tempAC = 2;

  battleMessage = "Tony defends! +2 AC";

  waitingForEnemyTurn = true;
  enemyTurnStart = millis();

  needsRedraw = true;
}

void runAway() {

  Serial.println("Run selected");

  battleMessage = "You run away!";

  waitingForTown = true;
  townStart = millis();

  needsRedraw = true;
}

//======================================================
// Enemy Turn
//======================================================

void takeEnemyTurn() {

  performAttack(goblin, player);

  player.tempAC = 0;

  if (player.hp <= 0) {

    battleState = PLAYER_LOSE;
    playSound(SoundEffect::GAME_OVER);

  } else {

    battleState = PLAYER_TURN;
  }

  needsRedraw = true;
}