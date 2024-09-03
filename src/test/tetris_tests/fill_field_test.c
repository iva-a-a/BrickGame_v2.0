#include "for_testing.h"

START_TEST(fill_01) {
  Game_tetris *tetris = get_GameInfo();
  initial_info();

  tetris->now[0][0] = 1;
  tetris->now[0][1] = 1;
  tetris->now[1][0] = 1;
  tetris->now[1][1] = 1;
  tetris->x = 5;
  tetris->y = 2;

  int **play_field = memory_alloc(ROWS_BOARD, COL_BOARD);

  filling_field(tetris);
  play_field[2][5] = 1;
  play_field[2][6] = 1;
  play_field[3][5] = 1;
  play_field[3][6] = 1;

  ck_assert_int_eq(
      eq_mat(tetris->game_info.field, play_field, ROWS_BOARD, COL_BOARD), true);
  free_memory(play_field, ROWS_BOARD);
  free_info();
}
END_TEST

Suite *s21_fill_test_suite(void) {
  Suite *suite = suite_create("s21_fill_test");
  TCase *tcase_core = tcase_create("s21_fill_test");

  tcase_add_test(tcase_core, fill_01);

  suite_add_tcase(suite, tcase_core);

  return suite;
}