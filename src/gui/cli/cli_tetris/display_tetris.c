#include "display_tetris.h"

void print_stats_tetris() {
  mvprintw(0, 27, "NEXT");
  mvprintw(20, 24, "SPACE - rotate");
}

void clear_next_figure() {
  for (int i = 0; i < ROWS_FIGURE - 1; i++) {
    for (int j = 0; j < COL_FIGURE; j++) {
      mvprintw(2 + i, 26 + j * 2 + 1, "  ");
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
    print_stats(info->level, info->speed, info->score, info->high_score);
    print_arr(info->field);
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
    update(&tetris);
    GameInfo_t info_tetris = updateCurrentState();
    printCurrentState(&info_tetris);
    free_gameinfo(&info_tetris);
  }
  free_info(&tetris);
}
