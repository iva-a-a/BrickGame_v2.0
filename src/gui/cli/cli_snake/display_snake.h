#pragma once

#include "../../../brick_game/snake/controller_snake.h"
#include "../display.h"

namespace s21 {
class SnakeDisplay {
private:
  Controller *controller;

public:
  SnakeDisplay(Controller *c);
  ~SnakeDisplay() = default;

  void print_win();

  void game_snake();
  void printCurrentState(GameInfo_t &info);
};
} // namespace s21
