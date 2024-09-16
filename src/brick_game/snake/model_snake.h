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
  std::list<Coordinate> snake; /*змейка*/
  Coordinate apple;            /*яблоко*/
  Direction dir;               /*направление движения*/
  GameState_t state;           /*состояние игры*/
  UserAction_t currentAction;  /*кнопки*/
  /** предыдущее время падения фигуры */
  long long int prev_time;

  int s_score;
  int s_high_score;
  int s_level;
  int s_speed;

public:
  SnakeGame();
  ~SnakeGame() = default;

  void set_state(GameState_t state);
  void set_currAction(UserAction_t currentAction);
  void set_prev_time(long long int time);

  GameState_t get_state() const;
  UserAction_t get_currAction();
  std::list<Coordinate> &get_snake();
  Coordinate get_apple();
  int get_score();
  int get_high_score();
  int get_level();
  int get_speed();

  void clearing_game();
  void initial_info();
  void put_apple();
  void create_snake();

  Coordinate snake_head_new_pos();
  bool collision(const Coordinate &pos);
  void check_move_snake();
  void move_snake();
  void change_direction(UserAction_t currentAction);
  void increase_level();
  void save_high_score();

  void update();
};

} // namespace s21