#pragma once

#include <QKeyEvent>
#include <QTimer>

#include "../../brick_game/tetris/back_tetris.h"
#include "../../brick_game/tetris/controller_tetris.h"
#include "desktop.h"

namespace s21 {

/**
 * @class TetrisWidget
 * @brief класс для отображения игры "Тетрис" на основе Qt
 */
class TetrisWidget : public CommonDraw {
  Q_OBJECT
 public:
  /**
   * @brief конструктор класса TetrisWidget
   * @param parent указатель на родительское окно QMainWindow
   */
  explicit TetrisWidget(QMainWindow *parent);
  /**
   * @brief деструктор класса TetrisWidget
   */
  ~TetrisWidget();

  /**
   * @brief вывод статистики для игры "Тетрис"
   * @param p ссылка на объект QPainter для рисования
   */
  void draw_stat_tetris(QPainter &p);

 protected:
  /**
   * @brief обработка нажатия клавиш
   * @param key указатель на объект QKeyEvent, содержащий информацию о нажатой
   * клавише
   */
  void keyPressEvent(QKeyEvent *key) override;
  /**
   * @brief обработка события перерисовки виджета
   * @param event указатель на объект QPaintEvent, содержащий информацию о
   * событии перерисовки
   */
  void paintEvent(QPaintEvent *event) override;

 private:
  QTimer *timer; /**< таймер для обновления состояния игры */
  Game_tetris _game; /**< объект игры "Тетрис" */

 private slots:
  /**
   * @brief обновление отображения состояния игры
   */
  void update_display();
};

}  // namespace s21