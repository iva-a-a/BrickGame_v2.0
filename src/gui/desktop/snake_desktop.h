#pragma once

#include "../../brick_game/snake/controller_snake.h"
#include "desktop.h"
#include <QKeyEvent>
#include <QTimer>

namespace s21 {

class SnakeWidget : public CommonDraw {
  Q_OBJECT
public:
  explicit SnakeWidget(QMainWindow *parent);
  ~SnakeWidget();

  void draw_win(QPainter &p);

protected:
  void keyPressEvent(QKeyEvent *key) override;
  void paintEvent(QPaintEvent *event) override;

private:
  s21::Controller controller;
  QTimer *timer;

private slots:
  void update_display();
};

} // namespace s21