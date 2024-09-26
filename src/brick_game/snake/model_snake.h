#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <list>

#include "../defines.h"
#include "../struct.h"

namespace s21 {

/**
 * @enum Direction
 * @brief направление движения змейки
 */
enum class Direction {
  Up,    /**< движение вверх*/
  Down,  /**< движение вниз*/
  Right, /**< движение вправо*/
  Left   /**< движение влево*/
};

/**
 * @struct Coordinate
 * @brief координаты на игровом поле
 */
struct Coordinate {
  int x; /**< Координата x */
  int y; /**< Координата y */
  /**
   * @brief проверка равенства координат
   * @param a координата для сравнения
   * @return true, если координаты равны, иначе false
   */
  bool eq_coordinate(const Coordinate &a) const {
    return (x == a.x && y == a.y);
  }
  /**
   * @brief перегрузка оператора ==
   * @param a координата для сравнения
   * @return true, если координаты равны, иначе false
   */
  bool operator==(const Coordinate &a) const { return eq_coordinate(a); }
};

/**
 * @class SnakeGame
 * @brief основной класс для игры "Змейка"
 */
class SnakeGame {
 private:
  Direction dir;     /**< направление движения змейки*/
  GameState_t state; /**< состояние игры */
  UserAction_t currentAction; /**< текущее действие игрока */
  long long int prev_time; /**< предыдущее время падения фигуры */

  int s_high_score; /**< количество рекордных очков */
  int s_level;      /**< номер уровня */
  int s_speed;      /**< скорость движения змейки */

 protected:
  std::list<Coordinate> snake; /**< список координат змейки */
  int s_score;                 /**< количество очков */
  Coordinate apple;            /**< Координаты яблока */
 public:
  /**
   * @brief конструктор класса SnakeGame
   */
  SnakeGame();
  /**
   * @brief деструктор класса SnakeGame
   */
  ~SnakeGame() = default;

  /**
   * @brief установка состояния игры
   * @param state новое состояние игры
   */
  void set_state(GameState_t state);
  /**
   * @brief установка текущего действия игрока
   * @param currentAction новое действие игрока
   */
  void set_currAction(UserAction_t currentAction);
  /**
   * @brief установка предыдущего времени
   * @param time новое значение времени
   */
  void set_prev_time(long long int time);

  // /**
  //  * @brief установка количества очков (для тестирования)
  //  * @param score новое значение очков
  //  */
  // void set_score(int score);

  /**
   * @brief получение текущего состояние игры
   * @return текущее состояние игры
   */
  GameState_t get_state() const;
  /**
   * @brief получение текущего действие игрока
   * @return текущее действие игрока
   */
  UserAction_t get_currAction();
  /**
   * @brief получение ссылки на список координат змейки
   * @return список координат змейки
   */
  std::list<Coordinate> &get_snake();
  /**
   * @brief получение координат яблока
   * @return координаты яблока
   */
  Coordinate get_apple();
  /**
   * @brief получение количества очков
   * @return количество очков
   */
  int get_score();
  /**
   * @brief получение рекордного количества очков
   * @return рекордное количество очков
   */
  int get_high_score();
  /**
   * @brief получение уровня игры
   * @return уровень игры
   */
  int get_level();
  /**
   * @brief получение скорости игры
   * @return скорость игры
   */
  int get_speed();

  /**
   * @brief сброс параметров игры
   */
  void clearing_game();
  /**
   * @brief инициализирует параметры игры
   */
  void initial_info();
  /**
   * @brief размещение яблока на игровом поле
   */
  void put_apple();
  /**
   * @brief создание начальной позиции змейки
   */
  void create_snake();

  /**
   * @brief вычисление новой позиции головы змейки
   * @return новая позиция головы змейки
   */
  Coordinate snake_head_new_pos();
  /**
   * @brief проверка на столкновение с заданной позицией
   * @param pos координаты позиции для проверки
   * @return true, если произошла коллизия, иначе false
   */
  bool collision(const Coordinate &pos);
  /**
   * @brief проверка возможности движения змейки
   */
  void check_move_snake();
  /**
   * @brief движение змейку
   */
  void move_snake();
  /**
   * @brief изменение направления движения змейки по действию игрока
   * @param currentAction действие игрока
   */
  void change_direction(UserAction_t currentAction);
  /**
   * @brief повышение уровня игры
   */
  void increase_level();
  /**
   * @brief сохранение рекордных очков
   */
  void save_high_score();

  /**
   * @brief обновляет игры
   */
  void update();
};

}  // namespace s21