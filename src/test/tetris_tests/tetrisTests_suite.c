#include "tetrisTests_suite.h"

int main() {
  run_tests();
  return 0;
}

void run_testcase(Suite *testscase, int counter_testcase) {
  if (counter_testcase > 1) putchar('\n');
  printf("Test %d:\n", counter_testcase);

  SRunner *sr = srunner_create(testscase);
  srunner_set_fork_status(sr, CK_NOFORK);
  srunner_run_all(sr, CK_VERBOSE);  // изменить CK_ENV на CK_VERBOSE , для более
                                    // подробного вывода информации о тестах
  srunner_free(sr);
}
void run_tests() {
  int counter_testcase = 0;
  Suite *list_cases[] = {s21_move_test_suite(),   s21_rotate_test_suite(),
                         s21_other_test_suite(),  s21_fill_test_suite(),
                         s21_level_test_suite(),  s21_coll_test_suite(),
                         s21_hscore_test_suite(), s21_rem_sc_test_suite(),
                         s21_fall_test_suite(),   NULL};

  for (Suite **testcase = list_cases; *testcase; testcase++) {
    run_testcase(*testcase, ++counter_testcase);
  }
}
