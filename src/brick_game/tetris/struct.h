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
  Action
} UserAction_t;

/**
 * @enum GameState_t
 * @brief состояния конечного автомата
 */
typedef enum {
  /** старт */
  Begin,
  /** генерация фигур */
  Generation,
  /** падение фигуры */
  Falling,
  /** пауза */
  Break,
  /** поворот */
  Moving_rotate,
  /** движение фигуры влево */
  Moving_left,
  /** движение фигуры вправо */
  Moving_right,
  /** движение фигуры вниз */
  Moving_down,
  /** соединение фигуры и поля */
  Attaching,
  /** конец игры */
  End,
  /** выход из игры */
  Exit
} GameState_t;

/**
 * @struct GameInfo_t
 * @brief частичная информация о текущем состоянии игры
 */
typedef struct {
  /** игровое поле */
  int **field;
  /** превью фигура */
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
  /** частичная информация о текущем состоянии игры */
  GameInfo_t game_info;
  /** информация о состоянии конечного автомата */
  GameState_t state;
} Game_tetris;

#endif