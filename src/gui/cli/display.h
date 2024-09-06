#ifndef DISPLAY_H
#define DISPLAY_H

#include "../../brick_game/tetris/back_tetris.h"
#include <ncurses.h>

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
 * @brief отрисовка заставки для выбора игры
 */
void print_game_setection();
void clear_screen();

/**
 * @brief отрисовка игрового поля
 */
void print_game_board();

/**
 * @brief вывод информациии об игре
 */
void print_stats();

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

#endif