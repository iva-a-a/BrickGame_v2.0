#include "display_snake.h"

using namespace s21;

SnakeDisplay::SnakeDisplay(Controller *c) : controller{c} {}

void SnakeDisplay::print_snake(std::list<Coordinate> snake) {
  for (auto &i : snake) {
    mvprintw(i.x + 1, i.y * 2 + 1, "[]");
  }
}

void SnakeDisplay::print_apple(Coordinate apple) {
  mvprintw(apple.x + 1, apple.y * 2 + 1, "[]");
}

void SnakeDisplay::print_win() {
  mvprintw(9, 0, "%*c", 22, ' ');
  mvprintw(10, 0, "         YOU WIN        ");
  mvprintw(11, 0, "%*c", 22, ' ');
}

void SnakeDisplay::print_stats_snake(GameInfo_t gameInfo) {
  mvprintw(6, 29, "%d", gameInfo.level);
  mvprintw(9, 29, "%.2f", (float)500 / gameInfo.speed);
  mvprintw(12, 29, "%d", gameInfo.score);
  mvprintw(15, 29, "%d", gameInfo.high_score);
}

void SnakeDisplay::game_snake() {
  const SnakeGame &snake = SnakeGame::get_instance();
  while (snake.get_state() != Exit) {
    controller->userInput(input_key(), false);
    controller->updateCurrentState();
    printCurrentState();
  }
}
void SnakeDisplay::printCurrentState() {
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