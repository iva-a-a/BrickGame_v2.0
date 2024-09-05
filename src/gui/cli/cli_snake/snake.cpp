#include "snake.h"

// int main() {
//   setup_gui();
//   game_snake();
//   delete_gui();
//   return 0;
// }

void s21::game_snake() {
  const SnakeGame &snake = SnakeGame::get_instance();
  while (snake.get_state() != Exit) {
    userInput(input_key(), false);
    updateCurrentState();
    printCurrentState();
  }
}

void s21::userInput(UserAction_t currentAction, bool hold) {
  SnakeGame &snake = SnakeGame::get_instance();
  hold = true;
  if (currentAction == Start && snake.get_state() == Begin && hold == true) {
    snake.set_state(Generation);
  } else if (snake.get_state() == Falling) {
    if (currentAction == Pause) {
      snake.set_state(Break);
    } else if (currentAction == Left || currentAction == Right /*||
               currentAction == Down */
               || currentAction == Up) {
      snake.set_state(Moving_rotate);
      snake.set_currAction(currentAction);

    } /*else if (currentAction == Terminate) {
      snake.set_state(End);
    }*/
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
}

GameInfo_t s21::updateCurrentState() {
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

void s21::printCurrentState() {
  SnakeGame &snake = SnakeGame::get_instance();
  if (snake.get_state() == Begin) {
    print_start();
  } else if (snake.get_state() == End) {
    if (snake.get_GameInfo().score == SCORE_WIN) {
      print_stats_snake(snake.get_GameInfo());
      print_win();
    } else {
      print_game_over();
    }
  } else {
    print_game_board();
    print_stats();
    print_stats_snake(snake.get_GameInfo());
    print_apple(snake.get_apple());
    print_snake(snake.get_snake());
    if (snake.get_state() == Break) {
      print_pause();
    }
  }
  refresh();
}
