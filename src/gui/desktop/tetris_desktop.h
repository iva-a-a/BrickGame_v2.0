#pragma once

#include "../../brick_game/tetris/controller_tetris.h"
#include "desktop.h"
#include <QGraphicsView>
#include <QKeyEvent>

#include <QTimer>

namespace s21 {

class TetrisWidget : public CommonDraw {
  Q_OBJECT
public:
  explicit TetrisWidget(QWidget *window = nullptr);
  ~TetrisWidget();

  void draw_stat_tetris(QPainter &p);

protected:
  void keyPressEvent(QKeyEvent *key) override;
  void paintEvent(QPaintEvent *event) override;

private:
  QTimer *timer;

private slots:
  void update_display();
};

} // namespace s21