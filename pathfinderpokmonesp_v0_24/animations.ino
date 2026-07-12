//======================================
// Battle Animations
//======================================

#include "animations.h"

AnimationState animationState = ANIM_IDLE;
unsigned long animationStart = 0;


void updateBattleAnimation() {

  if (battleState == PLAYER_WIN || battleState == PLAYER_LOSE)
    return;

  switch (animationState) {

    case ANIM_IDLE:
      break;

    case ANIM_STEP_FORWARD:

  fighterX++;

  if (fighterX >= 30) {

    animationState = ANIM_SWING;
    animationStart = millis();
  }

  spritesNeedRedraw = true;

  break;

  case ANIM_SWING:

  // Hold the attack pose for 150 ms

  if (millis() - animationStart >= 150) {

    animationState = ANIM_STEP_BACK;
  }

  spritesNeedRedraw = true;

  break;

    case ANIM_STEP_BACK:

      fighterX--;

      if (fighterX <= 20) {

        fighterX = 20;
        animationState = ANIM_IDLE;
      }

      spritesNeedRedraw = true;

      break;
  }
}