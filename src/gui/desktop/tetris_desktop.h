#pragma once

#include "../../brick_game/tetris/back_tetris.h"
#include "../../brick_game/tetris/controller_tetris.h"
#include "desktop.h"
#include <QKeyEvent>
#include <QTimer>

namespace s21 {

class TetrisWidget : public CommonDraw {
  Q_OBJECT
public:
  explicit TetrisWidget(QMainWindow *parent);
  ~TetrisWidget();

  void draw_stat_tetris(QPainter &p);

protected:
  void keyPressEvent(QKeyEvent *key) override;
  void paintEvent(QPaintEvent *event) override;

private:
  QTimer *timer;
  Game_tetris _game;

private slots:
  void update_display();
};

} // namespace s21