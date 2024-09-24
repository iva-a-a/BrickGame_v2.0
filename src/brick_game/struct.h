#ifndef STRUCT_H
#define STRUCT_H

/**
 * @enum UserAction_t
 * @brief пользовательское действие
 */
typedef enum {
  /** кнопка старт */
  Start,
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
 * @struct Game_tetris
 * @brief полная информация о текущем состоянии игры
 */
typedef struct {
  /** игровое поле */
  int **field;
  /** превью фигура */
  int **next;
  /** текущая фигура на поле */
  int **now;
  /** координата фигуры по строке */
  int x;
  /** координата фигуры по столбцу */
  int y;
  /** номер текущей фигуры */
  int number_now_f;
  /** номер следующей генерируемой фигуры */
  int number_next_f;
  /** предыдущее время падения фигуры */
  long long int prev_time;
  /** количество очков */
  int score;
  /** количество рекордных очков */
  int high_score;
  /** номер уровня */
  int level;
  /** скорость */
  int speed;
  /** информация о состоянии конечного автомата */
  GameState_t state;
} Game_tetris;

#endif