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
  void print_snake(std::list<Coordinate> snake);
  void print_apple(Coordinate apple);
  void print_stats_snake(GameInfo_t gameInfo);

  void game_snake();
  void printCurrentState();
};
} // namespace s21
