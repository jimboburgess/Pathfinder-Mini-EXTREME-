#pragma once

enum PotionType {
  POTION_HEALING,
  POTION_COUNT
};

enum EnemyType {

  NONE,
  GOBLIN_SPEARMAN,
  GOBLIN_ARCHER,
  GOBLIN_CHIEF

};


struct Character {

  const char* name;

  int hp;
  int maxHP;

  int armorClass;
  int tempAC;

  int attackBonus;

  int weaponSides;
  int damageBonus;

  int potions[POTION_COUNT];

  EnemyType enemyType;
};