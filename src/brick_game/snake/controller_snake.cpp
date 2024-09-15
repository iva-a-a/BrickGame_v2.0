#include "controller_snake.h"

using namespace s21;

Controller::Controller(SnakeGame *model) : model{model} {}

void Controller::userInput(UserAction_t currentAction, bool hold) {
  SnakeGame &snake = SnakeGame::get_instance();
  hold = true;
  if (currentAction == Start && snake.get_state() == Begin && hold == true) {
    snake.set_state(Generation);
  } else if (snake.get_state() == Falling) {
    if (currentAction == Pause) {
      snake.set_state(Break);
    } else if (currentAction == Left || currentAction == Right ||
               currentAction == Down || currentAction == Up) {
      snake.set_state(Moving_rotate);
      snake.set_currAction(currentAction);

    } else if (currentAction == Terminate) {
      snake.set_state(End);
    }
  } else if (snake.get_state() == Break) {
    if (currentAction == Pause) {
      snake.set_state(Falling);
    } else if (currentAction == Terminate) {
      snake.set_state(End);
    }
  } else if (snake.get_state() == End) {
    if (currentAction == Start) {
      snake.set_state(Begin);
    } else if (currentAction == Terminate) {
      snake.set_state(Exit);
    }
  }
  // if (hold) {
  //   snake.move_snake();
  // }
}

GameInfo_t Controller::updateCurrentState() {
  SnakeGame &snake = SnakeGame::get_instance();
  bool hold = false;
  if (snake.get_state() == Begin) {
    snake.clearing_game();
  } else if (snake.get_state() == Generation) {
    snake.set_prev_time(time_in_millisec());
    snake.put_apple();
    snake.set_state(Falling);
  } else if (snake.get_state() == Falling) {
    snake.move_snake();
  } else if (snake.get_state() == Moving_rotate) {
    snake.change_direction(snake.get_currAction(), hold);
    snake.snake_head_new_pos();
    snake.set_state(Falling);
  } else if (snake.get_state() == Attaching) {
    snake.increase_level();
    snake.save_high_score();
    snake.set_state(Generation);
  }
  return snake.get_GameInfo();
}