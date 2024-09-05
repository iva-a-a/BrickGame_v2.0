#ifndef TESTS
#define TESTS

#include <check.h>
#include <stdio.h>
#include <stdlib.h>

#include "../brick_game/tetris/back_tetris.h"

void run_testcase(Suite *testscase, int counter_testcase);
void run_tests();

Suite *s21_move_test_suite(void);
Suite *s21_rotate_test_suite(void);
Suite *s21_other_test_suite(void);
Suite *s21_fill_test_suite(void);
Suite *s21_level_test_suite(void);
Suite *s21_coll_test_suite(void);
Suite *s21_hscore_test_suite(void);
Suite *s21_rem_sc_test_suite(void);
Suite *s21_fall_test_suite(void);

#endif
