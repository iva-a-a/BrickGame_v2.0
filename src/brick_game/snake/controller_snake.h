#pragma once

#include "model_snake.h"

namespace s21 {

class Controller {

public:
  SnakeGame *model;
  Controller(SnakeGame *model);
  ~Controller() = default;

  void userInput(UserAction_t currentAction, bool hold);
  GameInfo_t updateCurrentState();
};
} // namespace s21