#ifndef DISPLAY_TETRIS_H
#define DISPLAY_TETRIS_H

#include "../../../brick_game/tetris/controller_tetris.h"
#include "../display.h"

/**
 * @brief вывод информации для тетриса
 */
void print_stats_tetris();

/**
 * @brief отрисовка игрового поля, заполняемого фигурами
 * @param arr указатель на входную матрицу
 * @param row количество строк матрицы
 * @param col количество столбцов матрицы
 */
void print_fallfigure(int **arr, int row, int col);

/**
 * @brief очистка места для отрисовки превью фигуры
 */
void clear_next_figure();

/**
 * @brief отрисовка игры
 *
 * @param info состояние игры
 */
void printCurrentState(GameInfo_t *info);

/**
 * @brief бесконечный цикл игры
 */
void game_tetris();

#endif