HERE ARE FILES FOR CREATING A SIMPLE PATHFINDER BASED GAME.

IT RUNS ON AN ESP32-S3-ZERO ON A 240 X 240 TFT SCREEN.

AS ON 7/6/20206 IT IS PROGRAMMED TO RUN ON two BUTTONS, and an ec11 encoder

<img width="1691" height="1221" alt="image" src="https://github.com/user-attachments/assets/631afe45-fe55-441c-944a-fd2711bef958" />


<img width="1074" height="858" alt="20260707_221149 1" src="https://github.com/user-attachments/assets/31d963bd-8dd0-4ebd-9a4b-a91b735b7db3" />



The eventual plan is to have a small RPG.

Character select
  
  Fighter
  
  Arcane Spell caster
  
  Rogue
  
  Cleric

Town
  Home, for rest
  
  Ye olde shoppe, for selling a buying gear and potions
  
  Castle, for accepting simple quests such as kill 10 goblins, find 200ft of rope, etc. 
  
  Barn, for chicken looking or horse peepin.
  
  perhaps othr characters to talk with.

Dungeons

  using the five room dungeon technique
  https://donjon.bin.sh/fantasy/5_room/

  
  Entrance and Guardian: An initial challenge or obstacle that establishes the dungeon's theme and keeps casual looters out.
  
  Puzzle or Roleplaying Challenge: A mental or social trial that provides a change of pace from straight combat.
  
  Trick or Setback: A trap, red herring, or unexpected complication designed to build tension.
  
  Climax, Big Battle, or Conflict: The major boss fight or final confrontation of the adventure.
  
  Reward, Revelation, or Plot Twist: The resolution, where the players receive their loot, discover a secret.

  Eventually, One player can join with other players to complete dungeons. using ESP NOW connections.

  
Add more type of enemies

goblins

oozes

undead skeleton, necromancer, spirits

demons/devils

elementals or giants

classic beasts i.e. owlbear

dragons





  
  main.ino
│
├── setup()
├── loop()


buttons.ino

├── handleButtons()

├── handleStartButtons()

├── handleBattleButtons()

└── handleEndScreenButtons()


│
battle.ino
│
├── performAttack()


├── takePlayerTurn()


├── takeEnemyTurn()


├── useHealingPotion()


├── defend()


├── runAway()


└── resetBattle()


│
display.ino
│


├── drawStartScreen()


├── drawStartAnimation()


├── drawBattleScreen()


├── drawBattleSprites()


└── drawCriticalHit()


│
enemies.ino
│


└── generateGoblin()
│


potions.ino
│


└── usePotion()
│


sprites.cpp


sprites.h


characters.h


battle.h

