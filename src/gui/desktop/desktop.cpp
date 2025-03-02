#include "desktop.h"

#include <iomanip>
#include <sstream>
#include <string>

using namespace s21;

void CommonDraw::setup_window() {
  setFixedSize(SIZE_RECT * 10 + 200, SIZE_RECT * 20 + 10);
  setFocusPolicy(Qt::StrongFocus);
}

void CommonDraw::setup_painter(QPainter &p) {
  QFont font;
  font.setPointSize(14);
  p.setFont(font);
}

QColor CommonDraw::get_color(int c) {
  switch (c) {
    case 1:
      return QColor(Qt::cyan);
    case 2:
      return QColor(Qt::blue);
    case 3:
      return QColor(255, 165, 0);
    case 4:
      return QColor(Qt::yellow);
    case 5:
      return QColor(Qt::green);
    case 6:
      return QColor(128, 0, 128);
    case 7:
      return QColor(Qt::red);
    default:
      return QColor(Qt::black);
  }
}

void CommonDraw::draw_arr(int **arr, QPainter &p) {
  if (arr != nullptr) {
    size_t i = 0;
    while (arr[i][0] != -1 && arr[i][1] != -1 && arr[i][2] != -1) {
      QColor color = get_color(arr[i][2]);
      p.fillRect(arr[i][1] * SIZE_RECT, arr[i][0] * SIZE_RECT, SIZE_RECT,
                 SIZE_RECT, QBrush(color));
      p.drawRect(arr[i][1] * SIZE_RECT, arr[i][0] * SIZE_RECT, SIZE_RECT,
                 SIZE_RECT);
      i++;
    }
  }
}

void CommonDraw::draw_board(QPainter &p) {
  for (int x = 0; x < SIZE_RECT * 10; x += SIZE_RECT) {
    for (int y = 0; y < SIZE_RECT * 20; y += SIZE_RECT) {
      p.drawRect(x, y, SIZE_RECT, SIZE_RECT);
    }
  }
}

void CommonDraw::draw_start(QPainter &p) {
  p.drawText(rect(), Qt::AlignCenter, "Press ENTER to Start");
}

void CommonDraw::draw_pause(QPainter &p) {
  p.drawText(SIZE_RECT * 10 + 5, SIZE_RECT * 10 + 25, "PAUSE");
}
void CommonDraw::draw_gameover(QPainter &p) {
  p.drawText(SIZE_RECT * 10 + 5, SIZE_RECT * 10 + 25, "GAME OVER!");
  p.drawText(SIZE_RECT * 10 + 5, SIZE_RECT * 19 + 25, "ENTER - restart");
}

void CommonDraw::draw_banner_stat(QPainter &p, int level, int speed, int score,
                                  int h_score, int begin_speed) {
  std::string l = "Level: " + std::to_string(level);
  p.drawText(SIZE_RECT * 10 + 5, SIZE_RECT * 4 + 25, l.data());

  float speedSn = (float)begin_speed / speed;
  std::ostringstream oss;
  oss << std::fixed << std::setprecision(2) << speedSn;
  std::string sp = "Speed: " + oss.str();
  p.drawText(SIZE_RECT * 10 + 5, SIZE_RECT * 5 + 25, sp.data());

  std::string s = "Score: " + std::to_string(score);
  p.drawText(SIZE_RECT * 10 + 5, SIZE_RECT * 6 + 25, s.data());

  std::string hs = "High score: " + std::to_string(h_score);
  p.drawText(SIZE_RECT * 10 + 5, SIZE_RECT * 7 + 25, hs.data());

  p.drawText(SIZE_RECT * 10 + 5, SIZE_RECT * 14 + 25, "     Press:");
  p.drawText(SIZE_RECT * 10 + 5, SIZE_RECT * 15 + 25, "ESC - exit");
  p.drawText(SIZE_RECT * 10 + 5, SIZE_RECT * 16 + 25, "BACKSPACE - pause");
  p.drawText(SIZE_RECT * 10 + 5, SIZE_RECT * 17 + 25, "ARROWS - move");
}