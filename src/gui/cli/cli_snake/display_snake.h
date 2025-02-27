#pragma once

#include "../../../brick_game/snake/controller_snake.h"
#include "../display.h"
/**
 * @class SnakeDisplay
 * @brief класс для отображения игры "Змейка" в терминале
 */
class SnakeDisplay {
 private:
  Controller *controller; /**< указатель на контроллер игры */

 public:
  /**
   * @brief конструктор класса SnakeDisplay
   * @param c указатель на объект Controller, который будет использоваться для
   * управления игрой
   */
  explicit SnakeDisplay(Controller *c);
  /**
   * @brief деструктор класса SnakeDisplay по умолчаниб
   */
  ~SnakeDisplay() = default;

  /**
   * @brief вывод сообщения о победе
   */
  void print_win();

  /**
   * @brief основной игровой бесконечный цикл игры "Змейка"
   */
  void game_snake();
  /**
   * @brief отрисовка текущего состояние игры
   * @param info ссылка на структуру GameInfo_t, содержащую информацию о текущем
   * состоянии игры
   */
  void printCurrentState(GameInfo_t &info);
};
