#include "tetris_desktop.h"

using namespace s21;
TetrisWidget::TetrisWidget(QMainWindow *parent) : CommonDraw(parent) {
  setup_game(&_game);
  QWidget::setWindowTitle("Tetris");
  setup_window();
  timer = new QTimer();
  connect(timer, &QTimer::timeout, this, &TetrisWidget::update_display);
  timer->start(30);
}

TetrisWidget::~TetrisWidget() { delete timer; }

void TetrisWidget::draw_stat_tetris(QPainter &p) {
  p.drawText(SIZE_RECT * 10 + 5, SIZE_RECT * 18 + 25, "SPACE - move");
  p.drawText(SIZE_RECT * 10 + 5, SIZE_RECT, "Next:");
}

void TetrisWidget::keyPressEvent(QKeyEvent *key) {
  UserAction_t act = None;
  if (key->key() == Qt::Key_Down) {
    act = Down;
  } else if (key->key() == Qt::Key_Up) {
    act = Up;
  } else if (key->key() == Qt::Key_Left) {
    act = Left;
  } else if (key->key() == Qt::Key_Right) {
    act = Right;
  } else if (key->key() == Qt::Key_Enter || key->key() == Qt::Key_Return) {
    act = Start;
  } else if (key->key() == Qt::Key_Escape) {
    act = Terminate;
  } else if (key->key() == Qt::Key_Backspace) {
    act = Pause;
  } else {
    act = Action;
  }

  GameInfo_t *info = get_GameInfo();
  info->pause = (int)_game.state;
  userInput(act, false);
  _game.state = (GameState_t)info->pause;
  if (_game.state == Exit) {
    this->close();
    parent->show();
  }
}

void TetrisWidget::paintEvent(QPaintEvent *event) {
  Q_UNUSED(event)
  QPainter p(this);
  setup_painter(p);
  update_game(&_game);
  GameInfo_t info = updateCurrentState();
  GameState_t state = _game.state;

  if (state != Begin) {
    draw_board(p);
    draw_arr(info.field, p, Qt::black);
    draw_arr(info.next, p, Qt::black);
    draw_banner_stat(p, info.level, info.speed, info.score, info.high_score);
    draw_stat_tetris(p);
  }
  if (state == Begin) {
    draw_start(p);
  } else if (state == End) {
    draw_gameover(p);
  } else if (state == Break) {
    draw_pause(p);
  }
  free_gameinfo(&info);
}

void TetrisWidget::update_display() { update(); }
