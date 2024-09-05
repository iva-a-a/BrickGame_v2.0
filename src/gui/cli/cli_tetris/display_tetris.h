#ifndef DISPLAY_TETRIS_H
#define DISPLAY_TETRIS_H

#include "../display.h"
/**
 * @brief вывод информациии об игре
 *
 * @param info состояние игры тетрис
 */
void print_stats_tetris(Game_tetris *info);

/**
 * @brief отрисовка поля, заполненного упавшими фигурами
 *
 * @param tetris состояние игры
 */
void print_fall_figure(Game_tetris *tetris);

/**
 * @brief отрисовка текущей фигуры на поле
 *
 * @param tetris состояние игры
 */
void print_now_figure(Game_tetris *tetris);

/**
 * @brief отрисовка следующей фигуры
 *
 * @param tetris состояние игры
 */
void print_next_figure(Game_tetris *tetris);
#endif