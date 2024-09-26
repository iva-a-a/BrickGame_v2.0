#include "tetrisTests_suite.h"

START_TEST(move_01) {
  Game_tetris *tetris = get_GameInfo();
  initial_info();

  tetris->now[0][0] = 1;
  tetris->now[0][1] = 1;
  tetris->now[1][0] = 1;
  tetris->now[1][1] = 1;
  tetris->x = 2;
  tetris->y = 7;

  move_figure(tetris, Left);
  ck_assert_int_eq(tetris->x, 1);
  move_figure(tetris, Left);
  ck_assert_int_eq(tetris->x, 0);
  move_figure(tetris, Left);
  ck_assert_int_eq(tetris->x, 0);
  free_info();
}
END_TEST

START_TEST(move_02) {
  Game_tetris *tetris = get_GameInfo();
  initial_info();
  tetris->game_info.field[15][7] = 1;
  tetris->game_info.field[16][7] = 1;
  tetris->game_info.field[17][7] = 1;
  tetris->game_info.field[18][7] = 1;
  tetris->game_info.field[19][7] = 1;

  tetris->now[0][0] = 1;
  tetris->now[0][1] = 1;
  tetris->now[1][0] = 1;
  tetris->now[1][1] = 1;
  tetris->x = 4;
  tetris->y = 15;

  move_figure(tetris, Right);
  ck_assert_int_eq(tetris->x, 5);
  move_figure(tetris, Right);
  ck_assert_int_eq(tetris->x, 5);
  free_info();
}
END_TEST

START_TEST(move_03) {
  Game_tetris *tetris = get_GameInfo();
  initial_info();
  tetris->game_info.field[5][2] = 1;
  tetris->game_info.field[5][3] = 1;
  tetris->game_info.field[5][4] = 1;
  tetris->game_info.field[5][5] = 1;
  tetris->game_info.field[5][6] = 1;

  tetris->now[0][0] = 1;
  tetris->now[0][1] = 1;
  tetris->now[1][0] = 1;
  tetris->now[1][1] = 1;
  tetris->x = 2;
  tetris->y = 2;

  move_figure(tetris, Down);
  ck_assert_int_eq(tetris->y, 3);
  move_figure(tetris, Right);
  ck_assert_int_eq(tetris->x, 3);
  move_figure(tetris, Right);
  ck_assert_int_eq(tetris->x, 4);
  move_figure(tetris, Right);
  ck_assert_int_eq(tetris->x, 5);
  move_figure(tetris, Right);
  ck_assert_int_eq(tetris->x, 6);
  move_figure(tetris, Right);
  ck_assert_int_eq(tetris->x, 7);
  move_figure(tetris, Down);
  ck_assert_int_eq(tetris->y, 18);
  free_info();
}
END_TEST

Suite *s21_move_test_suite(void) {
  Suite *suite = suite_create("s21_move_test");
  TCase *tcase_core = tcase_create("s21_move_test");

  tcase_add_test(tcase_core, move_01);
  tcase_add_test(tcase_core, move_02);
  tcase_add_test(tcase_core, move_03);

  suite_add_tcase(suite, tcase_core);

  return suite;
}