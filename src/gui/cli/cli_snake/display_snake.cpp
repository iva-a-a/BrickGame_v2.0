#include "display_snake.h"

using namespace s21;

SnakeDisplay::SnakeDisplay(Controller *c) : controller{c} {}

void SnakeDisplay::print_win() {
  mvprintw(9, 0, "%*c", 22, ' ');
  mvprintw(10, 0, "         YOU WIN        ");
  mvprintw(11, 0, "%*c", 22, ' ');
}

void SnakeDisplay::game_snake() {
  while (controller->get_model()->get_state() != Exit) {
    UserAction_t prev_key = controller->get_model()->get_currAction();
    UserAction_t key = input_key();
    controller->userInput(key, prev_key == key && key != None);
    GameInfo_t info = controller->updateCurrentState();
    printCurrentState(info);
    controller->clearGameInfo(info);
  }
}

void SnakeDisplay::printCurrentState(GameInfo_t &info) {
  GameState_t state = controller->get_model()->get_state();
  if (state == Begin) {
    print_start();
  } else if (state == End) {
    if (info.score == SCORE_WIN) {
      print_stats(info.level, info.speed, info.score, info.high_score, 500);
      print_win();
    } else {
      print_game_over();
    }
  } else {
    print_game_board();
    print_stats_ban();
    print_stats(info.level, info.speed, info.score, info.high_score, 500);
    print_arr(info.field);
    print_arr(info.next);
    if (state == Break) {
      print_pause();
    }
  }
  refresh();
}