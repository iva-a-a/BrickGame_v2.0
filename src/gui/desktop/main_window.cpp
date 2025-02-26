#include "main_window.h"

using namespace s21;

MainWindow::MainWindow() { setup_ui(); }

MainWindow::~MainWindow() { delete_game(); }

void MainWindow::setup_ui() {
  setFixedSize(300, 100);
  QMainWindow::setWindowTitle("BRICK GAME V2.0");
  QWidget *centralWidget = new QWidget(this);
  setCentralWidget(centralWidget);

  QHBoxLayout *mainLayout = new QHBoxLayout(centralWidget);

  QPushButton *snakeButton = new QPushButton("SNAKE", this);
  QPushButton *tetrisButton = new QPushButton("TETRIS", this);

  snakeButton->setFixedSize(100, 50);
  tetrisButton->setFixedSize(100, 50);

  connect(snakeButton, &QPushButton::clicked, this,
          &MainWindow::on_push_snake_clicked);
  connect(tetrisButton, &QPushButton::clicked, this,
          &MainWindow::on_push_tetris_clicked);

  mainLayout->addWidget(snakeButton);
  mainLayout->addWidget(tetrisButton);

  mainLayout->setContentsMargins(0, 0, 0, 0);
  mainLayout->setSpacing(10);
}

void MainWindow::on_push_snake_clicked() {
  delete_game();
  SnakeWidget *snake = new SnakeWidget(this);
  snake->show();
  this->hide();
}

void MainWindow::on_push_tetris_clicked() {
  delete_game();
  TetrisWidget *tetris = new TetrisWidget(this);
  tetris->show();
  this->hide();
}

void MainWindow::delete_game() {
  if (snake) {
    delete snake;
  }
  if (tetris) {
    delete tetris;
  }
}