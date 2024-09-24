#pragma once

#include <QMainWindow>
#include <QPainter>
#include <QWidget>

#define SIZE_RECT 30
namespace s21 {
class CommonDraw : public QWidget {

public:
  explicit CommonDraw(QMainWindow *w) : parent{w} {};
  ~CommonDraw() = default;

  void setup_window();
  void setup_painter(QPainter &p);

  void draw_arr(int **arr, QPainter &p, const QColor &color);

  void draw_board(QPainter &p);
  void draw_start(QPainter &p);
  void draw_pause(QPainter &p);
  void draw_gameover(QPainter &p);

  void draw_banner_stat(QPainter &p, int level, int speed, int score,
                        int h_score);

protected:
  QMainWindow *parent;
};
} // namespace s21
