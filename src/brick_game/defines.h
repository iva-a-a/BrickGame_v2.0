#ifndef DEFINES_H
#define DEFINES_H

/**
 * @def ROWS_BOARD
 * @brief количество строк поля
 */
#define ROWS_BOARD 20

/**
 * @def COL_BOARD
 * @brief количество столбцов поля
 */
#define COL_BOARD 10

/**
 * @def ROWS_FIGURE
 * @brief количество строк для фигуры
 */
#define ROWS_FIGURE 4
/**
 * @def COL_FIGURE
 * @brief количество столбцов для фигуры
 */
#define COL_FIGURE 4

/**
 * @def TETRIS_F
 * @brief количество фигур
 */
#define TETRIS_F 7

/**
 * @def SCORE_1
 * @brief количество очков за 1 убранную линию
 */
#define SCORE_1 100

/**
 * @def SCORE_2
 * @brief количество очков за 2 убранные линии
 */
#define SCORE_2 300

/**
 * @def SCORE_3
 * @brief количество очков за 3 убранные линии
 */
#define SCORE_3 700

/**
 * @def SCORE_4
 * @brief количество очков за 4 убранные линии
 */
#define SCORE_4 1500

/**
 * @def SCORE_WIN
 * @brief количество очков для выигрыша змейки
 */
#define SCORE_WIN 200

/**
 * @def LEVEL_NEXT
 * @brief количество очков, необходимых для увеличения уровня тетриса
 */
#define LEVEL_NEXT 600

/**
 * @def LEVEL_NEXT_SNAKE
 * @brief количество очков, необходимых для увеличения уровня змейки
 */
#define LEVEL_NEXT_SNAKE 5

/**
 * @def MAX_LEVEL
 * @brief максимальное количество уровней
 */
#define MAX_LEVEL 10

/**
 * @def FIGURES
 * @brief возможные фигуры для игры в тетрис: I, J, L, O, S, T, Z
 */
#define FIGURES                                                                \
  {                                                                            \
    {{0, 0, 0, 0}, {1, 1, 1, 1}, {0, 0, 0, 0}, {0, 0, 0, 0}},                  \
        {{1, 0, 0, 0}, {1, 1, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}},              \
        {{0, 0, 1, 0}, {1, 1, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}},              \
        {{0, 1, 1, 0}, {0, 1, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}},              \
        {{0, 1, 1, 0}, {1, 1, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}},              \
        {{0, 1, 0, 0}, {1, 1, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}}, {            \
      {1, 1, 0, 0}, {0, 1, 1, 0}, {0, 0, 0, 0}, { 0, 0, 0, 0 }                 \
    }                                                                          \
  }

#endif