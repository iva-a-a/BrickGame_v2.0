#include "tetrisTests_suite.h"

START_TEST(high_01) {
  Game_tetris *tetris = get_GameInfo();
  initial_info();

  ck_assert_int_eq(tetris->game_info.high_score, 0);
  FILE *highScore = fopen("highscore_tetris.txt", "r");
  ck_assert_ptr_nonnull(highScore);

  tetris->game_info.score += 600;
  save_high_score(tetris);
  ck_assert_ptr_nonnull(highScore);
  ck_assert_int_eq(tetris->game_info.high_score, 600);

  tetris->game_info.score += 100;
  save_high_score(tetris);
  ck_assert_ptr_nonnull(highScore);
  ck_assert_int_eq(tetris->game_info.high_score, 700);

  tetris->game_info.high_score = 1500;
  tetris->game_info.score += 100;
  save_high_score(tetris);
  ck_assert_ptr_nonnull(highScore);
  ck_assert_int_eq(tetris->game_info.high_score, 1500);

  fclose(highScore);
  ck_assert_int_eq(tetris->game_info.high_score, 1500);
  free_info();
}
END_TEST

Suite *s21_hscore_test_suite(void) {
  Suite *suite = suite_create("s21_hscore_test");
  TCase *tcase_core = tcase_create("s21_hscore_test");

  tcase_add_test(tcase_core, high_01);

  suite_add_tcase(suite, tcase_core);

  return suite;
}