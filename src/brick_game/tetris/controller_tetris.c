#include "controller_tetris.h"

void userInput(UserAction_t action, bool hold) {
  GameInfo_t *info = get_GameInfo();
  int *state = &info->pause;

  if (action == Start && *state == Begin) {
    *state = Generation;
  } else if (*state == Falling) {
    if (action == Pause) {
      *state = Break;
    } else if (action == Left && !hold) {
      *state = Moving_left;
    } else if (action == Right && !hold) {
      *state = Moving_right;
    } else if (action == Down) {
      *state = Moving_down;
    } else if (action == Action) {
      *state = Moving_rotate;
    } else if (action == Terminate) {
      *state = End;
    }
  } else if (*state == Break) {
    if (action == Pause) {
      *state = Falling;
    } else if (action == Terminate) {
      *state = End;
    }
  } else if (*state == End) {
    if (action == Start) {
      *state = Begin;
    } else if (action == Terminate) {
      *state = Exit;
    }
  }
}

GameInfo_t updateCurrentState() {
  GameInfo_t *info = get_GameInfo();
  return *info;
}