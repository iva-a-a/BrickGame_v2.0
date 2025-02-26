#pragma once

#include "model_snake.h"

namespace s21 {

/**
 * @class Controller
 * @brief класс, отвечающий за управление игрой "Змейка"
 */
class Controller {
 private:
  SnakeGame model; /**< модель игры "Змейка" */

 public:
  /**
   * @brief конструктор по умолчанию класса Controller
   */
  Controller() = default;
  /**
   * @brief деструктор по умолчанию класса Controller
   */
  ~Controller() = default;

  /**
   * @brief преобразование списка координат змеи в двумерный массив
   *
   * @param snake список координат, представляющий змею
   * @return указатель на двумерный массив с координатами змеи
   */
  int **convert_snake_to_array(std::list<Coordinate> snake);
  /**
   * @brief преобразование координат яблока в двумерный массив
   *
   * @param apple координаты яблока
   * @return указатель на двумерный массив с координатами яблока
   */
  int **convert_apple_to_array(Coordinate apple);
  /**
   * @brief освобождение памяти, занятой двумерным массивом
   *
   * @param array указатель на массив, который необходимо освободить
   */
  void free_array(int **array);

  /**
   * @brief обработка пользовательского ввода
   *
   * @param currentAction текующее действие пользователя
   * @param hold параметр, указывающий, удерживается ли кнопка
   */
  void userInput(UserAction_t currentAction, bool hold);
  /**
   * @brief обновление текущего состояние игры
   *
   * @return структура с информацией о текущем состоянии игры
   */
  GameInfo_t updateCurrentState();
  /**
   * @brief очистка информации о состоянии игры
   *
   * @param info_snake ссылка на структуру, которую нужно очистить
   */
  void clearGameInfo(GameInfo_t &info_snake);

  /**
   * @brief получение указателя на модель игры
   *
   * @return указатель на модель структуры SnakeGame
   */
  SnakeGame *get_model();
};
}  // namespace s21