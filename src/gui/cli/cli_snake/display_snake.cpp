#include "display_snake.h"

using namespace s21;

SnakeDisplay::SnakeDisplay(Controller *c) : controller{c} {}

void SnakeDisplay::print_arr(int **arr) {
  if (arr == nullptr) {
    return;
  }
  size_t i = 0;
  while (arr[i][0] != -1 && arr[i][1] != -1) {
    mvprintw(arr[i][0] + 1, arr[i][1] * 2 + 1, "[]");
    i++;
  }
}

void SnakeDisplay::print_win() {
  mvprintw(9, 0, "%*c", 22, ' ');
  mvprintw(10, 0, "         YOU WIN        ");
  mvprintw(11, 0, "%*c", 22, ' ');
}

void SnakeDisplay::print_stats_snake(int level, int speed, int score,
                                     int high_score) {
  mvprintw(6, 29, "%d", level);
  mvprintw(9, 29, "%.2f", (float)500 / speed);
  mvprintw(12, 29, "%d", score);
  mvprintw(15, 29, "%d", high_score);
}

void SnakeDisplay::game_snake() {
  while (controller->model->get_state() != Exit) {
    UserAction_t prev_key = controller->model->get_currAction();
    UserAction_t key = input_key();
    controller->userInput(key, prev_key == key && key != None);
    GameInfo_t info = controller->updateCurrentState();
    printCurrentState(info);
    controller->clearGameInfo(info);
  }
}

void SnakeDisplay::printCurrentState(GameInfo_t &info) {
  GameState_t state = controller->model->get_state();
  if (state == Begin) {
    print_start();
  } else if (state == End) {
    if (info.score == SCORE_WIN) {
      print_stats_snake(info.level, info.speed, info.score, info.high_score);
      print_win();
    } else {
      print_game_over();
    }
  } else {
    print_game_board();
    print_stats();
    print_stats_snake(info.level, info.speed, info.score, info.high_score);
    print_arr(info.field);
    print_arr(info.next);
    if (state == Break) {
      print_pause();
    }
  }
  refresh();
}