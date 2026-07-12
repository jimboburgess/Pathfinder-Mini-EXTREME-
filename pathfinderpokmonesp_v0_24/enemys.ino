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

