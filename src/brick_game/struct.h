#ifndef STRUCT_H
#define STRUCT_H

#include <sys/time.h>
#include <time.h>
/**
 * @enum UserAction_t
 * @brief пользовательское действие
 */
typedef enum {
  /** кнопка старт */
  Start = 10,
  /** кнопка пауза */
  Pause,
  /** кнопка выход */
  Terminate,
  /** кнопка влево */
  Left,
  /** кнопка вправо */
  Right,
  /** кнопка вверх */
  Up,
  /** кнопка вниз */
  Down,
  /** кнопка движение */
  Action,
  /** отсутствие нажатия нужной кнопки */
  None
} UserAction_t;

/**
 * @enum GameState_t
 * @brief состояния конечного автомата
 */
typedef enum {
  /** старт */
  Begin,
  /** генерация */
  Generation,
  /** падение фигуры или движение змейки*/
  Falling,
  /** пауза */
  Break,
  /** поворот */
  Moving_rotate,
  /** движение влево */
  Moving_left,
  /** движение вправо */
  Moving_right,
  /** движение вниз */
  Moving_down,
  /** соединение */
  Attaching,
  /** конец игры */
  End,
  /** выход из игры */
  Exit
} GameState_t;

/**
 * @struct GameInfo_t
 * @brief информация о текущем состоянии игры
 */
typedef struct {
  /** игровое поле */
  int **field;
  /** превью */
  int **next;
  /** количество очков */
  int score;
  /** количество рекордных очков */
  int high_score;
  /** номер уровня */
  int level;
  /** скорость */
  int speed;
  /** нажата ли пауза */
  int pause;
} GameInfo_t;

/**
 * @brief получение времени в миллисекундах
 *
 * @return возвращает время в миллисекундах
 */
inline long long int time_in_millisec() {
  struct timeval tv;
  gettimeofday(&tv, NULL);
  return (((long long int)tv.tv_sec) * 1000) + (tv.tv_usec / 1000);
}

#endif