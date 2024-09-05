#include "back_snake.h"

using namespace s21;

GameInfo_t &SnakeGame::get_GameInfo() { return gameInfo; }
UserAction_t SnakeGame::get_currAction() { return currentAction; }
void SnakeGame::set_currAction(UserAction_t action) {
  this->currentAction = action;
}

std::list<Coordinate> &SnakeGame::get_snake() { return snake; }

void SnakeGame::set_prev_time(long long int time) { prev_time = time; }

Coordinate SnakeGame::get_apple() { return apple; }

void SnakeGame::initial_info() {
  FILE *highScore;
  highScore = fopen("highscore_snake.txt", "r");
  if (highScore) {
    if (fscanf(highScore, "%d", &gameInfo.high_score) == 0) {
      gameInfo.high_score = 0;
    }
    fclose(highScore);
  }
  clearing_game();
}

void SnakeGame::clearing_game() {

  gameInfo.score = 0;
  gameInfo.level = 1;
  gameInfo.speed = 500;
  gameInfo.pause = 0;

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
  srand(time(NULL)); //вынести в мейн
  initial_info();
}

SnakeGame &SnakeGame::get_instance() {
  static SnakeGame snake;
  return snake;
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
  for (auto i = --(--snake.end()); i != snake.begin(); i--) {
    if (pos.eq_coordinate(*i)) {
      return true;
    }
  }
  return false;
}

/*движение змейки*/
void SnakeGame::move_snake() {
  long long int time = time_in_millisec();
  Coordinate pos = snake_head_new_pos();
  if (time - prev_time > gameInfo.speed) {
    snake.push_back(pos);
    if (pos.eq_coordinate(apple) == true) {
      gameInfo.score++;
      if (gameInfo.score == SCORE_WIN) {
        state = End;
      } else {
        state = Attaching;
      }
    } else {
      snake.pop_front();
    }
    if (collision(pos)) {
      state = End;
    }
    prev_time = time;
  }
}

void SnakeGame::change_direction(UserAction_t currentAction, bool hold) {
  hold = true;
  if (currentAction == Down && dir != Direction::Up && hold == true) {
    dir = Direction::Down;
  } else if (currentAction == Up && dir != Direction::Down) {
    dir = Direction::Up;
  } else if (currentAction == Left && dir != Direction::Right) {
    dir = Direction::Left;
  } else if (currentAction == Right && dir != Direction::Left) {
    dir = Direction::Right;
  }
  /*реализовать холд*/
}

void SnakeGame::increase_level() {
  while (gameInfo.score >= gameInfo.level * LEVEL_NEXT_SNAKE &&
         gameInfo.level != MAX_LEVEL) {
    if (gameInfo.level < MAX_LEVEL) {
      gameInfo.level++;
      gameInfo.speed -= 50;
    }
  }
}

void SnakeGame::save_high_score() {
  if (gameInfo.score >= gameInfo.high_score) {
    gameInfo.high_score = gameInfo.score;
    FILE *highScore;
    highScore = fopen("highscore_snake.txt", "w");
    if (highScore) {
      fprintf(highScore, "%d", gameInfo.high_score);
      fclose(highScore);
    }
  }
}
