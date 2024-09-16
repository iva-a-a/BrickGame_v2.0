#include "brick_game_cli.h"

int main() {
  setup_gui();
  int key = getch();

  while (key != 27) {
    print_game_setection();
    if (key == 't' || key == 'T') {
      setup_game();
      game_tetris();
      clear_screen();
    } else if (key == 's' || key == 'S') {
      s21::SnakeGame model{};
      s21::Controller controller{&model};
      s21::SnakeDisplay game{&controller};
      game.game_snake();
      clear_screen();
    }
    key = getch();
  }

  free_info();
  delete_gui();
  return 0;
}