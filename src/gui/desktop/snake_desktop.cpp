#include "snake_desktop.h"

#include <iomanip>
#include <sstream>
#include <string>

using namespace s21;

#define LOG(...)                                                               \
  {                                                                            \
    printf(__VA_ARGS__);                                                       \
    fflush(stdout);                                                            \
    printf("\n");                                                              \
  }

SnakeWidget::SnakeWidget(QMainWindow *window)
    : QMainWindow{window}, model{}, controller{&model} {
  setFixedSize(SIZE_RECT * 10 + 200, SIZE_RECT * 20 + 10);
  setFocusPolicy(Qt::StrongFocus);
  setWindowTitle("Snake");

  timer = new QTimer;
  connect(timer, &QTimer::timeout, this, &SnakeWidget::update_display);
  timer->start(30);
}

SnakeWidget::~SnakeWidget() { delete timer; }

void SnakeWidget::draw_apple(QPainter &p) {
  s21::SnakeGame m = s21::SnakeGame::get_instance();
  Coordinate apple = m.get_apple();
  p.fillRect(apple.y * SIZE_RECT, apple.x * SIZE_RECT, SIZE_RECT, SIZE_RECT,
             QBrush(Qt::red));
}

void SnakeWidget::draw_snake(QPainter &p) {
  s21::SnakeGame m = s21::SnakeGame::get_instance();
  for (const auto &i : m.get_snake()) {
    p.fillRect(i.y * SIZE_RECT, i.x * SIZE_RECT, SIZE_RECT, SIZE_RECT,
               QBrush(Qt::black));
  }
}

void SnakeWidget::draw_field(QPainter &p) {
  for (int x = 0; x < SIZE_RECT * 10; x += SIZE_RECT) {
    for (int y = 0; y < SIZE_RECT * 20; y += SIZE_RECT) {
      p.drawRect(x, y, SIZE_RECT, SIZE_RECT);
    }
  }
}

void SnakeWidget::draw_stat(QPainter &p) {
  s21::SnakeGame m = s21::SnakeGame::get_instance();
  GameInfo_t info = m.get_GameInfo();
  QFont font;
  font.setPointSize(14);
  p.setFont(font);
  std::string s = "Score: " + std::to_string(info.score);
  p.drawText(SIZE_RECT * 10 + 5, SIZE_RECT + 25, s.data());
  std::string hs = "High score: " + std::to_string(info.high_score);
  p.drawText(SIZE_RECT * 10 + 5, SIZE_RECT * 2 + 25, hs.data());
  std::string l = "Level: " + std::to_string(info.level);
  p.drawText(SIZE_RECT * 10 + 5, SIZE_RECT * 3 + 25, l.data());
  float speedSn = (float)500 / info.speed;
  std::ostringstream oss;
  oss << std::fixed << std::setprecision(2) << speedSn;
  std::string sp = "Speed: " + oss.str();
  p.drawText(SIZE_RECT * 10 + 5, SIZE_RECT * 4 + 25, sp.data());

  p.drawText(SIZE_RECT * 10 + 5, SIZE_RECT * 15 + 25, "     Press:");
  p.drawText(SIZE_RECT * 10 + 5, SIZE_RECT * 16 + 25, "ESC - exit");
  p.drawText(SIZE_RECT * 10 + 5, SIZE_RECT * 17 + 25, "BACKSPACE - pause");
  p.drawText(SIZE_RECT * 10 + 5, SIZE_RECT * 18 + 25, "ARROWS - move");
}

void SnakeWidget::paintEvent(QPaintEvent *event) {
  // Q_UNUSED(event)
  // QPainter p(this);
  // SnakeGame &snake = SnakeGame::get_instance();

  // controller.updateCurrentState();
  // LOG("paintEvent, %d", snake.get_state());

  // if (snake.get_state() == Begin) {

  //   p.drawText(rect(), Qt::AlignCenter, "Press ENTER to Start");
  // } else if (snake.get_state() == End) {
  //   if (snake.get_GameInfo().score == SCORE_WIN) {
  //     p.drawText(rect(), Qt::AlignCenter, "You Win!");
  //     draw_stat(p);
  //   } else {
  //     p.drawText(rect(), Qt::AlignCenter, "Game Over!");
  //   }
  // } else if (snake.get_state() == Falling) {
  //   draw_field(p);
  //   draw_apple(p);
  //   draw_snake(p);
  //   draw_stat(p);

  // } else if (snake.get_state() == Break) {
  //   p.drawText(305, 325, "PAUSE");
  // }

  Q_UNUSED(event)
  QPainter p(this);
  SnakeGame &snake = SnakeGame::get_instance();

  controller.updateCurrentState();
  LOG("paintEvent, %d", snake.get_state());
  if (snake.get_state() != Begin) {
    draw_field(p);
    draw_apple(p);
    draw_snake(p);
    draw_stat(p);
  }
  if (snake.get_state() == Begin) {
    p.drawText(rect(), Qt::AlignCenter, "Press ENTER to Start");
  } else if (snake.get_state() == End) {
    if (snake.get_GameInfo().score == SCORE_WIN) {
      p.drawText(SIZE_RECT * 10 + 5, SIZE_RECT * 10 + 25, "YOU WIN!");
    } else {
      p.drawText(SIZE_RECT * 10 + 5, SIZE_RECT * 10 + 25, "GAME OVER!");
      p.drawText(SIZE_RECT * 10 + 5, SIZE_RECT * 19 + 25, "ENTER - restart");
    }
  } else if (snake.get_state() == Break) {
    p.drawText(SIZE_RECT * 10 + 5, SIZE_RECT * 10 + 25, "PAUSE");
  }
}

void SnakeWidget::keyPressEvent(QKeyEvent *key) {
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
  bool hold = (act == Action) ? true : false;
  controller.userInput(act, hold);
  update_display();
  if (act == Terminate) {
    if (key->key() == Qt::Key_Escape) {
      QWidget::close();
    }
  }
}

void SnakeWidget::update_display() {
  repaint();
  update();
}
