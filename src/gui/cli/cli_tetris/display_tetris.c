#include "display_tetris.h"

void print_stats_tetris(Game_tetris *info) {
  mvprintw(0, 27, "NEXT");
  mvprintw(20, 24, "SPACE - rotate");

  mvprintw(6, 29, "%d", info->game_info.level);
  mvprintw(9, 29, "%.2f", (float)1000 / info->game_info.speed);
  mvprintw(12, 29, "%d", info->game_info.score);
  mvprintw(15, 29, "%d", info->game_info.high_score);
}

void print_fall_figure(Game_tetris *tetris) {
  for (int i = 0; i < ROWS_BOARD; i++) {
    for (int j = 0; j < COL_BOARD; j++) {
      if (tetris->game_info.field[i][j] == 1) {
        mvprintw(i + 1, j * 2 + 1, "[]");
      }
    }
  }
}

void print_now_figure(Game_tetris *tetris) {
  for (int i = 0; i < ROWS_FIGURE; i++) {
    for (int j = 0; j < COL_FIGURE; j++) {
      if (tetris->now[i][j] == 1) {
        mvprintw(tetris->y + i + 1, (tetris->x + j) * 2 + 1, "[]");
      }
    }
  }
}

void print_next_figure(Game_tetris *tetris) {
  for (int i = 0; i < ROWS_FIGURE - 1; i++) {
    for (int j = 0; j < COL_FIGURE; j++) {
      if (tetris->game_info.next[i][j] == 1) {
        mvprintw(2 + i, 28 + j * 2 + 1, "[]");
      } else {
        mvprintw(2 + i, 28 + j * 2 + 1, "  ");
      }
    }
  }
}