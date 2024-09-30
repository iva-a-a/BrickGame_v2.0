#include "back_tetris.h"

#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>

GameInfo_t *get_GameInfo() {
  static GameInfo_t Info;
  return &Info;
}

void setup_game(Game_tetris *tetris) {
  srand(time(NULL));
  initial_info(tetris);
}

void initial_info(Game_tetris *tetris) {
  tetris->field = (int **)malloc(sizeof(int *) * ROWS_BOARD);
  for (int i = 0; i < ROWS_BOARD; i++) {
    tetris->field[i] = (int *)calloc(sizeof(int), COL_BOARD);
  }

  tetris->next = (int **)malloc(sizeof(int *) * ROWS_FIGURE);
  for (int i = 0; i < ROWS_FIGURE; i++) {
    tetris->next[i] = (int *)calloc(sizeof(int), COL_FIGURE);
  }
  tetris->now = (int **)malloc(sizeof(int *) * ROWS_FIGURE);
  for (int i = 0; i < ROWS_FIGURE; i++) {
    tetris->now[i] = (int *)malloc(sizeof(int) * COL_FIGURE);
  }
  clearing_game(tetris);
  FILE *highScore;
  highScore = fopen("highscore_tetris.txt", "r");
  if (highScore) {
    if (fscanf(highScore, "%d", &tetris->high_score) == 0) {
      tetris->high_score = 0;
    }
    fclose(highScore);
  } else {
    tetris->high_score = 0;
    save_high_score(tetris);
  }
}

void free_info(Game_tetris *tetris) {
  if (tetris->field) {
    for (int i = 0; i < ROWS_BOARD; i++) {
      free(tetris->field[i]);
    }
    free(tetris->field);
  }
  if (tetris->next) {
    for (int i = 0; i < ROWS_FIGURE; i++) {
      free(tetris->next[i]);
    }
    free(tetris->next);
  }
  if (tetris->now) {
    for (int i = 0; i < ROWS_FIGURE; i++) {
      free(tetris->now[i]);
    }
    free(tetris->now);
  }
}

void clearing_game(Game_tetris *tetris) {
  clear_mat(tetris->field, ROWS_BOARD, COL_BOARD);
  clear_mat(tetris->next, ROWS_FIGURE, COL_FIGURE);

  tetris->score = 0;
  tetris->level = 1;
  tetris->speed = 1000;

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
      tetris->next[i][j] = figs[num][i][j];
    }
  }
  tetris->number_next_f = num;
}

void fall_figure(Game_tetris *tetris) {
  long long int time = time_in_millisec();
  if (time - tetris->prev_time > tetris->speed) {
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
      tetris->now[i][j] = tetris->next[i][j];
    }
  }
  tetris->number_now_f = tetris->number_next_f;
}

void filling_field(Game_tetris *tetris) {
  for (int i = 0; i < ROWS_FIGURE; i++) {
    for (int j = 0; j < COL_FIGURE; j++) {
      if (tetris->y + i >= 0 && tetris->x + j >= 0 && tetris->now[i][j] == 1) {
        tetris->field[tetris->y + i][tetris->x + j] = tetris->number_now_f + 1;
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
      if (tetris->field[i][j] == 0) {
        is_full = false;
      }
    }
    if (is_full == false) {
      full_row--;
    } else {
      count++;
      for (int k = full_row; k > 0; k--) {
        for (int j = 0; j < COL_BOARD; j++) {
          tetris->field[k][j] = tetris->field[k - 1][j];
          tetris->field[k - 1][j] = 0;
        }
      }
      i++;
    }
  }
  return count;
}

void scoring_points(Game_tetris *tetris, int count) {
  if (count == 1) {
    tetris->score += SCORE_1;
  } else if (count == 2) {
    tetris->score += SCORE_2;
  } else if (count == 3) {
    tetris->score += SCORE_3;
  } else if (count == 4) {
    tetris->score += SCORE_4;
  }
}

void increase_level(Game_tetris *tetris) {
  while (tetris->score >= tetris->level * LEVEL_NEXT &&
         tetris->level != MAX_LEVEL) {
    if (tetris->level < MAX_LEVEL) {
      tetris->level++;
      tetris->speed -= 100;
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
        } else if (tetris->field[y][x] != 0) {
          is_col = 2; /*касание с фигурой на поле*/
        }
      }
    }
  }
  return is_col;
}

void save_high_score(Game_tetris *tetris) {
  if (tetris->score >= tetris->high_score) {
    tetris->high_score = tetris->score;
    FILE *highScore;
    highScore = fopen("highscore_tetris.txt", "w");
    if (highScore) {
      fprintf(highScore, "%d", tetris->high_score);
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

void update_game(Game_tetris *tetris) {
  if (tetris->state == Begin) {
    clearing_game(tetris);
  } else if (tetris->state == Generation) {
    tetris->x = COL_BOARD / 2 - COL_FIGURE / 2;
    tetris->y = 0;
    tetris->prev_time = time_in_millisec();
    copy_figures(tetris);
    gen_rand_figure(tetris);
    if (collision(tetris) == 0) {
      tetris->state = Falling;
    } else {
      tetris->state = End;
    }
  } else if (tetris->state == Falling) {
    fall_figure(tetris);
  } else if (tetris->state == Moving_down) {
    move_figure(tetris, Down);
    tetris->state = Falling;
  } else if (tetris->state == Moving_left) {
    move_figure(tetris, Left);
    tetris->state = Falling;
  } else if (tetris->state == Moving_right) {
    move_figure(tetris, Right);
    tetris->state = Falling;
  } else if (tetris->state == Moving_rotate) {
    rotate_figure(tetris);
    tetris->state = Falling;
  } else if (tetris->state == Attaching) {
    filling_field(tetris);
    scoring_points(tetris, remove_row(tetris));
    increase_level(tetris);
    save_high_score(tetris);
    tetris->state = Generation;
  }

  GameInfo_t *info = get_GameInfo();
  if (info) {
    info->field = tetris->field;

    if (tetris->state != End) {
      int **t_now = convert_matrix(tetris->now, ROWS_FIGURE, COL_FIGURE,
                                   tetris->y, tetris->x);
      set_color_third_elem(t_now, tetris->number_now_f + 1);
      int **t_next =
          convert_matrix(tetris->next, ROWS_FIGURE, COL_FIGURE, 1, 12);
      set_color_third_elem(t_next, tetris->number_next_f + 1);

      info->next = join_matrix(t_next, t_now);
    } else {
      int **t_now = convert_matrix(tetris->now, ROWS_FIGURE, COL_FIGURE, 1, 12);
      set_color_third_elem(t_now, tetris->number_now_f + 1);
      info->next = t_now;
    }
    info->score = tetris->score;
    info->high_score = tetris->high_score;
    info->level = tetris->level;
    info->speed = tetris->speed;
  }
}

void set_color_third_elem(int **arr, int color) {
  int i = 0;
  while (arr[i][0] != -1 && arr[i][1] != -1 && arr[i][2] != -1) {
    arr[i][2] = color;
    i++;
  }
}

int **convert_matrix(int **arr1, int row, int col, int x, int y) {
  int count = 0;
  for (int i = 0; i < row; i++) {
    for (int j = 0; j < col; j++) {
      if (arr1[i][j] == 1) {
        count++;
      }
    }
  }
  int **mat = (int **)malloc((count + 1) * sizeof(int *));
  int k = 0;
  for (int i = 0; i < row; i++) {
    for (int j = 0; j < col; j++) {
      if (arr1[i][j] == 1) {
        mat[k] = (int *)malloc(3 * sizeof(int));
        mat[k][0] = i + x;
        mat[k][1] = j + y;
        mat[k][2] = 0;
        k++;
      }
    }
  }
  mat[k] = (int *)malloc(3 * sizeof(int));
  mat[k][0] = -1;
  mat[k][1] = -1;
  mat[k][2] = -1;
  return mat;
}

int **join_matrix(int **arr1, int **arr2) {
  int i = 0;
  int count = 0;
  while (arr1[i][0] != -1 && arr1[i][1] != -1 && arr1[i][2] != -1) {
    i++;
    count++;
  }
  i = 0;
  while (arr2[i][0] != -1 && arr2[i][1] != -1 && arr2[i][2] != -1) {
    i++;
    count++;
  }
  int **mat = (int **)malloc((count + 1) * sizeof(int *));
  i = 0;
  int j = 0;
  while (arr1[i][0] != -1 && arr1[i][1] != -1 && arr1[i][2] != -1) {
    mat[j] = arr1[i];
    i++;
    j++;
  }
  free(arr1[i]);
  i = 0;
  while (arr2[i][0] != -1 && arr2[i][1] != -1 && arr2[i][2] != -1) {
    mat[j] = arr2[i];
    i++;
    j++;
  }
  mat[j] = arr2[i];

  free(arr1);
  free(arr2);
  return mat;
}

void free_matrix(int **arr) {
  if (arr) {
    size_t i = 0;
    while (arr[i][0] != -1 && arr[i][1] != -1 && arr[i][2] != -1) {
      free(arr[i]);
      i++;
    }
    free(arr[i]);
    free(arr);
  }
}

void free_gameinfo(GameInfo_t *info) { free_matrix(info->next); }
