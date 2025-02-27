#pragma once

#include <QKeyEvent>
#include <QTimer>

#include "../../brick_game/snake/controller_snake.h"
#include "desktop.h"

/**
 * @class SnakeWidget
 * @brief класс для отображения игры "Змейка" на основе Qt
 */
class SnakeWidget : public CommonDraw {
  Q_OBJECT
 public:
  /**
   * @brief конструктор класса SnakeWidget
   * @param parent указатель на родительское окно типа QMainWindow
   */
  explicit SnakeWidget(QMainWindow *parent);
  /**
   * @brief деструктор класса SnakeWidget
   */
  ~SnakeWidget();

  /**
   * @brief отрисовка состояния "Победа"
   * @param p ссылка на объект QPainter для рисования
   */
  void draw_win(QPainter &p);

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
  Controller controller; /**< контроллер игры "Змейка"*/
  QTimer *timer;         /**< таймер для обновления состояния игры */

 private slots:
  /**
   * @brief обновление отображения состояния игры
   */
  void update_display();
};