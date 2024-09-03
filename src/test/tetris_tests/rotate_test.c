#include "for_testing.h"

START_TEST(rotate_01) {
  Game_tetris *tetris = get_GameInfo();
  initial_info();

  tetris->now[0][0] = 1;
  tetris->now[0][1] = 1;
  tetris->now[1][0] = 1;
  tetris->now[1][1] = 1;
  tetris->number_now_f = 3;

  int **figure = memory_alloc(ROWS_FIGURE, COL_FIGURE);
  figure[0][0] = 1;
  figure[0][1] = 1;
  figure[1][0] = 1;
  figure[1][1] = 1;

  rotate_figure(tetris);
  ck_assert_int_eq(eq_mat(tetris->now, figure, ROWS_FIGURE, COL_FIGURE), true);

  rotate_figure(tetris);
  ck_assert_int_eq(eq_mat(tetris->now, figure, ROWS_FIGURE, COL_FIGURE), true);

  free_memory(figure, ROWS_FIGURE);
  free_info();
}
END_TEST

START_TEST(rotate_02) {
  Game_tetris *tetris = get_GameInfo();
  initial_info();

  tetris->now[0][1] = 1;
  tetris->now[1][0] = 1;
  tetris->now[1][1] = 1;
  tetris->now[1][2] = 1;
  tetris->number_now_f = 5;

  int **figure = memory_alloc(ROWS_FIGURE, COL_FIGURE);

  rotate_figure(tetris);
  figure[0][1] = 1;
  figure[1][1] = 1;
  figure[1][2] = 1;
  figure[2][1] = 1;
  ck_assert_int_eq(eq_mat(tetris->now, figure, ROWS_FIGURE, COL_FIGURE), true);

  rotate_figure(tetris);
  clear_mat(figure, ROWS_FIGURE, COL_FIGURE);
  figure[1][0] = 1;
  figure[1][1] = 1;
  figure[1][2] = 1;
  figure[2][1] = 1;
  ck_assert_int_eq(eq_mat(tetris->now, figure, ROWS_FIGURE, COL_FIGURE), true);

  rotate_figure(tetris);
  clear_mat(figure, ROWS_FIGURE, COL_FIGURE);
  figure[0][1] = 1;
  figure[1][0] = 1;
  figure[1][1] = 1;
  figure[2][1] = 1;
  ck_assert_int_eq(eq_mat(tetris->now, figure, ROWS_FIGURE, COL_FIGURE), true);

  free_memory(figure, ROWS_FIGURE);
  free_info();
}
END_TEST

START_TEST(rotate_03) {
  Game_tetris *tetris = get_GameInfo();
  initial_info();

  tetris->now[1][0] = 1;
  tetris->now[1][1] = 1;
  tetris->now[1][2] = 1;
  tetris->now[1][3] = 1;
  tetris->number_now_f = 0;

  int **figure = memory_alloc(ROWS_FIGURE, COL_FIGURE);

  rotate_figure(tetris);
  figure[0][2] = 1;
  figure[1][2] = 1;
  figure[2][2] = 1;
  figure[3][2] = 1;
  ck_assert_int_eq(eq_mat(tetris->now, figure, ROWS_FIGURE, COL_FIGURE), true);

  rotate_figure(tetris);
  clear_mat(figure, ROWS_FIGURE, COL_FIGURE);
  figure[2][0] = 1;
  figure[2][1] = 1;
  figure[2][2] = 1;
  figure[2][3] = 1;
  ck_assert_int_eq(eq_mat(tetris->now, figure, ROWS_FIGURE, COL_FIGURE), true);

  rotate_figure(tetris);
  clear_mat(figure, ROWS_FIGURE, COL_FIGURE);
  figure[0][1] = 1;
  figure[1][1] = 1;
  figure[2][1] = 1;
  figure[3][1] = 1;
  ck_assert_int_eq(eq_mat(tetris->now, figure, ROWS_FIGURE, COL_FIGURE), true);

  free_memory(figure, ROWS_FIGURE);
  free_info();
}
END_TEST

START_TEST(rotate_04) {
  Game_tetris *tetris = get_GameInfo();
  initial_info();

  tetris->now[0][0] = 1;
  tetris->now[1][0] = 1;
  tetris->now[1][1] = 1;
  tetris->now[1][2] = 1;
  tetris->number_now_f = 1;
  tetris->x = 0;
  tetris->y = 4;

  int **figure = memory_alloc(ROWS_FIGURE, COL_FIGURE);

  rotate_figure(tetris);
  figure[0][1] = 1;
  figure[0][2] = 1;
  figure[1][1] = 1;
  figure[2][1] = 1;
  ck_assert_int_eq(eq_mat(tetris->now, figure, ROWS_FIGURE, COL_FIGURE), true);

  move_figure(tetris, Left);
  rotate_figure(tetris);
  ck_assert_int_eq(eq_mat(tetris->now, figure, ROWS_FIGURE, COL_FIGURE), true);

  free_memory(figure, ROWS_FIGURE);
  free_info();
}
END_TEST

Suite *s21_rotate_test_suite(void) {
  Suite *suite = suite_create("s21_rotate_test");
  TCase *tcase_core = tcase_create("s21_rotate_test");

  tcase_add_test(tcase_core, rotate_01);
  tcase_add_test(tcase_core, rotate_02);
  tcase_add_test(tcase_core, rotate_03);
  tcase_add_test(tcase_core, rotate_04);

  suite_add_tcase(suite, tcase_core);

  return suite;
}