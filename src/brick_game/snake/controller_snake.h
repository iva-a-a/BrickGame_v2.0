#pragma once

#include "model_snake.h"

namespace s21 {

class Controller {
private:
  SnakeGame model;

public:
  Controller() = default;
  ~Controller() = default;

  int **convert_snake_to_array(std::list<Coordinate> snake);
  int **convert_apple_to_array(Coordinate apple);
  void free_array(int **array);

  void userInput(UserAction_t currentAction, bool hold);
  GameInfo_t updateCurrentState();
  void clearGameInfo(GameInfo_t &info_snake);

  SnakeGame *get_model();
};
} // namespace s21