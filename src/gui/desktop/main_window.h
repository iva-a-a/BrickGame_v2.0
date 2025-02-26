#pragma once

#include <QMainWindow>
#include <QPushButton>
#include <QVBoxLayout>

#include "snake_desktop.h"
#include "tetris_desktop.h"

namespace s21 {

/**
 * @class MainWindow
 * @brief главное окно приложения
 */
class MainWindow : public QMainWindow {
  Q_OBJECT
 public:
  /**
   * @brief Конструктор MainWindow
   */
  MainWindow();
  /**
   * @brief Деструктор MainWindow
   */
  ~MainWindow();

 private:
  /**
   * @brief настройка пользовательского интерфейса

   */
  void setup_ui();

  SnakeWidget *snake = nullptr; /**< Указатель на виджет "Змейка" */
  TetrisWidget *tetris = nullptr; /**< Указатель на виджет "Тетрис" */

  /**
   * @brief очистка памяти игры
   */
  void delete_game();

 private slots:
  /**
   * @brief обработка нажатия кнопки "Змейка"
   */
  void on_push_snake_clicked();
  /**
   * @brief обработка нажатия кнопки "Тетрис"
   */
  void on_push_tetris_clicked();
};
}  // namespace s21
