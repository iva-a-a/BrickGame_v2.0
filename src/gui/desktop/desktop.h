#pragma once

#include <QMainWindow>
#include <QPainter>

#define SIZE_RECT 30

class CommonDraw : public QMainWindow {

public:
  explicit CommonDraw(QMainWindow *window) : QMainWindow{window} {};
  ~CommonDraw() = default;

  void setup_window();
  void setup_painter(QPainter &p);

  void draw_arr(int **arr, QPainter &p);

  void draw_board(QPainter &p);
  void draw_start(QPainter &p);
  void draw_pause(QPainter &p);
  void draw_gameover(QPainter &p);

  void draw_banner_stat(QPainter &p, int level, int speed, int score,
                        int h_score);
};
