#include "tetrisTests_suite.h"

START_TEST(level_01) {
  Game_tetris *tetris = get_GameInfo();
  initial_info();

  increase_level(tetris);
  ck_assert_int_eq(tetris->game_info.level, 1);
  ck_assert_int_eq(tetris->game_info.speed, 1000);

  tetris->game_info.score += 600;
  increase_level(tetris);
  ck_assert_int_eq(tetris->game_info.level, 2);
  ck_assert_int_eq(tetris->game_info.speed, 900);

  tetris->game_info.score += 1200;
  increase_level(tetris);
  ck_assert_int_eq(tetris->game_info.level, 4);
  ck_assert_int_eq(tetris->game_info.speed, 700);

  tetris->game_info.score += 100;
  increase_level(tetris);
  ck_assert_int_eq(tetris->game_info.level, 4);
  ck_assert_int_eq(tetris->game_info.speed, 700);

  tetris->game_info.score += 3500;
  increase_level(tetris);
  ck_assert_int_eq(tetris->game_info.level, 10);
  ck_assert_int_eq(tetris->game_info.speed, 100);

  tetris->game_info.score += 3000;
  increase_level(tetris);
  ck_assert_int_eq(tetris->game_info.level, 10);
  ck_assert_int_eq(tetris->game_info.speed, 100);

  free_info();
}
END_TEST

Suite *s21_level_test_suite(void) {
  Suite *suite = suite_create("s21_level_test");
  TCase *tcase_core = tcase_create("s21_level_test");

  tcase_add_test(tcase_core, level_01);

  suite_add_tcase(suite, tcase_core);

  return suite;
}