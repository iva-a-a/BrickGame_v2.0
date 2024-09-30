#include "display_tetris.h"

void print_stats_tetris() {
  mvprintw(0, 27, "NEXT");
  mvprintw(20, 24, "SPACE - rotate");
}

void clear_next_figure() {
  for (int i = 0; i < ROWS_FIGURE - 1; i++) {
    for (int j = 0; j < COL_FIGURE; j++) {
      mvprintw(2 + i, 24 + j * 2 + 1, "  ");
    }
  }
}

void print_fallfigure(int **arr, int row, int col) {
  if (arr != NULL) {
    for (int i = 0; i < row; i++) {
      for (int j = 0; j < col; j++) {
        if (arr[i][j] != 0) {
          mvprintw(i + 1, j * 2 + 1, "[]");
        }
      }
    }
  }
}
void printCurrentState(GameInfo_t *info) {
  int *state = &info->pause;
  if (*state == Begin) {
    print_start();
  } else if (*state == End) {
    print_game_over();
  } else {
    print_game_board();
    print_stats_ban();
    print_stats_tetris();
    print_stats(info->level, info->speed, info->score, info->high_score, 1000);
    print_fallfigure(info->field, ROWS_BOARD, COL_BOARD);
    clear_next_figure();
    print_arr(info->next);
    if (*state == Break) {
      print_pause();
    }
  }
  refresh();
}

void game_tetris() {
  Game_tetris tetris;
  setup_game(&tetris);
  while (tetris.state != Exit) {
    GameInfo_t *info = get_GameInfo();
    info->pause = (int)tetris.state;
    userInput(input_key(), false);
    tetris.state = (GameState_t)info->pause;
    update_game(&tetris);
    GameInfo_t info_tetris = updateCurrentState();
    printCurrentState(&info_tetris);
    free_gameinfo(&info_tetris);
  }
  free_info(&tetris);
}
