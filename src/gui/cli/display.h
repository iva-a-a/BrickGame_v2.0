#ifndef DISPLAY_H
#define DISPLAY_H

#include <ncurses.h>

#include "../../brick_game/tetris/function.h"

/**
 * @brief иницилизация графического интерфейса программы
 */
void setup_gui();

/**
 * @brief удаление графического интерфейса
 */
void delete_gui();

/**
 * @brief ввод с клавиатуры
 *
 * @return возвращает пользовательское действие
 */
UserAction_t input_key();

/**
 * @brief отрисовка игрового поля
 */
void print_game_board();

/**
 * @brief вывод информациии об игре
 *
 * @param info состояние игры
 */
void print_stats(Game_tetris *info);

/**
 * @brief вывод заставки начала игры
 */
void print_start();

/**
 * @brief вывод паузы
 */
void print_pause();

/**
 * @brief вывод результатов
 */
void print_game_over();

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