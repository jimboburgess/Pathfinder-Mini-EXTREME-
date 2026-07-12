void usePotion(Character& character, PotionType type) {

  switch (type) {

    case POTION_HEALING:
      {

        if (character.potions[POTION_HEALING] <= 0) {

          battleMessage = "No healing potions!";
          return;
        }

        character.potions[POTION_HEALING]--;

        int healAmount = random(1, 9) + 1;  // 1d8+1

        character.hp += healAmount;

        if (character.hp > character.maxHP) {
          character.hp = character.maxHP;
        }

        playSound(SoundEffect::POTION);

        battleMessage =
          String(character.name) + " healed " + String(healAmount) + " HP!";

        break;
      }
  }
}