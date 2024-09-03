#include "tetrisTests_suite.h"

START_TEST(coll_01) {
  Game_tetris *tetris = get_GameInfo();
  initial_info();

  tetris->now[1][0] = 1;
  tetris->now[1][1] = 1;
  tetris->now[1][2] = 1;
  tetris->now[1][3] = 1;

  tetris->x = 2;
  tetris->y = 8;

  tetris->game_info.field[9][3] = 1;

  ck_assert_int_eq(collision(tetris), 2);
  free_info();
}
END_TEST

START_TEST(coll_02) {
  Game_tetris *tetris = get_GameInfo();
  initial_info();

  tetris->now[1][0] = 1;
  tetris->now[1][1] = 1;
  tetris->now[1][2] = 1;
  tetris->now[1][3] = 1;

  tetris->x = -1;
  tetris->y = 18;

  ck_assert_int_eq(collision(tetris), 1);
  free_info();
}
END_TEST

START_TEST(coll_03) {
  Game_tetris *tetris = get_GameInfo();
  initial_info();

  tetris->now[1][0] = 1;
  tetris->now[1][1] = 1;
  tetris->now[1][2] = 1;
  tetris->now[1][3] = 1;

  tetris->x = 2;
  tetris->y = 5;

  ck_assert_int_eq(collision(tetris), 0);
  free_info();
}
END_TEST

Suite *s21_coll_test_suite(void) {
  Suite *suite = suite_create("s21_coll_test");
  TCase *tcase_core = tcase_create("s21_coll_test");

  tcase_add_test(tcase_core, coll_01);
  tcase_add_test(tcase_core, coll_02);
  tcase_add_test(tcase_core, coll_03);

  suite_add_tcase(suite, tcase_core);

  return suite;
}