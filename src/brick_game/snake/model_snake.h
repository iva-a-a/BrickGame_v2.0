#include "../tetris/back_tetris.h"

#include <cstdlib> // для rand()
#include <ctime>   // для time()
#include <iostream>
#include <list>

namespace s21 {

enum class Direction {
  Up,    /*движение вверх*/
  Down,  /*движение вниз*/
  Right, /*движение вправо*/
  Left   /*движение влево*/
};

struct Coordinate {
  int x;
  int y;
  bool eq_coordinate(const Coordinate &a) const {
    return (x == a.x && y == a.y);
  }
};

class SnakeGame {
private:
  GameInfo_t gameInfo;
  std::list<Coordinate> snake; /*змейка*/
  Coordinate apple;            /*яблоко*/
  Direction dir;               /*направление движения*/
  GameState_t state;           /*состояние игры*/
  UserAction_t currentAction;  /*кнопки*/
  /** предыдущее время падения фигуры */
  long long int prev_time;
  SnakeGame();
  ~SnakeGame() = default;
  SnakeGame(SnakeGame const &) = delete;
  SnakeGame &operator=(SnakeGame const &) = delete;

public:
  void set_state(GameState_t state);
  GameState_t get_state() const;

  static SnakeGame &get_instance();

  GameInfo_t &get_GameInfo();
  UserAction_t get_currAction();
  void set_currAction(UserAction_t currentAction);
  std::list<Coordinate> &get_snake();
  void set_prev_time(long long int time);
  Coordinate get_apple();

  void clearing_game();
  void initial_info();
  void put_apple();
  void create_snake();

  Coordinate snake_head_new_pos();
  bool collision(const Coordinate &pos);
  void move_snake();
  void change_direction(UserAction_t currentAction, bool hold);
  void increase_level();
  void save_high_score();
};

} // namespace s21