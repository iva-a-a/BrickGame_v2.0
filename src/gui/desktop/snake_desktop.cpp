#include "snake_desktop.h"

using namespace s21;

SnakeWidget::SnakeWidget(QMainWindow *window) : QMainWindow{window}, game{} {
  printf("SnakeWidget");
  setFixedSize(470, 605);
  setFocusPolicy(Qt::StrongFocus);
  setWindowTitle("Snake");
  scene = new QGraphicsScene(this);
  timer = new QTimer;
  connect(timer, &QTimer::timeout, this, &SnakeWidget::update_display);
  timer->start(30);
}

SnakeWidget::~SnakeWidget() { delete timer; }

void SnakeWidget::draw_apple() {
  Coordinate apple = game.get_apple();
  scene->addEllipse(apple.x * 10, apple.y * 10, 10, 10, QPen(Qt::black),
                    QBrush(Qt::red));
}

void SnakeWidget::draw_snake() {
  printf("draw_snake");
  scene->clear();
  for (const auto &i : game.get_snake()) {
    scene->addRect(i.x * 10, i.y * 10, 10, 10, QPen(Qt::black),
                   QBrush(Qt::green));
  }
}

void SnakeWidget::paintEvent(/*QPaintEvent *event*/) {
  printf("paintEvent");
  QPainter p(this);
  SnakeGame &snake = SnakeGame::get_instance();
  if (snake.get_state() == Begin) {
    p.drawText(rect(), Qt::AlignCenter, "Press ENTER to Start");
  } else if (snake.get_state() == End) {
    if (snake.get_GameInfo().score == SCORE_WIN) {
      p.drawText(rect(), Qt::AlignCenter, "You Win!");
      // статистика
    } else {
      p.drawText(rect(), Qt::AlignCenter, "Game Over!");
    }
  } else {
    draw_apple();
    draw_snake();
    // статистика
    if (snake.get_state() == Break) {
      p.drawText(rect(), Qt::AlignCenter, "PAUSE");
    }
  }
}

void SnakeWidget::keyPressEvent(QKeyEvent *key) {
  UserAction_t act;
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
  // bool hold = (act == Action) ? true : false;
  // controller.userInput(act, hold);
  // update_paint();
  if (act == Terminate) {
    QWidget::close();
  }
}

void SnakeWidget::update_display() {
  // update();
  repaint();
}
