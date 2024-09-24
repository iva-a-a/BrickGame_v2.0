#pragma once

#include "snake_desktop.h"
#include "tetris_desktop.h"

#include <QMainWindow>
#include <QPushButton>
#include <QVBoxLayout>

namespace s21 {
class MainWindow : public QMainWindow {
  Q_OBJECT
public:
  MainWindow();
  ~MainWindow();

private:
  void setup_ui();

  SnakeWidget *snake = nullptr;
  TetrisWidget *tetris = nullptr;
  void delete_game();

private slots:
  void on_push_snake_clicked();
  void on_push_tetris_clicked();
};
} // namespace s21
