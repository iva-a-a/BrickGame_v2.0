#include <unistd.h>

#include "tetrisTests_suite.h"

START_TEST(fall_01) {
  Game_tetris *tetris = get_GameInfo();
  setup_game();
  copy_figures(tetris);
  tetris->state = Falling;

  tetris->prev_time -= 2000;
  fall_figure(tetris);

  ck_assert_int_eq(tetris->y, 1);
  ck_assert_int_eq(tetris->state, Falling);
  free_info();
}
END_TEST

START_TEST(fall_02) {
  Game_tetris *tetris = get_GameInfo();
  setup_game();
  copy_figures(tetris);
  tetris->state = Falling;

  for (int j = 0; j < COL_BOARD; j++) {
    tetris->game_info.field[4][j] = 1;
  }

  tetris->prev_time -= 2000;
  fall_figure(tetris);
  ck_assert_int_eq(tetris->y, 1);
  ck_assert_int_eq(tetris->state, Falling);

  tetris->prev_time -= 2000;
  fall_figure(tetris);
  ck_assert_int_eq(tetris->y, 2);
  ck_assert_int_eq(tetris->state, Falling);

  tetris->prev_time -= 2000;
  fall_figure(tetris);
  ck_assert_int_eq(tetris->y, 2);
  ck_assert_int_eq(tetris->state, Attaching);

  free_info();
}
END_TEST

Suite *s21_fall_test_suite(void) {
  Suite *suite = suite_create("s21_fall_test");
  TCase *tcase_core = tcase_create("s21_fall_test");

  tcase_add_test(tcase_core, fall_01);
  tcase_add_test(tcase_core, fall_02);

  suite_add_tcase(suite, tcase_core);

  return suite;
}