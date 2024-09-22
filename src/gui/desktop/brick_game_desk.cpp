#include "brick_game_desk.h"

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);

  s21::SnakeWidget window;
  window.show();

  return app.exec();
}