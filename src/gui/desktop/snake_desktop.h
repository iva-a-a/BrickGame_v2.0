#pragma once

#include "../../brick_game/snake/controller_snake.h"

#define SIZE_RECT 30

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QKeyEvent>
#include <QMainWindow>
#include <QPainter>
#include <QTimer>

namespace s21 {

class SnakeWidget : public QMainWindow {
  Q_OBJECT
public:
  explicit SnakeWidget(QMainWindow *window = nullptr);
  ~SnakeWidget();

  void draw_apple(QPainter &p);
  void draw_snake(QPainter &p);
  void draw_field(QPainter &p);
  void draw_stat(QPainter &p);

protected:
  void keyPressEvent(QKeyEvent *key) override;
  void paintEvent(QPaintEvent *event) override;

private:
  s21::SnakeGame model;
  s21::Controller controller;
  QTimer *timer;
  QGraphicsScene *scene;

private slots:
  void update_display();
};

} // namespace s21