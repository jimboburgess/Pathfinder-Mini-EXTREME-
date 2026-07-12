#pragma once

enum AnimationState {

  ANIM_IDLE,
  ANIM_STEP_FORWARD,
  ANIM_SWING,
  ANIM_STEP_BACK

};

extern AnimationState animationState;

void updateBattleAnimation();