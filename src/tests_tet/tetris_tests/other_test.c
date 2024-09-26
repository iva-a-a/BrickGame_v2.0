#include "for_testing.h"

START_TEST(clear_mat_01) {
  Game_tetris *tetris = get_GameInfo();
  initial_info();

  tetris->now[0][0] = 1;
  tetris->now[0][1] = 1;
  tetris->now[1][0] = 1;
  tetris->now[1][1] = 1;

  int **figure = memory_alloc(ROWS_FIGURE, COL_FIGURE);
  clear_mat(tetris->now, ROWS_FIGURE, COL_FIGURE);
  ck_assert_int_eq(eq_mat(tetris->now, figure, ROWS_FIGURE, COL_FIGURE), true);
  free_memory(figure, ROWS_FIGURE);
  free_info();
}
END_TEST

START_TEST(copy_figure_02) {
  Game_tetris *tetris = get_GameInfo();
  initial_info();

  tetris->now[0][0] = 1;
  tetris->now[0][1] = 1;
  tetris->now[1][0] = 1;
  tetris->now[1][1] = 1;

  copy_figures(tetris);
  ck_assert_int_eq(
      eq_mat(tetris->now, tetris->game_info.next, ROWS_FIGURE, COL_FIGURE),
      true);
  ck_assert_int_eq(tetris->number_now_f, tetris->number_next_f);
  free_info();
}
END_TEST

START_TEST(setup_03) {
  Game_tetris *tetris = get_GameInfo();
  FILE *highScore;
  highScore = fopen("highscore_tetris.txt", "w");
  if (highScore) {
    fprintf(highScore, "invalid_data");
    fclose(highScore);
  }
  setup_game();

  int **play_field = memory_alloc(ROWS_BOARD, COL_BOARD);
  int **now_f = memory_alloc(ROWS_FIGURE, COL_FIGURE);

  ck_assert_ptr_nonnull(tetris->game_info.field);
  for (int i = 0; i < ROWS_BOARD; i++) {
    ck_assert_ptr_nonnull(tetris->game_info.field[i]);
  }

  ck_assert_ptr_nonnull(tetris->game_info.next);
  for (int i = 0; i < ROWS_FIGURE; i++) {
    ck_assert_ptr_nonnull(tetris->game_info.next[i]);
  }

  ck_assert_ptr_nonnull(tetris->now);
  for (int i = 0; i < ROWS_FIGURE; i++) {
    ck_assert_ptr_nonnull(tetris->now[i]);
  }

  ck_assert_int_eq(tetris->game_info.score, 0);
  ck_assert_int_eq(tetris->game_info.level, 1);
  ck_assert_int_eq(tetris->game_info.speed, 1000);
  ck_assert_int_eq(tetris->game_info.pause, 0);

  ck_assert_int_eq(tetris->x, COL_BOARD / 2 - COL_FIGURE / 2);
  ck_assert_int_eq(tetris->y, 0);
  ck_assert_int_eq(tetris->state, Begin);

  ck_assert_int_eq(
      eq_mat(tetris->game_info.field, play_field, ROWS_BOARD, COL_BOARD), true);
  ck_assert_int_eq(eq_mat(tetris->now, now_f, ROWS_FIGURE, COL_FIGURE), true);

  free_memory(play_field, ROWS_BOARD);
  free_memory(now_f, ROWS_FIGURE);

  free_info();
}
END_TEST

Suite *s21_other_test_suite(void) {
  Suite *suite = suite_create("s21_other_test");
  TCase *tcase_core = tcase_create("s21_other_test");

  tcase_add_test(tcase_core, clear_mat_01);
  tcase_add_test(tcase_core, copy_figure_02);
  tcase_add_test(tcase_core, setup_03);

  suite_add_tcase(suite, tcase_core);

  return suite;
}