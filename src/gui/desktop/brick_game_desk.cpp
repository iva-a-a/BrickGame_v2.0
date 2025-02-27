#include "brick_game_desk.h"

/**
 * @brief основная функция программы для десктопного интерфейса
 *
 * @param argc количество аргументов командной строки
 * @param argv массив аргументов командной строки
 * @return код завершения программы
 */
int main(int argc, char *argv[]) {
  QApplication app(argc, argv);

  MainWindow window;
  window.show();

  return app.exec();
}