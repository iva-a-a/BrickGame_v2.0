#include "controller_snake.h"

int **Controller::convert_snake_to_array(std::list<Coordinate> snake) {
  int **arr = new int *[snake.size() + 1];
  size_t index = 0;
  for (auto &i : snake) {
    arr[index] = new int[3];
    arr[index][0] = i.x;
    arr[index][1] = i.y;
    arr[index][2] = 0;
    index++;
  }
  arr[index] = new int[3];
  arr[index][0] = -1;
  arr[index][1] = -1;
  arr[index][2] = -1;
  return arr;
}

int **Controller::convert_apple_to_array(Coordinate apple) {
  int **arr = new int *[2];
  size_t index = 0;

  arr[index] = new int[3];
  arr[index][0] = apple.x;
  arr[index][1] = apple.y;
  arr[index][2] = 7;
  index++;

  arr[index] = new int[3];
  arr[index][0] = -1;
  arr[index][1] = -1;
  arr[index][2] = -1;
  return arr;
}

void Controller::free_array(int **arr) {
  if (arr != nullptr) {
    size_t i = 0;
    while (arr[i][0] != -1 && arr[i][1] != -1 && arr[i][2] != -1) {
      delete[] arr[i];
      i++;
    }
    delete[] arr[i];
    delete[] arr;
  }
}

void Controller::userInput(UserAction_t currentAction, bool hold) {
  if (currentAction == Start && model.get_state() == Begin) {
    model.set_state(Generation);
  } else if (model.get_state() == Falling) {
    if (currentAction == Pause) {
      model.set_state(Break);
    } else if (currentAction == Left || currentAction == Right ||
               currentAction == Up || currentAction == Down) {
      model.set_state(Moving_rotate);
      model.set_currAction(currentAction);
    } else if (currentAction == Terminate) {
      model.set_state(End);
    }
  } else if (model.get_state() == Break) {
    if (currentAction == Pause) {
      model.set_state(Falling);
    } else if (currentAction == Terminate) {
      model.set_state(End);
    }
  } else if (model.get_state() == End) {
    if (currentAction == Start) {
      model.set_state(Begin);
    } else if (currentAction == Terminate) {
      model.set_state(Exit);
    }
  }
  if (hold) {
    model.move_snake();
  }
}

GameInfo_t Controller::updateCurrentState() {
  model.update();
  GameInfo_t info_snake;

  info_snake.score = model.get_score();
  info_snake.high_score = model.get_high_score();
  info_snake.speed = model.get_speed();
  info_snake.level = model.get_level();
  info_snake.pause = 0;

  info_snake.next = convert_snake_to_array(model.get_snake());
  info_snake.field = convert_apple_to_array(model.get_apple());
  return info_snake;
}

void Controller::clearGameInfo(GameInfo_t &info_snake) {
  free_array(info_snake.field);
  free_array(info_snake.next);
}

SnakeGame *Controller::get_model() { return &model; }