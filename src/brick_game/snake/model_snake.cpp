#include "model_snake.h"

#include <fstream>

using namespace s21;

UserAction_t SnakeGame::get_currAction() { return currentAction; }
void SnakeGame::set_currAction(UserAction_t action) {
  this->currentAction = action;
}

std::list<Coordinate> &SnakeGame::get_snake() { return snake; }

void SnakeGame::set_prev_time(long long int time) { prev_time = time; }

Coordinate SnakeGame::get_apple() { return apple; }

void SnakeGame::initial_info() {
  std::ifstream inputFile("highscore_snake.txt");

  if (inputFile.is_open()) {
    inputFile >> s_high_score;
    inputFile.close();
  } else {
    std::ofstream outputFile("highscore_snake.txt");
    s_high_score = 0;
    outputFile << s_high_score;
    outputFile.close();
  }
  clearing_game();
}

int SnakeGame::get_score() { return this->s_score; }
int SnakeGame::get_high_score() { return this->s_high_score; }
int SnakeGame::get_level() { return this->s_level; }
int SnakeGame::get_speed() { return this->s_speed; }

void SnakeGame::clearing_game() {

  s_score = 0;
  s_level = 1;
  s_speed = 500;
  prev_time = 0;

  currentAction = None;
  state = Begin;
  dir = Direction::Up;
  put_apple();
  create_snake();
}

/*генерируем рандомное положение яблока*/
void SnakeGame::put_apple() {
  int x, y;
  bool apple_on_snake;
  do {
    x = rand() % ROWS_BOARD;
    y = rand() % COL_BOARD;
    apple = {x, y};
    apple_on_snake = false;
    for (const auto &i : snake) {
      if (apple.eq_coordinate(i)) {
        apple_on_snake = true;
      }
    }
  } while (apple_on_snake);
}

void SnakeGame::create_snake() { snake = {{18, 5}, {17, 5}, {16, 5}, {15, 5}}; }

/*конструктор по умолчанию - иницилизация игры*/
SnakeGame::SnakeGame() {
  srand(time(NULL));
  initial_info();
}

void SnakeGame::set_state(GameState_t state) { this->state = state; }

GameState_t SnakeGame::get_state() const { return this->state; }

/*получаем новое положение головы в зависимости от направления движения*/
Coordinate SnakeGame::snake_head_new_pos() {
  Coordinate pos = snake.back();
  switch (dir) {
  case Direction::Up:
    pos.x--;
    break;
  case Direction::Down:
    pos.x++;
    break;
  case Direction::Left:
    pos.y--;
    break;
  case Direction::Right:
    pos.y++;
  }
  return pos;
}

/*проверка на столкновение*/
bool SnakeGame::collision(const Coordinate &pos) {
  if (pos.x < 0 || pos.x >= ROWS_BOARD || pos.y < 0 || pos.y >= COL_BOARD) {
    return true;
  }
  for (auto i = --snake.end(); i != snake.begin(); i--) {
    if (pos.eq_coordinate(*i)) {
      return true;
    }
  }
  return false;
}

void SnakeGame::move_snake() {
  Coordinate pos = snake_head_new_pos();
  if (collision(pos)) {
    // snake.pop_back();
    // snake.push_front(pos);
    state = End;
  }
  snake.push_back(pos);
  if (pos.eq_coordinate(apple) == true) {
    s_score++;
    if (s_score == SCORE_WIN) {
      state = End;
    } else {
      state = Attaching;
    }
  } else {
    snake.pop_front();
  }
}

/*движение змейки*/
void SnakeGame::check_move_snake() {
  long long int time = time_in_millisec();

  if (time - prev_time > s_speed) {
    move_snake();
    prev_time = time;
  }
}

void SnakeGame::change_direction(UserAction_t currentAction) {
  if (currentAction == Down && dir != Direction::Up) {
    dir = Direction::Down;
  } else if (currentAction == Up && dir != Direction::Down) {
    dir = Direction::Up;
  } else if (currentAction == Left && dir != Direction::Right) {
    dir = Direction::Left;
  } else if (currentAction == Right && dir != Direction::Left) {
    dir = Direction::Right;
  }
}

void SnakeGame::increase_level() {
  while (s_score >= s_level * LEVEL_NEXT_SNAKE && s_level != MAX_LEVEL) {
    if (s_level < MAX_LEVEL) {
      s_level++;
      s_speed -= 50;
    }
  }
}

void SnakeGame::save_high_score() {
  if (s_score >= s_high_score) {
    s_high_score = s_score;
    std::ofstream outputFile("highscore_snake.txt");
    outputFile << s_high_score;
    outputFile.close();
  }
}

void SnakeGame::update() {
  if (state == Begin) {
    clearing_game();
  } else if (state == Generation) {
    set_prev_time(time_in_millisec());
    put_apple();
    set_state(Falling);
  } else if (state == Falling) {
    check_move_snake();
  } else if (state == Moving_rotate) {
    change_direction(currentAction);
    snake_head_new_pos();
    set_state(Falling);
  } else if (state == Attaching) {
    increase_level();
    save_high_score();
    state = Generation;
  }
}
