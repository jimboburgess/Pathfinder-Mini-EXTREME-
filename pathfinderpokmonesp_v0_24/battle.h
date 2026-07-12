#pragma once

enum BattleOption {
  OPTION_ATTACK,
  OPTION_POTION,
  OPTION_DEFEND,
  OPTION_RUN
};


extern BattleOption selectedOption;

const int NUM_BATTLE_OPTIONS = 4;

