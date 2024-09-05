#include "back_tetris.h"

#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>

Game_tetris *get_GameInfo() {
  static Game_tetris Info = {0};
  return &Info;
}

long long int time_in_millisec() {
  struct timeval tv;
  gettimeofday(&tv, NULL);
  return (((long long int)tv.tv_sec) * 1000) + (tv.tv_usec / 1000);
}

void setup_game() {
  srand(time(NULL));
  initial_info();
}

void initial_info() {
  Game_tetris *tetris = get_GameInfo();
  tetris->game_info.field = (int **)malloc(sizeof(int *) * ROWS_BOARD);
  for (int i = 0; i < ROWS_BOARD; i++) {
    tetris->game_info.field[i] = (int *)calloc(sizeof(int), COL_BOARD);
  }

  tetris->game_info.next = (int **)malloc(sizeof(int *) * ROWS_FIGURE);
  for (int i = 0; i < ROWS_FIGURE; i++) {
    tetris->game_info.next[i] = (int *)calloc(sizeof(int), COL_FIGURE);
  }

  FILE *highScore;
  highScore = fopen("highscore_tetris.txt", "r");
  if (highScore) {
    if (fscanf(highScore, "%d", &tetris->game_info.high_score) == 0) {
      tetris->game_info.high_score = 0;
    }
    fclose(highScore);
  }

  tetris->now = (int **)malloc(sizeof(int *) * ROWS_FIGURE);
  for (int i = 0; i < ROWS_FIGURE; i++) {
    tetris->now[i] = (int *)malloc(sizeof(int) * COL_FIGURE);
  }
  clearing_game();
}

void free_info() {
  Game_tetris *tetris = get_GameInfo();
  for (int i = 0; i < ROWS_BOARD; i++) {
    free(tetris->game_info.field[i]);
  }
  free(tetris->game_info.field);

  for (int i = 0; i < ROWS_FIGURE; i++) {
    free(tetris->game_info.next[i]);
  }
  free(tetris->game_info.next);

  for (int i = 0; i < ROWS_FIGURE; i++) {
    free(tetris->now[i]);
  }
  free(tetris->now);
}

void clearing_game() {
  Game_tetris *tetris = get_GameInfo();
  clear_mat(tetris->game_info.field, ROWS_BOARD, COL_BOARD);
  clear_mat(tetris->game_info.next, ROWS_FIGURE, COL_FIGURE);

  tetris->game_info.score = 0;
  tetris->game_info.level = 1;
  tetris->game_info.speed = 1000;
  tetris->game_info.pause = 0;

  clear_mat(tetris->now, ROWS_FIGURE, COL_FIGURE);

  tetris->x = COL_BOARD / 2 - COL_FIGURE / 2;
  tetris->y = 0;
  tetris->state = Begin;

  gen_rand_figure(tetris);
}

void gen_rand_figure(Game_tetris *tetris) {
  int figs[TETRIS_F][ROWS_FIGURE][COL_FIGURE] = FIGURES;
  int num = rand() % TETRIS_F;
  for (int i = 0; i < ROWS_FIGURE; i++) {
    for (int j = 0; j < COL_FIGURE; j++) {
      tetris->game_info.next[i][j] = figs[num][i][j];
    }
  }
  tetris->number_next_f = num;
}

void fall_figure(Game_tetris *tetris) {
  long long int time = time_in_millisec();
  if (time - tetris->prev_time > tetris->game_info.speed) {
    tetris->y++;
    if (collision(tetris) != 0) {
      tetris->y--;
      tetris->state = Attaching;
    }
    tetris->prev_time = time;
  }
}

void rotate_figure(Game_tetris *tetris) {
  if (tetris->number_now_f != 3) {
    int size;
    if (tetris->number_now_f == 0) {
      size = 4;
    } else {
      size = 3;
    }
    int tmp[size][size];
    for (int i = 0; i < size; i++) {
      for (int j = 0; j < size; j++) {
        tmp[j][i] = tetris->now[i][j];
      }
    }
    for (int i = 0; i < size; i++) {
      for (int j = 0; j < size; j++) {
        tetris->now[i][j] = tmp[i][size - j - 1];
      }
    }
    if (collision(tetris) != 0) {
      for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
          tetris->now[j][i] = tmp[i][j];
        }
      }
    }
  }
}

void move_figure(Game_tetris *tetris, UserAction_t key) {
  if (key == Left) { /*влево*/
    tetris->x--;
    if (collision(tetris) != 0) {
      tetris->x++;
    }
  } else if (key == Right) { /*вправо*/
    tetris->x++;
    if (collision(tetris) != 0) {
      tetris->x--;
    }
  } else if (key == Down) { /*вниз*/
    while (collision(tetris) == 0) {
      tetris->y++;
    }
    tetris->y--;
  }
}

void copy_figures(Game_tetris *tetris) {
  for (int i = 0; i < ROWS_FIGURE; i++) {
    for (int j = 0; j < COL_FIGURE; j++) {
      tetris->now[i][j] = tetris->game_info.next[i][j];
    }
  }
  tetris->number_now_f = tetris->number_next_f;
}

void filling_field(Game_tetris *tetris) {
  for (int i = 0; i < ROWS_FIGURE; i++) {
    for (int j = 0; j < COL_FIGURE; j++) {
      if (tetris->y + i >= 0 && tetris->x + j >= 0 && tetris->now[i][j] == 1) {
        tetris->game_info.field[tetris->y + i][tetris->x + j] = 1;
      }
    }
  }
}

int remove_row(Game_tetris *tetris) {
  int full_row = ROWS_BOARD - 1;
  int count = 0;
  for (int i = ROWS_BOARD - 1; i >= 0; i--) {
    bool is_full = true;
    for (int j = 0; j < COL_BOARD; j++) {
      if (tetris->game_info.field[i][j] == 0) {
        is_full = false;
      }
    }
    if (is_full == false) {
      full_row--;
    } else {
      count++;
      for (int k = full_row; k > 0; k--) {
        for (int j = 0; j < COL_BOARD; j++) {
          tetris->game_info.field[k][j] = tetris->game_info.field[k - 1][j];
          tetris->game_info.field[k - 1][j] = 0;
        }
      }
      i++;
    }
  }
  return count;
}

void scoring_points(Game_tetris *tetris, int count) {
  if (count == 1) {
    tetris->game_info.score += SCORE_1;
  } else if (count == 2) {
    tetris->game_info.score += SCORE_2;
  } else if (count == 3) {
    tetris->game_info.score += SCORE_3;
  } else if (count == 4) {
    tetris->game_info.score += SCORE_4;
  }
}

void increase_level(Game_tetris *tetris) {
  while (tetris->game_info.score >= tetris->game_info.level * LEVEL_NEXT &&
         tetris->game_info.level != MAX_LEVEL) {
    if (tetris->game_info.level < MAX_LEVEL) {
      tetris->game_info.level++;
      tetris->game_info.speed -= 100;
    }
  }
}

int collision(Game_tetris *tetris) {
  int is_col = 0;
  for (int i = 0; i < ROWS_FIGURE; i++) {
    for (int j = 0; j < COL_FIGURE; j++) {
      if (tetris->now[i][j] != 0) {
        int x = tetris->x + j, y = tetris->y + i;
        if (x < 0 || x >= COL_BOARD || y >= ROWS_BOARD || y < 0) {
          is_col = 1; /*касание с краями поля*/
        } else if (tetris->game_info.field[y][x] == 1) {
          is_col = 2; /*касание с фигурой на поле*/
        }
      }
    }
  }
  return is_col;
}

void save_high_score(Game_tetris *tetris) {
  if (tetris->game_info.score >= tetris->game_info.high_score) {
    tetris->game_info.high_score = tetris->game_info.score;
    FILE *highScore;
    highScore = fopen("highscore_tetris.txt", "w");
    if (highScore) {
      fprintf(highScore, "%d", tetris->game_info.high_score);
      fclose(highScore);
    }
  }
}

void clear_mat(int **matrix, int x, int y) {
  for (int i = 0; i < x; i++) {
    for (int j = 0; j < y; j++) {
      matrix[i][j] = 0;
    }
  }
}