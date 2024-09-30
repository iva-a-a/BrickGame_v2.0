#include "snake_desktop.h"

using namespace s21;

SnakeWidget::SnakeWidget(QMainWindow *parent)
    : CommonDraw(parent), controller{} {
  QWidget::setWindowTitle("Snake");
  setup_window();
  timer = new QTimer();
  connect(timer, &QTimer::timeout, this, &SnakeWidget::update_display);
  timer->start(30);
}

SnakeWidget::~SnakeWidget() { delete timer; }

void SnakeWidget::draw_win(QPainter &p) {
  p.drawText(SIZE_RECT * 10 + 5, SIZE_RECT * 10 + 25, "YOU WIN!");
}

void SnakeWidget::paintEvent(QPaintEvent *event) {
  Q_UNUSED(event)
  QPainter p(this);
  setup_painter(p);

  GameInfo_t info = controller.updateCurrentState();
  GameState_t state = controller.get_model()->get_state();
  if (state != Begin) {
    draw_board(p);
    draw_arr(info.field, p);
    draw_arr(info.next, p);
    draw_banner_stat(p, info.level, info.speed, info.score, info.high_score,
                     500);
  }
  if (state == Begin) {
    draw_start(p);
  } else if (state == End) {
    if (info.score == SCORE_WIN) {
      draw_win(p);
    } else {
      draw_gameover(p);
    }
  } else if (state == Break) {
    draw_pause(p);
  }
}

void SnakeWidget::keyPressEvent(QKeyEvent *key) {
  UserAction_t prev_key = controller.get_model()->get_currAction();
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
  controller.userInput(act, act == prev_key && act != None);
  update_display();
  if (controller.get_model()->get_state() == Exit) {
    this->close();
    parent->show();
  }
}

void SnakeWidget::update_display() { update(); }
