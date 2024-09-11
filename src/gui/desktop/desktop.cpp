#include "snake_desktop.h"
#include <QApplication>
// #include <QLabel>

// #include <QPushButton>

// #include <QVBoxLayout>
// #include <QWidget>

// int main(int argc, char *argv[]) {
//   QApplication app(argc, argv);
//   // Создаем основное окно
//   QWidget window;
//   window.setWindowTitle("BRICK GAME V2.0");

//   // Создаем виджеты
//   QLabel *label = new QLabel("Game:");
//   QPushButton *b_quit = new QPushButton("Quit");
//   QPushButton *b_snake = new QPushButton("Snake");
//   QPushButton *b_tetris = new QPushButton("Tetris");
//   // Устанавливаем соединение для кнопки
//   QObject::connect(b_quit, &QPushButton::clicked, &app, &QApplication::quit);

//   QObject::connect(b_snake, &QPushButton::clicked, &app,
//   &QApplication::quit); QObject::connect(b_tetris, &QPushButton::clicked,
//   &app, &QApplication::quit);

//   // Создаем расположение и добавляем виджеты
//   QVBoxLayout *layout = new QVBoxLayout;
//   layout->addWidget(label);

//   layout->addWidget(b_snake);
//   layout->addWidget(b_tetris);
//   layout->addWidget(b_quit);

//   // Устанавливаем расположение в главное окно
//   window.setLayout(layout);

//   // Отображаем главное окно
//   window.resize(250, 100);
//   window.show();
//   // delete label;
//   // delete b_quit;
//   // delete b_snake;
//   // delete b_tetris;

//   return app.exec();
// }

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);

  s21::SnakeWidget window;
  window.show();

  return app.exec();
}