#include "for_testing.h"

START_TEST(rem_sc_01) {
  Game_tetris *tetris = get_GameInfo();
  initial_info();
  for (int j = 0; j < COL_BOARD; j++) {
    tetris->game_info.field[19][j] = 1;
  }
  int **play_field = memory_alloc(ROWS_BOARD, COL_BOARD);

  int count = remove_row(tetris);
  ck_assert_int_eq(
      eq_mat(tetris->game_info.field, play_field, ROWS_BOARD, COL_BOARD), true);
  ck_assert_int_eq(count, 1);
  scoring_points(tetris, count);
  ck_assert_int_eq(tetris->game_info.score, SCORE_1);

  free_memory(play_field, ROWS_BOARD);
  free_info();
}
END_TEST

START_TEST(rem_sc_02) {
  Game_tetris *tetris = get_GameInfo();
  initial_info();
  for (int j = 0; j < COL_BOARD; j++) {
    tetris->game_info.field[19][j] = 1;
    tetris->game_info.field[18][j] = 1;
  }
  int **play_field = memory_alloc(ROWS_BOARD, COL_BOARD);

  int count = remove_row(tetris);
  ck_assert_int_eq(
      eq_mat(tetris->game_info.field, play_field, ROWS_BOARD, COL_BOARD), true);
  ck_assert_int_eq(count, 2);
  scoring_points(tetris, count);
  ck_assert_int_eq(tetris->game_info.score, SCORE_2);

  free_memory(play_field, ROWS_BOARD);
  free_info();
}
END_TEST

START_TEST(rem_sc_03) {
  Game_tetris *tetris = get_GameInfo();
  initial_info();
  for (int j = 0; j < COL_BOARD; j++) {
    tetris->game_info.field[19][j] = 1;
    tetris->game_info.field[18][j] = 1;
    tetris->game_info.field[17][j] = 1;
  }
  int **play_field = memory_alloc(ROWS_BOARD, COL_BOARD);

  int count = remove_row(tetris);
  ck_assert_int_eq(
      eq_mat(tetris->game_info.field, play_field, ROWS_BOARD, COL_BOARD), true);
  ck_assert_int_eq(count, 3);
  scoring_points(tetris, count);
  ck_assert_int_eq(tetris->game_info.score, SCORE_3);

  free_memory(play_field, ROWS_BOARD);
  free_info();
}
END_TEST

START_TEST(rem_sc_04) {
  Game_tetris *tetris = get_GameInfo();
  initial_info();
  for (int j = 0; j < COL_BOARD; j++) {
    tetris->game_info.field[19][j] = 1;
    tetris->game_info.field[18][j] = 1;
    tetris->game_info.field[17][j] = 1;
    tetris->game_info.field[16][j] = 1;
  }
  int **play_field = memory_alloc(ROWS_BOARD, COL_BOARD);

  int count = remove_row(tetris);
  ck_assert_int_eq(
      eq_mat(tetris->game_info.field, play_field, ROWS_BOARD, COL_BOARD), true);
  ck_assert_int_eq(count, 4);
  scoring_points(tetris, count);
  ck_assert_int_eq(tetris->game_info.score, SCORE_4);

  free_memory(play_field, ROWS_BOARD);
  free_info();
}
END_TEST

START_TEST(rem_sc_05) {
  Game_tetris *tetris = get_GameInfo();
  initial_info();
  tetris->game_info.score = 100;

  for (int j = 0; j < COL_BOARD - 3; j++) {
    tetris->game_info.field[19][j] = 1;
  }

  int **play_field = memory_alloc(ROWS_BOARD, COL_BOARD);
  for (int j = 0; j < COL_BOARD - 3; j++) {
    play_field[19][j] = 1;
  }

  int count = remove_row(tetris);
  ck_assert_int_eq(
      eq_mat(tetris->game_info.field, play_field, ROWS_BOARD, COL_BOARD), true);
  ck_assert_int_eq(count, 0);
  scoring_points(tetris, count);
  ck_assert_int_eq(tetris->game_info.score, 100);

  free_memory(play_field, ROWS_BOARD);
  free_info();
}
END_TEST

Suite *s21_rem_sc_test_suite(void) {
  Suite *suite = suite_create("s21_rem_sc_test");
  TCase *tcase_core = tcase_create("s21_rem_sc_test");

  tcase_add_test(tcase_core, rem_sc_01);
  tcase_add_test(tcase_core, rem_sc_02);
  tcase_add_test(tcase_core, rem_sc_03);
  tcase_add_test(tcase_core, rem_sc_04);
  tcase_add_test(tcase_core, rem_sc_05);

  suite_add_tcase(suite, tcase_core);

  return suite;
}