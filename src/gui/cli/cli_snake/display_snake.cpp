#include "display_snake.h"

using namespace s21;

void s21::print_snake(std::list<Coordinate> snake) {
  for (auto &i : snake) {
    mvprintw(i.x + 1, i.y * 2 + 1, "[]");
  }
}

void s21::print_apple(Coordinate apple) {
  mvprintw(apple.x + 1, apple.y * 2 + 1, "[]");
}

void s21::print_win() {
  mvprintw(9, 0, "%*c", 22, ' ');
  mvprintw(10, 0, "         YOU WIN        ");
  mvprintw(11, 0, "%*c", 22, ' ');
}

void s21::print_stats_snake(GameInfo_t gameInfo) {
  mvprintw(6, 29, "%d", gameInfo.level);
  mvprintw(9, 29, "%.2f", (float)500 / gameInfo.speed);
  mvprintw(12, 29, "%d", gameInfo.score);
  mvprintw(15, 29, "%d", gameInfo.high_score);
}